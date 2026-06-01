#pragma once

class GameLogic
{
public:
    GameLogic();

    void reset();
    bool selectCard(int row, int col);
    void hideNonMatch();

    int getShape(int row, int col);
    bool isRevealed(int row, int col);
    bool isMatched(int row, int col);

    bool hasPendingNonMatch();
    bool isGameOver();

    int getMatchedPairs();
    int getRemainingPairs();

private:
    // Board state arrays.
    int pattern[5][5];
    bool revealed[5][5];
    bool matched[5][5];

    // First and second selected card locations.
    int firstRow;
    int firstCol;
    int secondRow;
    int secondCol;

    // Tracks how many cards are currently selected.
    int selectionCount;

    // Used when two selected cards do not match.
    bool pendingNonMatch;

    // Tracks successful matches.
    int matchedPairs;

    void createRandomBoard();
    void checkMatch();
};