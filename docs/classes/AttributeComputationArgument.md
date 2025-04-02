AttributeComputationArgument
=================

defined in `src/attribute.hpp`

## Description

This class is passed to a virtual method of the [`Attribute`](Attribute.md) class to compute the value of the attribute.

It contains the following properties:
- `attribute_container`: The attribute container that contains the attribute set.
- `buff`: The attribute buff used to compute the value of the attribute.
- `operated_value`: The currently operated value of the attribute by a buff.
- `runtime_attribute`: The runtime attribute instance that represents the current `Attribute`.

## Methods

- `get_parent_attributes`: returns an array of [`RuntimeAttribute`](RuntimeAttribute.md) that are parents of the current attribute.

[Back to classes](README.md)
