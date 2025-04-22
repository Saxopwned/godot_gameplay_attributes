Godot Gameplay Attributes
=========================

![GGA logo](godot/icon.svg)

> (Part of [Godot Gameplay Systems](https://github.com/OctoD/godot-gameplay-systems))

[discord server here](https://discord.gg/meA6pDTXpr)

# Installation

- Open the asset store
- Search for "Gameplay Attributes"
- Install and enjoy!

or 

follow the [instructions here](./docs/install.md)

# Docs

Documentation is available in the [docs folder](./docs/README.md).

# Usage

The addon provides a set of resources and a node that can be used to 
define gameplay attributes with ease and flexibility. 
These nodes can be added to any scene in your game to define the 
attributes of the objects in that scene.

# How does it work?

- Attributes define, well, attributes.
  - They can also be used to define derived attributes (attributes that are calculated from other attributes).
- Attribute sets contain the attributes definitions (aka, they describe which attribute an attribute container has).
  - Just use them as they, 99% of the time you will not need to customize them.
- Attribute containers expose attributes life-cycle, values and signals to the node-tree.
  - Same as above, just use them as they are and you will be fine.
- Attribute buffs are used to modify directly (or transiently) the attributes values.
  - Buffs can be instantly applied, have a duration, can be stacked, can be unique, can be removed if transient, etc.
  - They can also be used to modify multiple attributes at once by overloading a couple of methods.

# Comparing G.G.A. with the popular G.A.S. from Unreal Engine

- GGA is fully decoupled from an ability system (you can find it [here](https://github.com/OctoD/godot-gameplay-abilities)), 
  while GAS is mostly coupled to it (if you need only one of the two things, you still have to deal with the other).
- You can define the attributes you want to use inside the editor (or by scripting, or with c++ or your favourite language) 
  , while in GAS you have to define them in C++ first.
- GAS does not provide an easy way to define derived attributes, you need to use calculation classes inside GameplayEffects.
- GGA is not networked by default, but you can easily add it to your game (with a couple of RPCs), giving you 
  the flexibility to choose if and how to handle the replication for attributes.
- GGA can be used in any game, while GAS is mostly used in RPGs and shooters. You want to build a rts with deck-building features? 
  Go on, the whole system does not hold you back.
- A scene can have multiple attribute containers, while in GAS you have to use a single attribute set for each actor 
  (not really a feature, but if you need it you can use it).
- It's dead simple and consistent, you need to learn a few concepts, and you are ready to go. 
  You can use it in your game without having to learn a whole new system.

> tools not rules.

## Contributing

If you want to contribute to this project, please read the [CONTRIBUTING.md](CONTRIBUTING.md) file.

Don't be shy, this project is open to any kind of contribution!

## License

[MIT](LICENSE)
