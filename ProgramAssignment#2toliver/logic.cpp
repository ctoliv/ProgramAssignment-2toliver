#include "logic.h"
#include <cstdlib>
#include <ctime>

GameLogic::GameLogic()
{
    
    srand((unsigned int)time(0));
    reset();
}

// Initializes the board arrays
void GameLogic::reset()
{
    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            pattern[row][col] = 0;
            revealed[row][col] = false;
            matched[row][col] = false;
        }
    }
    createRandomBoard();
}

// Creates 12 pairs and places them randomly in the first 24 boxes
void GameLogic::createRandomBoard()
{
    int shapes[24];

    // Create 12 matching pairs using shape IDs 1 through 12
    for (int i = 0; i < 12; i++)
    {
        shapes[i * 2] = i + 1;
        shapes[i * 2 + 1] = i + 1;
    }

    // Shuffle the shape list
    for (int i = 0; i < 24; i++)
    {
        int randomIndex = rand() % 24;

        int temp = shapes[i];
        shapes[i] = shapes[randomIndex];
        shapes[randomIndex] = temp;
    }

    int index = 0;

    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            // Bottom-right box is only for status information
            if (row == 4 && col == 4)
            {
                pattern[row][col] = 0;
            }
            else
            {
                pattern[row][col] = shapes[index];
                index++;
            }
        }
    }
}

int GameLogic::getShape(int row, int col)
{
    return pattern[row][col];
}

bool GameLogic::isRevealed(int row, int col)
{
    return revealed[row][col];
}

bool GameLogic::isMatched(int row, int col)
{
    return matched[row][col];
}