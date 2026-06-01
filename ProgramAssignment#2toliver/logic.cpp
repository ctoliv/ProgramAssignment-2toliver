#include "logic.h"
#include <cstdlib>
#include <ctime>

GameLogic::GameLogic()
{
    srand((unsigned int)time(0));
    reset();
}

void GameLogic::reset()
{
    firstRow = -1;
    firstCol = -1;
    secondRow = -1;
    secondCol = -1;
    selectionCount = 0;
    matchedPairs = 0;
    pendingNonMatch = false;

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

void GameLogic::createRandomBoard()
{
    int shapes[24];

    // Create 12 matching pairs.
    for (int i = 0; i < 12; i++)
    {
        shapes[i * 2] = i + 1;
        shapes[i * 2 + 1] = i + 1;
    }

    // Randomize the order of the pairs.
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
            // Reserve the bottom-right square for status information.
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

bool GameLogic::selectCard(int row, int col)
{
    // Rejects clicks outside the board.
    if (row < 0 || row >= 5 || col < 0 || col >= 5)
    {
        return false;
    }

    // Do not allow new selections while a non-match is still showing.
    if (pendingNonMatch)
    {
        return false;
    }

    // The bottom-right square displays status.
    if (row == 4 && col == 4)
    {
        return false;
    }

    // Do not allow already revealed or matched cards to be selected again.
    if (matched[row][col] || revealed[row][col])
    {
        return false;
    }

    revealed[row][col] = true;

    if (selectionCount == 0)
    {
        firstRow = row;
        firstCol = col;
        selectionCount = 1;
    }
    else if (selectionCount == 1)
    {
        secondRow = row;
        secondCol = col;
        selectionCount = 2;
        checkMatch();
    }

    return true;
}
// Checks whether the first and second selected cards match
void GameLogic::checkMatch()
{
    if (pattern[firstRow][firstCol] == pattern[secondRow][secondCol])
    {
        matched[firstRow][firstCol] = true;
        matched[secondRow][secondCol] = true;
        matchedPairs++;

        firstRow = -1;
        firstCol = -1;
        secondRow = -1;
        secondCol = -1;
        selectionCount = 0;
    }
    else
    {
        // Keep both cards visible until main hides them after 5 seconds.
        pendingNonMatch = true;
    }
}

void GameLogic::hideNonMatch()
{
    if (pendingNonMatch)
    {
        revealed[firstRow][firstCol] = false;
        revealed[secondRow][secondCol] = false;

        firstRow = -1;
        firstCol = -1;
        secondRow = -1;
        secondCol = -1;
        selectionCount = 0;

        pendingNonMatch = false;
    }
}

bool GameLogic::hasPendingNonMatch()
{
    return pendingNonMatch;
}

bool GameLogic::isGameOver()
{
    return matchedPairs == 12;
}

int GameLogic::getMatchedPairs()
{
    return matchedPairs;
}

int GameLogic::getRemainingPairs()
{
    return 12 - matchedPairs;
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