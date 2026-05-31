#include "logic.h"

GameLogic::GameLogic()
{
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