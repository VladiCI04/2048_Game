#include "board.h"
#include "randomise.h"

unsigned int** createBoard(unsigned short const dimension) {
    // Allocate memory for an array of pointers (rows)
    unsigned int** board = new unsigned int* [dimension];

    // Allocate memory for each row
    for (unsigned short row = 0; row < dimension; row++) {
        board[row] = new unsigned int[dimension];
    }

    for (unsigned short row = 0; row < dimension; row++) {
        for (unsigned short col = 0; col < dimension; col++) {
            board[row][col] = 0;
        }
    }

    return board;
}

void addNumToBoard(unsigned int** board, unsigned int const moveCount, unsigned short const dimension) {
    unsigned short randRow = randomIndexGenerator(dimension);
    unsigned short randCol = randomIndexGenerator(dimension);

    if (board[randRow][randCol] == 0) {
        unsigned short randNum = randomNumberGenerator(moveCount);
        board[randRow][randCol] = randNum;
    }
    else {
        addNumToBoard(board, moveCount, dimension);
    }
}

bool isBoardFull(unsigned int** board, unsigned short const dimension) {
    for (unsigned short row = 0; row < dimension; row++) {
        for (unsigned short col = 0; col < dimension; col++) {
            unsigned int element = board[row][col];

            if (element == 0) {
                return false;
            }
        }
    }

    return true;
}