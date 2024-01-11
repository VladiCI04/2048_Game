#include "leaderboard.h"

#include <iostream>
#include <fstream>
#include <string>

#include "deleteHeap.h"
#include "printConsole.h"
#include "gameEngine.h"

void addPlayerToLeaderboard(unsigned int** board, unsigned char* playerName, unsigned short const dimension) {
    std::string fileName = "Leaderboard" + std::to_string(dimension) + 'x' + std::to_string(dimension) + ".txt";
    std::ofstream outputFile(fileName, std::ios::app);

    // Check if the file is open
    if (!outputFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return;
    }

    unsigned int sumPlayerPoints = playerPoints(board, dimension);

    // Write data to the file
    outputFile << playerName << ' ' << sumPlayerPoints << std::endl;

    // Close the file
    outputFile.close();
}

unsigned int playerPoints(unsigned int** board, unsigned short dimension) {
    unsigned int sumPlayerPoints = 0;

    for (unsigned short row = 0; row < dimension; row++) {
        for (unsigned short col = 0; col < dimension; col++) {
            unsigned int element = board[row][col];

            if (element != 0) {
                sumPlayerPoints += element;
            }
        }
    }

    deleteHeap(board, dimension);

    return sumPlayerPoints;
}

void leaderboard() {
    std::cout << std::endl;
    unsigned short dimension;
    std::cout << "Enter Leaderboard dimension (Dimension should be between 4 and 10): ";
    std::cin >> dimension;

    if (dimension >= 4 && dimension <= 10) {
        printLeaderboard(dimension);
    }
    else {
        std::cout << "Wrong dimension! Dimension should be 4, 5, 6, 7, 8, 9 or 10!" << std::endl;
        leaderboard();
    }

    gameMenu();
}