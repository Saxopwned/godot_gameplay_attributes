Attribute
=================

defined in `src/attribute.hpp`

## Description

The `Attribute` class is the base class for everything here.

Think about it as a "template" for a real attribute.

An `Attribute` class, if extended, can be used to describe:

- How its own value is calculated.
- Its own dependencies on other attributes (if the attribute derives from others).

> Note: if your game has many attributes, it's highly recommended 
> to instance your `Attribute` scripts as resources (.tres). This will
> prevent instancing too much resources in memory and will allow you to
> use the same attribute in multiple places.

## Methods

### _compute_value

An optional virtual method used to compute the value of the attribute.

You should override this function if:

- you want to clamp the value of the attribute.
- you want to compute the value of the attribute based on other attributes
  (e.g. a health attribute could depend on minimum and maximum health).

This function accepts one argument of type [`AttributeComputationArgument`](AttributeComputationArgument.md).

```gdscript
func _compute_value(argument: AttributeComputationArgument) -> float
```

### _derived_from

An optional virtual method used to tell the [`AttributeContainer`](AttributeContainer.md) if the attribute is derived from another attribute.

This will be used to link the other attributes ([`RuntimeAttribute`](RuntimeAttribute.md)) to the derived attribute.

You should override this function if:

- you want to derive the attribute from other attributes.

This function accepts one argument of type [`AttributeSet`](AttributeSet.md) and returns an array of [`Attribute`](Attribute.md).

```gdscript
func _derived_from(attribute_set: AttributeSet) -> Array[Attribute]
```

[Back to classes](README.md)
