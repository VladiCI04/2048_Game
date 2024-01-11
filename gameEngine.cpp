#include "gameEngine.h"

#include <iostream>

#include "printConsole.h"
#include "newGame.h"
#include "leaderboard.h"

void gameMenu() {
    // Print Game Menu
    printGameMenu();

    unsigned short answer;
    std::cin >> answer;

    if (answer == 1) {  // Start New Game
        startNewGame();
    }
    else if (answer == 2) {  // Leaderboard
        leaderboard();
    }
    else if (answer == 3) {  // Quit
        std::cout << std::endl << "Goodbye!" << std::endl << std::endl;
        return;
    }
    else {  // Wrong Input
        std::cout << std::endl;
        std::cout << "Wrong input! (Answer should be 1, 2 or 3)" << std::endl;
        return;
    }

    // Back In Game Menu
    gameMenu();
}