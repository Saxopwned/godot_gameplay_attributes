AttributeBuff
=================

defined in `src/attribute.hpp`

## Description

An `AttributeBuff` is a class which describes how an attribute is modified by it.

It can be used directly as a resource to modify attributes directly or 
can be extended to create more complex buffs.

> **Note:** Remember to instance those as a `.tres` resource if you need
> to squeeze the performance of your game.

## Methods

#### _applies_to

This method is used to gather the attributes that this buff applies to.

This function accepts one argument of type [`AttributeSet`](AttributeSet.md) and returns an array of [`Attribute`](Attribute.md).

You should override this function if:

- You want to apply the buff to a specific attribute.
- You want to gather more attributes to use them in the buff calculation.

```gdscript
func _applies_to() -> Array[Attribute]
```

#### _operate

This method is used to calculate all the operations applied to every attribute
in the array returned by `_applies_to`.

This function accepts these arguments:
- `values` of type `Array[float]` - The values of the attributes (as defined by `_applies_to`) to apply the buff to.
- `attribute_set` of type [`AttributeSet`](AttributeSet.md) - The attribute set to use to apply the buff.

This function must return an array of [`AttributeOperation`](AttributeOperation.md) which will be used to modify the attributes.

You should override this function if:

- You want to apply a specific operation to the attributes.
- You want to apply multiple operations to many attributes.
- You want to initialize the attributes in an `AttributeSet` with a specific value.

```gdscript
func _operate(values: Array[float], attribute_set: AttributeSet) -> Array[AttributeOperation]
```

[Back to classes](README.md)
