#include "newGame.h"

#include <iostream>

#include "printConsole.h"
#include "gameEngine.h"
#include "programConstants.h"
#include "board.h"
#include "leaderboard.h"
#include "moves.h"

void startNewGame() {
    // Start New Game Title
    printStartNewGameTitle();

    // Enter Nickname
    std::cout << "Enter your nickname: ";
    unsigned char playerName[MAX_INPUT_SIZE];
    std::cin >> playerName;

    // Enter Dimention
    unsigned short dimension = enterDimension();

    // Board
    unsigned int moveCount = 0;
    unsigned int** board = createBoard(dimension);
    addNumToBoard(board, moveCount, dimension);
    printBoard(board, dimension);
    playGame(board, dimension, moveCount);
    addPlayerToLeaderboard(board, playerName, dimension);
    gameMenu();
}

unsigned short enterDimension() {
    std::cout << "Enter dimension (Dimention should be between 4 and 10): ";
    unsigned short dimension;
    std::cin >> dimension;

    if (dimension < 4 || dimension > 10) {
        std::cout << "Wrong dimention! (Dimention should be between 4 and 10)";
        std::cout << std::endl;

        gameMenu();
    }

    return dimension;
}

void playGame(unsigned int** board, unsigned short const dimension, unsigned int& moveCount) {
    bool isWin = false;

    while (!isBoardFull(board, dimension)) {
        std::cout << std::endl;
        std::cout << "Enter diretction (Direction should be w, a, s or d): " << std::endl;
        unsigned char direction;
        std::cin >> direction;

        if (direction == 'w') {
            isWin = moveUp(board, dimension);
        }
        else if (direction == 'a') {
            isWin = moveLeft(board, dimension);
        }
        else if (direction == 's') {
            isWin = moveDown(board, dimension);
        }
        else if (direction == 'd') {
            isWin = moveRight(board, dimension);
        }
        else {
            std::cout << std::endl;
            std::cout << "Wrong direction! (Direction should be w, a, s or d): " << std::endl;
            return;
        }

        if (isWin) {
            break;
        }

        moveCount++;
        addNumToBoard(board, moveCount, dimension);
        printBoard(board, dimension);
    }

    if (isWin) {
        std::cout << "You win!" << std::endl;
    }
    else {
        std::cout << "You lose! Try again!" << std::endl;
    }
}