# Program 2 - Concentration Game

This repository contains my Program 2 project for CPSC 440 Game Programming.

## Description

This project is an Allegro version of Concentration, also known as Memory or Pairs. The player clicks two cards at a time to reveal hidden primitive shapes and tries to find all 12 matching pairs.

The game uses a 5x5 grid. The first 24 squares contain 12 randomly placed matching pairs, and the bottom-right square is used for status information.

## Features

- 5x5 Concentration game board
- 12 randomly placed matching pairs
- Mouse click selection
- Mouse coordinates converted into grid row and column positions
- Primitive shapes drawn inside the boxes
- First and second card selection tracking
- Matching cards are marked with a red X
- Non-matching cards stay visible for 5 seconds before hiding
- Bottom-right status box shows matched pairs and remaining pairs
- Win message displays when all pairs are matched

## Controls

- Left mouse click: Select a card
- Window close button: Exit the game

## Project Files

- `main.cpp` - Handles Allegro setup, mouse input, drawing, timer updates, and the main game loop
- `logic.h` - Defines the `GameLogic` class and its functions
- `logic.cpp` - Implements the game logic, random pair generation, card selection, matching, and non-match hiding

## How to Run

1. Open `ProgramAssignment#2toliver.sln` in Visual Studio.
2. Restore NuGet packages if Visual Studio asks.
3. Make sure Allegro is installed through NuGet.
4. Make sure the required Allegro add-ons are enabled:
   - Primitives Addon
   - Font Addon
5. Build and run the project.
6. Click two cards to reveal and compare them.

## Author

Christian Toliver
