How to make a RPG levelling system
========================

## Description

It's very common in RPG games to have a levelling system.

Usually a character has a level, a value for experience and other "accessories" like
- next level experience
- next level

Once a character levels up, some stats are increased, like health, mana, strength, etc.

You can handle those stats with the `Attribute` system in a very easy way.

## How should it work

1. The character has a level.
2. The character has a value for experience.
3. The character has a value for next level experience, which is derived both from level and experience and calculated in a `x` way.
4. When the character gains experience
   - the experience value is increased
   - if the experience value is greater than or equal to the next level experience, the character levels up.
     - the remaining experience is calculated as `experience - next_level_experience` and reassigned to the experience attribute.
     - the level is increased by 1.
   - if there is a hard cap on level, the level is clamped to the maximum value and checked before getting experience.

## Steps

1. Create a new `Attribute` class for the level.
   - This attribute will be used to store the level of the character.
   - If you need a "hard cap" on level, you can choose to create a `MaxLevelAttribute` class or you could simply export a value from this attribute.
2. Create a new `Attribute` class for the experience.
3. Create a new `Attribute` class for the next level experience.

Experience and Level attributes are considered to be "base" attributes, while the 'next level experience' is a "derived" attribute.

To handle the levelling, you will perform all calculations in an `AttributeBuff` class.

We need to do two things: set up the attributes and write the buff logic.

#### Setup attributes

Create a Level attribute.

This attribute will be used to store the level of the character.

```gdscript
class_name LevelAttribute
extends Attribute

const ATTRIBUTE_NAME = "Level"

@export var max_level: int = 60 ## hard cap on level, like in diablo games

func _init(_attribute_name := ATTRIBUTE_NAME):
    attribute_name = _attribute_name
    
    
func _compute_value(argument: AttributeComputationArgument) -> float:
    ## 1 is the minimum level, we clamp the level value to 1 and the exported max_level
    return clampf(argument.operated_value, 1, max_level)
```

Create an Experience attribute:

```gdscript
class_name ExperienceAttribute
extends Attribute

const ATTRIBUTE_NAME = "Experience"

func _init(_attribute_name := ATTRIBUTE_NAME):
    attribute_name = _attribute_name
```

Create a NextLevelExperience attribute (this is a derived attribute):

```gdscript
class_name NextLevelExperienceAttribute
extends Attribute

const ATTRIBUTE_NAME = "NextLevelExperience"
const EXPERIENCE_PER_LEVEL 	:= 20.0 # Base experience per level
const SCALE 				:= 1.5  # Scale for the experience curve


func _init(_attribute_name := ATTRIBUTE_NAME):
    attribute_name = _attribute_name

func _derived_from(attribute_set: AttributeSet) -> Array[Attribute]:
    return [
        attribute_set.find_by_name(LevelAttribute.ATTRIBUTE_NAME),
    ]
    
func _compute_value(argument: AttributeComputationArgument) -> float:
    var level_attribute := argument.get_parent_attributes()[0]
    var level := level_attribute.get_value()
    
    # The next level experience is calculated as 100 * level
    return round(((current_level * SCALE) ** 1.5) * EXPERIENCE_PER_LEVEL)
```

Create the `GetExperienceBuff` class, which also levels up the character if needed.

```gdscript
class_name GetExperienceBuff
extends AttributeBuff


@export var min_experience_gained: float = 3.0      # Minimum experience gained from the buff
@export var max_experience_gained: float = 10.0     # Maximum experience gained from the buff


func _applies_to(attribute_set: AttributeSet) -> Array[Attribute]:
    return [
        attribute_set.find_by_name(LevelAttribute.ATTRIBUTE_NAME),
        attribute_set.find_by_name(ExperienceAttribute.ATTRIBUTE_NAME),
        attribute_set.find_by_name(NextLevelExperienceAttribute.ATTRIBUTE_NAME),
    ]
    
    
func _operate(values: PackedFloatArray, attribute_set: AttributeSet) -> Array[AttributeOperation]:
    var level                   := values[0]
    var experience              := values[1]
    var next_level_experience   := values[2]
    var exp_gained              := randf_range(min_experience_gained, max_experience_gained)
    ## Let's calculate the new experience
    var new_experience          := experience + exp_gained

    ## Check if the character can levels up
    if level == attribute_set.find_by_name(LevelAttribute.ATTRIBUTE_NAME).max_level:
        # we add 0 level, experience and next level experience
        return [
            AttributeOperation.add(0), 
            AttributeOperation.add(0),
            AttributeOperation.add(0),
        ]

    var level_op: AttributeOperation    = AttributeOperation.add(0)
    var experience_op: AttributeOperation = AttributeOperation.add(exp_gained)
    var next_level_experience_op: AttributeOperation = AttributeOperation.add(0)
    
    if new_experience >= next_level_experience:
        return [
            AttributeOperation.add(1), ## level up!
            AttributeOperation.add(new_experience - next_level_experience), ## remaining experience
            next_level_experience_op, ## next level experience, 0 because it's automatically calculated by the derived attribute
        ]

    return [
        level_op, 
        experience_op,
        next_level_experience_op,
    ]
```

Apply the buff and enjoy.