# Welcome to the Arcade project!
Arcade is a gaming platform: a program that lets the user choose a game to play and keeps a register of
player scores

Authors:
* [Kattalin Ocariz](https://github.com/kocariz)
* Oriol Moles
* Arnau Espejo
# Project
To be able to deal with the elements of your gaming plateform at run-time, your graphics libraries and your games
must be implemented as dynamic libraries, loaded at runtime.
Each GUI available for the program must be used as a shared
library that will be loaded and used dynamically by the main
program.

[Documentation](https://github.com/kocariz/Arcade/blob/master/doc/arcadeDocumentation.pdf)
### Libraries
#### Graphic
* NCurses
* SDL2
* SFML
#### Games
* Nibbler
# Usage
```
./arcade ./lib/arcade_ncurses.so
```