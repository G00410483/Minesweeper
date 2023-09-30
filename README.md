# Minesweeper
This is a simple implementation of the classic game Mine Sweeper in C. The game can be played in either single-player or multiplayer mode.

How to Play
Compile and run the code.
You will be presented with a menu:
Select 1 for a new game.
Select 2 to load a saved game (Note: Loading is not fully implemented in this code).
Game Modes
Single Player: In this mode, you play alone, and your goal is to reveal all non-mined squares without stepping on a mine.
Multiplayer: In this mode, two players take turns playing. The player with the highest score wins. Your score increases by 10 for each non-mined square you reveal.
Gameplay
In both modes, you enter the row and column numbers to uncover squares.
If you uncover a square containing a mine, the game ends, and you lose.
In single-player mode, your goal is to score 100 points by revealing non-mined squares.
In multiplayer mode, both players take turns revealing squares, and the game ends when either player reaches 80 points.
The player with the highest score wins in multiplayer mode.
low you to save and load your progress. However, the loading feature is not working correctly.
Implementation Notes
The game is played on an 8x8 grid, and there are 10 random mines placed on the grid.
The code utilizes text files to save and load the game state (output, mines, and game mode).
The game output is displayed in the console, with numbers indicating the number of mines adjacent to each square.
Enjoy playing this basic version of Mine Sweeper!
