#include "printConsole.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
#include <string>

// Program Constants
#include "programConstants.h"

void printGameMenu() {
    std::cout << "---------------------" << std::endl;
    std::cout << "| 2048 Game         |" << std::endl;
    std::cout << "|                   |" << std::endl;
    std::cout << "| 1. Start New Game |" << std::endl;
    std::cout << "| 2. Leaderboard    |" << std::endl;
    std::cout << "| 3. Quit           |" << std::endl;
    std::cout << "---------------------" << std::endl;
    std::cout << "Your Answer (Answer should be 1, 2 or 3): ";
}

void printStartNewGameTitle() {
    std::cout << std::endl;
    std::cout << "-------------------2048 Game-----------------" << std::endl;
}

void printBoard(unsigned int** board, unsigned short const dimension) {
    printUpDashes(dimension);

    printBody(board, dimension);

    printDownDashes(dimension);
}


void printUpDashes(unsigned short const dimension) {
    unsigned short dashes = dimension * 3;

    for (unsigned short dash = 0; dash < dashes; dash++) {
        std::cout << '-';
    }
    std::cout << "Board";

    for (unsigned short dash = 0; dash < dashes; dash++) {
        std::cout << '-';
    }
    std::cout << std::endl << std::endl;
}

void printBody(unsigned int** board, unsigned short const dimension) {
    for (unsigned short row = 0; row < dimension; row++) {
        for (unsigned short col = 0; col < dimension; col++) {
            std::cout << std::setw(6) << board[row][col];
        }
        std::cout << std::endl << std::endl;
    }
}

void printDownDashes(unsigned short const dimension) {
    unsigned short dashes = dimension * 7;

    for (unsigned short dash = 0; dash < dashes; dash++) {
        std::cout << '-';
    }
    std::cout << std::endl << std::endl;
}

void printLeaderboard(unsigned short const dimension) {
    std::string fileName = "Leaderboard" + std::to_string(dimension) + 'x' + std::to_string(dimension) + ".txt";
    std::ifstream inputFile(fileName);

    // Check if the file is open
    if (!inputFile.is_open()) {
        std::cerr << "Leaderboard is empty." << std::endl;
        return;
    }

    std::vector<unsigned int> numbers;
    std::vector<unsigned int> numbers2;
    std::vector<std::string> names;
    char line[MAX_INPUT_SIZE + 1];
    while (inputFile.getline(line, MAX_INPUT_SIZE)) {
        unsigned int i = 0;
        if (line[i] == '\0') {
            break;
        }

        std::string name;
        while (line[i] != ' ') {
            name += line[i];
            i++;
        }
        i++;
        names.push_back(name);

        unsigned int number = 0;
        while (line[i] != '\0') {
            number = (number * 10) + (line[i] - '0');
            i++;
        }

        numbers.push_back(number);
        numbers2.push_back(number);
    }

    // Sort the vector
    std::sort(numbers2.begin(), numbers2.end());

    size_t index2 = numbers2.size() - 1;
    unsigned short count = 1;
    std::cout << std::endl;
    std::cout << "----------------------Leaderboard----------------------" << std::endl;
    // Read and print each line from the file
    while (count < 6 && !numbers2.empty() && index2 < numbers.size()) {
        unsigned short index = 0;

        while (true) {
            if (numbers2[index2] == numbers[index]) {
                std::cout << "| " << count << ". " << names[index] << " - " << numbers[index] << std::endl;
                numbers[index] = 0;
                break;
            }

            index++;
        }

        index2--;
        count++;
    }
    std::cout << "-------------------------------------------------------" << std::endl;
    std::cout << std::endl;

    // Close the file
    inputFile.close();
}