# MosGame 

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

## License
Copyright (c) 2011, Sebastian Paaske Tørholm
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
Neither the name of MosGame nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
