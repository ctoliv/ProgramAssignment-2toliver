#pragma once

class GameLogic
{
public:
    GameLogic();

    // Clears and prepares the board
    void reset();

    // Accessor functions used by the graphics code
    int getShape(int row, int col);
    bool isRevealed(int row, int col);
    bool isMatched(int row, int col);
    bool selectCard(int row, int col);

private:
    // Stores the hidden shape IDs for each card
    int pattern[5][5];

    // Tracks which cards are currently visible
    bool revealed[5][5];

    // Tracks which cards have already been matched
    bool matched[5][5];

    // Randomly fills the board with 12 matching pairs
    void createRandomBoard();
};