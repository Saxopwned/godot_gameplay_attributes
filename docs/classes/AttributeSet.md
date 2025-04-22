AttributeContainer
=================

defined in `../../src/attribute.hpp`

## Description

This class is a collection of [`Attribute`](Attribute.md) instances (or subclasses) 
that can be used to manage a set of attributes in a single object. 
It provides methods to add, remove, and retrieve attributes.

> Like for the Attribute class, it's a good thing to use instances of this class as 
> resources (.tres). 

## Members

- `attributes`: an array of attributes.

## Methods

> Although the class has these methods you will probably not use them directly or need to.

- add_attribute: adds an attribute to the set
- add_attributes: adds multiple attributes to the set
- find_by_classname: finds an attribute by its class name
- find_by_name: finds an attribute by its name
- get_attributes_names: returns a list of all attribute names
- get_set_name: returns the name of the set
- has_attribute: checks if an attribute exists in the set
- remove_attribute: removes an attribute from the set
- remove_attributes: removes multiple attributes from the set
- set_set_name: sets the name of the set

[Back to classes](README.md)
