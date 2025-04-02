RuntimeAttribute
=================

defined in `src/attribute.hpp`

## Description

It's the runtime representation of an [Attribute](Attribute.md) in the C++ code. 
It is used to store the attribute's value and buffs (or debuffs) at runtime.

You are not supposed to build this class yourself. 
It is built by the [AttributeContainer](AttributeContainer.md) class.

## Members

- `attribute`: it's the [Attribute](Attribute.md) this runtime attribute is built from.
- `buffs`: it's an array of [AttributeBuff](AttributeBuff.md) objects.
- `value`: the current value of the attribute.

## Signals

- `attribute_changed`: emitted when the attribute value changes.
- `buff_added`: emitted when a buff is added to the attribute.
- `buff_removed`: emitted when a buff is removed from the attribute.
- `buff_time_updated`: emitted when a buff time is updated.
- `buffs_cleared`: emitted when all buffs are cleared from the attribute.

## Methods

- `get_buffed_value`: gets the value of the attribute after applying buffs.
- `get_buffs`: gets the buffs applied to the attribute.
- ~~`get_derived_from`~~: deprecated. Use `get_parent_runtime_attributes` instead.
- `get_parent_runtime_attributes`: returns the attributes this runtime attribute is derived from. 
- `get_value`: gets the current value of the attribute.
- `has_ongoing_buffs`: checks if the attribute has any ongoing transient buffs.

[Back to classes](README.md)
