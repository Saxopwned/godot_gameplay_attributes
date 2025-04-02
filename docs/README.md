Godot Gameplay Attributes
=========================

Welcome!

Godot Gameplay Attributes is a Godot addon which adds a system to manage
attributes like health, mana, stamina, ammo etc. in a game.

It is designed to be as easy as possible without compromising on flexibility.

Technically speaking, it is a GDExtension (written in C++ 17) which provides:

- one node to manage attributes
- one resource to define attributes
    - one object (RefCounted) which stores an attribute value
- one resource to define attribute modifiers (buffs)
  -  one object (RefCounted) which stores a modifier value and lifetime

#### How does it work?

This addon is quite simple. 

The key concepts are:

- define as many attributes as you want.
- organize them in attributes sets (like for player, enemies, weapons etc.).
- give those sets to an attribute container to make them work.

One node which needs attributes, can have one or more attribute containers as you need.

#### Table of Contents

- [Installation](install.md) aka how to install and set up the addon
- [Classes](classes/README.md) aka the classes provided by the addon
- [how tos](how-to/README.md) aka different use cases and examples

#### Demo

A demo project is included in the repository. 
You can find it in the `godot` folder.

#### License

This addon is licensed under the MIT license. 

See the [LICENSE](../LICENSE) file for more information.

