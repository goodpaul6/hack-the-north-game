# Hack the North Game Template

This is a game template built for the *Game Programming in C++* workshop at
Hack the North 2021.

## Thoughts

A game typically consists of systems that operate at different levels of abstraction
relative to the game. There are low level systems like windowing, input and rendering.
These have practically nothing to do with the game itself.

Then we have mid-level systems that provide the structure to express the logic of the
game. Note that these systems do not model the gameplay logic themselves. Examples
include a physics engine, sprite animation, and entity system.

Lastly, we have the high-level systems. These are systems directly related to the game.
For example, a weapon system. Often times, the line between mid and high level 
systems is blurred (e.g. for this game we are implementing physics using the entity
system).

## Features

- [x] Cross-platform windowing and input
- [x] Image loading and display
- [x] Entity system
- [x] Simplified 2D physics
- [x] Runtime tweaker system
- [x] Flipping images
- [x] Flipbook animation
- [ ] Entity factory
- [ ] Bullets
- [ ] Tilemaps
- [ ] Audio playback
- [ ] Image-based level loading
