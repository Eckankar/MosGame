# MosGame 

[![Build Status](https://travis-ci.org/Eckankar/MosGame.svg?branch=master)](https://travis-ci.org/Eckankar/MosGame)

An attempt at making a game library for Moscow ML.

It attempts to replicate the style of PyGame.

Note, this is very much alpha at this point, and the names and functionality is sure to be changed a lot as the library gets expanded.
In short, don't rely on the interfaces staying the same until they're announced to be so.

## Requirements

In order to compile the library, you need:

* [Moscow ML](http://github.com/kfl/mosml)
* [SDL](http://www.libsdl.org/)
* [SDL_gfx](http://www.ferzkopp.net/joomla/content/view/19/14/)
* [SDL_image](http://www.libsdl.org/projects/SDL_image/)

## Compilation + installation

If you're running a unix-based system:

1. Check out a copy of the code, using the command `git clone git://github.com/Eckankar/MosGame.git`.
2. Inside the MosGame directory, edit the `Makefile`, such that all paths are correct for your system.
3. Write `make all` to build the library.
4. Write `sudo make install` to install the library.
