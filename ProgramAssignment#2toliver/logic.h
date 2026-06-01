#pragma once

class GameLogic
{
public:
    GameLogic();

    // Clears and prepares the board
    void reset();

    // Accessor functions used by the graphics code
    void hideNonMatch();
    int getShape(int row, int col);
    bool isRevealed(int row, int col);
    bool isMatched(int row, int col);
    bool selectCard(int row, int col);

    bool hasPendingNonMatch();
    int getMatchedPairs();
    int getRemainingPairs();
    bool isGameOver();

private:
    // Stores the hidden shape IDs for each card
    int pattern[5][5];

    // Tracks which cards are currently visible
    bool revealed[5][5];

    // Tracks which cards have already been matched
    bool matched[5][5];

    // Stores the first and second selected cards
    int firstRow;
    int firstCol;
    int secondRow;
    int secondCol;

    // 0 = no card selected, 1 = first card selected, 2 = second card selected
    int selectionCount;

    bool pendingNonMatch;

    // Tracks how many pairs have been found
    int matchedPairs;

    // Randomly fills the board with 12 matching pairs
    void createRandomBoard();

    // Compares the two selected cards
    void checkMatch();
};