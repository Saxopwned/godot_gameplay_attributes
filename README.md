Godot Gameplay Attributes
=========================

![GGA logo](godot/icon.svg)

> (Part of [Godot Gameplay Systems](https://github.com/OctoD/godot-gameplay-systems))

[discord server here](https://discord.gg/meA6pDTXpr)

# Installation

## Using the AssetLib

1. Open the Godot editor.
2. Navigate to the AssetLib tab.
3. Search for "Gameplay Attributes".
4. Install and enjoy!

## Using the GitHub repository

1. Download the latest version of the addon from the [release page](https://github.com/OctoD/godot_gameplay_attributes/releases).
2. Extract the contents of the zip file into your project's `addons` folder.
3. Enjoy!

## Using Git

Clone the repository into your project's `addons` folder:

```bash
git clone --recurse-submodules
```

Build the project:

```bash
scons platform=windows # or linux, macos etc
```
Enjoy!

# Usage

The addon provides a set of nodes and resources that can be used to define gameplay attributes. These nodes can be added to any scene in your game to define the attributes of the objects in that scene.

## How does it work and why

This addon works
using Godot's custom resources as attributes.

Each `Attribute` is a custom resource
that defines a single attribute
that can be contained
by an `AttributeSet` resource.
The choice of custom resources is due to Godot's performance
on handling many of them,
by giving at the same time the possibility
to inherit their base class
to create custom attributes.

An `Attribute` has a name,
an initial value,
and optionally it can define
how it derives from other attributes
and how other attributes can apply constraints to it.

The best way
to define your attributes is
to create your own custom resources as scripts
that inherit from the `Attribute` base class.
This way,
you can define your attribute
and use it later in your attribute sets.
Otherwise,
a normal `Attribute` resource can be used
if you do not need anything fancy.

An `AttributeSet` is a set of predefined attributes that can be used to define the attributes of an object in the game, like a character, an enemy, or any other object that has attributes.

Each `AttributeSet` has to be used by an `AttributeContainer` node, that is a node that contains the attributes of an object in the game. 

For each `Attribute` in the `AttributeSet`, the `AttributeContainer` will create a `RuntimeAttribute` that will hold the current value of the attribute, the reference to the `Attribute` resource, and an array to some `RuntimeBuff` that will modify the value of the attribute.

A `RuntimeBuff` is the representation of an `AttributeBuff` resource that will modify the value of an attribute. It has a value that will be added/subtracted/multiply/divided to the attribute value, and a duration that will define how long the buff will last (if 0, the buff will last forever).

### Derived attributes

Derived attributes are attributes that are calculated based on other attributes. For example, the health of a character can be calculated based on the strength and constitution attributes of the character, or mana can be calculated based on intelligence and wisdom.

To define a derived attribute,
you must create scripts that inherit from `Attribute` base class. 

Example:

```gdscript
class_name HealthDerivedAttribute extends Attribute


const ATTRIBUTE_NAME = "Health"


func _init(_attribute_name = ATTRIBUTE_NAME) -> void:
	attribute_name = _attribute_name


func _get_buffed_value(values: PackedFloat32Array) -> float:
	return values[0] * 6


func _derived_from(attribute_set: AttributeSet) -> Array[AttributeBase]:
	return [attribute_set.find_by_name(ConstitutionAttribute.ATTRIBUTE_NAME)]
	
	
func _get_initial_value(values: PackedFloat32Array) -> float:
	return values[0] * 6
```

You must override the `_get_buffed_value` method to define how the attribute value is calculated based on the values of the attributes that it depends on. You must override the `_derived_from` method to define which attributes the derived attribute depends on and the `_get_initial_value` method to define the initial value of the attribute.

## Attributes constraints

Some attributes
(like health,
mana,
stamina,
etc.)
could potentially have constraints,
like a maximum value,
a minimum value,
or a value
that can be calculated based on other attributes.

To achieve this is quite straightforward. You have to create a script that inherits from `Attribute` base class as your main attribute, one for the minimum value, one for the maximum value, and one for the derived value.

Example:

#### Defining the minimum and maximum constraints

The minimum health attribute should look similar to this:

```gdscript
class_name MinHealthAttribute
extends Attribute

const ATTRIBUTE_NAME := "MinHealthAttribute"

func _init(_attribute_name := ATTRIBUTE_NAME):
	attribute_name = _attribute_name


func _constrained_by(attribute_set: AttributeSet) -> Array[AttributeBase]:
	return [
		attribute_set.find_by_name(MaxHealthAttribute.ATTRIBUTE_NAME)
	]
	
	
func _get_constrained_value(buffed_value: float, buffed_values: PackedFloat32Array, previous_values: PackedFloat32Array) -> float:
	return minf(buffed_value, buffed_values[0]) # we don't want to exceed the value of the MaxHealthAttribute
```

While the maximum health attribute should look like this:

```gdscript
class_name MaxHealthAttribute
extends Attribute

const ATTRIBUTE_NAME := "MaxHealthAttribute"

func _init(_attribute_name := ATTRIBUTE_NAME):
	attribute_name = _attribute_name


func _constrained_by(attribute_set: AttributeSet) -> Array[AttributeBase]:
	return [
		attribute_set.find_by_name(MinHealthConstraintAttribute.ATTRIBUTE_NAME)
	]
	
	
func _get_constrained_value(buffed_value: float, buffed_values: PackedFloat32Array, previous_values: PackedFloat32Array) -> float:
	return maxf(buffed_value, buffed_values[0])
```

#### Applying the constraints to the main attribute

```gdscript
class_name Health
extends Attribute

const ATTRIBUTE_NAME := "Health"

func _init(_attribute_name := ATTRIBUTE_NAME):
	attribute_name = _attribute_name
	
	
func _constrained_by(attribute_set: AttributeSet) -> Array[AttributeBase]:
	return [
		attribute_set.find_by_name(MinHealthAttribute.ATTRIBUTE_NAME),
		attribute_set.find_by_name(MaxHealthAttribute.ATTRIBUTE_NAME),
	]
	
	
func _get_constrained_value(buffed_value: float, buffed_values: PackedFloat32Array, previous_values: PackedFloat32Array) -> float:
	return clampf(buffed_value, buffed_values[0], buffed_values[1]) # tada!
```

## Custom attribute buff/debuff

You can create your own custom attribute buff/debuff by creating a script that inherits from `AttributeBuff` base class.

This class provides two virtuals you have to implement: 

- `_applies_to(attribute_set: AttributeSet) -> Array[AttributeBase]` that will define to which attribute the buff will be applied.
- `_operate(values: Array[float], attribute_set: AttributeSet) -> Array[AttributeOperation]` that will define how the buff will modify the attributes.
  - The `values` parameter is an array subscribed attributes' buffed values (at runtime) that the buff will use.

You can find an example [here](godot/examples/character_levelling_and_experience/experience_buff.gd)

This is good for mechanics
where there is some kind of buff/debuff mitigation,
like 
- a shield that will absorb some damage before it reaches the health of a character
- a movement speed that will be reduced by a debuff.

## How to use this addon programmatically

Here is a short example

```gdscript
extends Node
# in this example, we will create a simple attribute that will represent the health of a character, which
# can be buffed or debuffed programmatically

const ATTRIBUTE_NAME = "health"


var attribute_container := AttributeContainer.new() 


func _ready():
	# create the attribute
	var health_attribute = Attribute.new()
	health_attribute.attribute_name = ATTRIBUTE_NAME
	health_attribute.initial_value = 100

	attribute_container.attribute_set = AttributeSet.new()
	attribute_container.attribute_set.add_attribute(health_attribute)

	add_child(attribute_container)

	# add a buff to the attribute
	var buff = AttributeBuff.new()
	buff.attribute_name = ATTRIBUTE_NAME
	buff.operation = AttributeOperation.add(10)
	
	var debuff = AttributeBuff.new()
	debuff.attribute_name = ATTRIBUTE_NAME
	debuff.operation = AttributeOperation.subtract(10)

	attribute_container.apply_buff(debuff)

	print(attribute_container.get_attribute_by_name(ATTRIBUTE_NAME).get_buffed_value()) # 90

	attribute_container.apply_buff(debuff)

	print(attribute_container.get_attribute_by_name(ATTRIBUTE_NAME).get_buffed_value()) # 80

	attribute_container.apply_buff(buff)

	print(attribute_container.get_attribute_by_name(ATTRIBUTE_NAME).get_buffed_value()) # 90

	attribute_container.apply_buff(buff)

	print(attribute_container.get_attribute_by_name(ATTRIBUTE_NAME).get_buffed_value()) # 100
```

## Other examples

You can find other examples in the `godot/examples` folder of this repository.

## Contributing

If you want to contribute to this project, please read the [CONTRIBUTING.md](CONTRIBUTING.md) file.

Don't be shy, this project is open to any kind of contribution!

## License

[MIT](LICENSE)
