Persist attributes when character dies
========================

## Description

If you ever played a diablo like game, you surely know that when your character dies, 
you do not lose all your experience and attributes.

This is a common mechanic in many games, where players can respawn and keep their progress,
but they may lose some items (not our case, at least, not for this addon), gold or experience.

There's a simple way to do achieve this in your game.

> Note: this example is very barebones, but it should be enough to get you started and to give you an idea.

## The logic behind

First we need to understand that a player is not always a character in the game. 

Game engines like Unreal Engine usually split the player and the character into two different classes.

We are going to achieve the same thing in our game by creating a scene for the player, and another one (child of player) for the character.

Both hold an [`AttributeContainer`](../classes/AttributeContainer.md) node

Both share the same attributes, except for some health, mana, etc.

## Steps

1. Create a new scene called `Player` and add an [`AttributeContainer`](../classes/AttributeContainer.md) node to it.
2. Create a new scene called `PlayerCharacter` and add an [`AttributeContainer`](../classes/AttributeContainer.md) node to it.
3. Make `PlayerCharacter` a child of `Player`.
4. Create your attributes.
5. Create two different `AttributeSet` resources, one for the player and another for the character. They will likely share a lot of attributes.
6. Create an `AttributeBuff` which applies values to all the attributes of the player.