# DodgeEm
Dodge Em  is a 2D game build in C++. It uses OpenGL for graphics .This game is inspired by 1980's Atari Game Dodge' Em. It also contains additional features like a cheat code system and a leader board.

This a small project that i undertook when i just started programming so there is a considerable room for improvement.Hope you enjoy playing it!
## Installation
To run these , you will need a C++ compiler and a linux distribution with OpenGL installed. If you dont have a C++ compiler and Open GL installed. Simply run the following terminal command:
```
make install
```
This will install G++ compiler and the necessary libaries for running this game.
## Running the Game
Now to run this game simply run
```
make run
```
## Editing / Modifying 
If you modified the code and wish to run the new version simply run:
```
make all
```
This will create a new binary for the game so that the Run command will run the new version of game.

## Activating Cheat system
The game does have a help screen to guide you through the game but details about the cheat system are intentionally missing there.
To activate the secret menu for cheats . Start a game and then go into pause menu by pressing <kbd>P</kbd>. While in the menu press the arrow keys in the following order:

<kbd>→</kbd><kbd>→</kbd><kbd>←</kbd><kbd>←</kbd><kbd>←</kbd>

This will open up a pin screen. Enter 1234 as the pin and you will enter the secret menu. There you can select from a bunch of cheat options to win the game.
