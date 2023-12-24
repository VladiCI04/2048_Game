#include <iostream>
#include <random>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

// Program Consts
short const MAX_INPUT_SIZE = 100;

// Global Variables
char LeaderboardName1[] = "Unknown"; // Leaderboard1
size_t LeaderboardPoints1 = 0;

char LeaderboardName2[] = "Unknown"; // Leaderboard2
size_t LeaderboardPoints2 = 0;

char LeaderboardName3[] = "Unknown"; // Leaderboard3
size_t LeaderboardPoints3 = 0;

char LeaderboardName4[] = "Unknown"; // Leaderboard4
size_t LeaderboardPoints4 = 0;

char LeaderboardName5[] = "Unknown"; // Leaderboard5
size_t LeaderboardPoints5 = 0;

// Function Declaration
void gameMenu();
void printGameMenu();
void startNewGame();
void printStartNewGameTitle();
unsigned short enterDimension();
unsigned int** createBoard(unsigned short const dimension);
void addNumToBoard(unsigned int** board, unsigned int const moveCount, unsigned short const dimension);
unsigned short randomIndexGenerator(unsigned short const dimension);
unsigned short randomNumberGenerator(unsigned int const moveCount);
void printBoard(unsigned int** board, unsigned short dimension);
void playGame(unsigned int** board, unsigned short const dimension, unsigned int& moveCount);
bool isBoardFull(unsigned int** board, unsigned short const dimension);
bool moveUp(unsigned int** board, unsigned short const dimension);
bool moveLeft(unsigned int** board, unsigned short const dimension);
bool moveDown(unsigned int** board, unsigned short const dimension);
bool moveRight(unsigned int** board, unsigned short const dimension);
void addPlayerToLeaderboard(unsigned const int** const board, unsigned const char* const playerName, unsigned short const dimension);
unsigned int playerPoints(unsigned const int** const board, unsigned short dimension);
void leaderboard();
void printLeaderboard(unsigned short const dimension);

int main()
{
    // Start Game
    gameMenu();
}

void gameMenu() {
    // Print Game Menu
    printGameMenu();

    unsigned short answer;
    std::cin >> answer;

    if (answer == 1 ) {  // Start New Game
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
        std::cout << "Wrong input! (Answer should be 1, 2 or 3)";
    }

    // Back In Game Menu
    gameMenu();
}

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
}

void printStartNewGameTitle() {
    std::cout << std::endl;
    std::cout << "-------------------2048 Game-----------------" << std::endl;
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

unsigned int** createBoard(unsigned short const dimension) {
    // Allocate memory for an array of pointers (rows)
    unsigned int** board = new unsigned int*[dimension];

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

unsigned short randomIndexGenerator(unsigned short dimension) {
    // Create a random number engine
    std::random_device random;
    std::mt19937 generator(random());

    // Define a distribution (e.g., uniform distribution between 0 and 9)
    std::uniform_int_distribution<unsigned short> distribution(0, 9);

    // Generate a random number
    unsigned short randomNumber = distribution(generator);
    while (randomNumber >= dimension) {
        randomNumber = distribution(generator);
    }

    return randomNumber;
}

unsigned short randomNumberGenerator(unsigned int moveCount) {
    // Create a random number engine
    std::random_device random;
    std::mt19937 generator(random());

    // Define a distribution (e.g., uniform distribution between 1 and 3)
    std::uniform_int_distribution<unsigned short> distribution(1, 3);

    // Generate a random number
    unsigned short randomNumber = distribution(generator);
    unsigned short num = 0;
    if (randomNumber == 1) {
        num = 2;
    }
    else if (randomNumber == 2) {
        num = 4;
    }
    else if (randomNumber == 3) {
        num = 8;
    }

    return num;
}

void printBoard(unsigned int** board, unsigned short dimension) {
    if (dimension == 4) {
        std::cout << "------------Board-----------" << std::endl << std::endl;
        for (unsigned short row = 0; row < dimension; row++) {
            for (unsigned short col = 0; col < dimension; col++) {
                std::cout << std::setw(6) << board[row][col] << std::setw(6);
            }
            std::cout << std::endl << std::endl;
        }
        std::cout << "----------------------------" << std::endl;
    }
    else if (dimension == 5) {
        std::cout << "---------------Board--------------" << std::endl << std::endl;
        for (unsigned short row = 0; row < dimension; row++) {
            for (unsigned short col = 0; col < dimension; col++) {
                std::cout << std::setw(6) << board[row][col] << std::setw(6);
            }
            std::cout << std::endl << std::endl;
        }
        std::cout << "----------------------------------" << std::endl;
    }
    else if (dimension == 6) {
        std::cout << "------------------Board-----------------" << std::endl << std::endl;
        for (unsigned short row = 0; row < dimension; row++) {
            for (unsigned short col = 0; col < dimension; col++) {
                std::cout << std::setw(6) << board[row][col] << std::setw(6);
            }
            std::cout << std::endl << std::endl;
        }
        std::cout << "----------------------------------------" << std::endl;    
    }
    else if (dimension == 7) {
        std::cout << "---------------------Board--------------------" << std::endl << std::endl;
        for (unsigned short row = 0; row < dimension; row++) {
            for (unsigned short col = 0; col < dimension; col++) {
                std::cout << std::setw(6) << board[row][col] << std::setw(6);
            }
            std::cout << std::endl << std::endl;
        }
        std::cout << "----------------------------------------------" << std::endl;
        }
    else if (dimension == 8) {
        std::cout << "------------------------Board-----------------------" << std::endl << std::endl;
        for (unsigned short row = 0; row < dimension; row++) {
            for (unsigned short col = 0; col < dimension; col++) {
                std::cout << std::setw(6) << board[row][col] << std::setw(6);
            }
            std::cout << std::endl << std::endl;
        }
        std::cout << "----------------------------------------------------" << std::endl;
    }
    else if (dimension == 9) {
        std::cout << "---------------------------Board--------------------------" << std::endl << std::endl;
        for (unsigned short row = 0; row < dimension; row++) {
            for (unsigned short col = 0; col < dimension; col++) {
                std::cout << std::setw(6) << board[row][col] << std::setw(6);
            }
            std::cout << std::endl << std::endl;
        }
        std::cout << "----------------------------------------------------------" << std::endl;
    }
    else if (dimension == 10) {
        std::cout << "------------------------------Board-----------------------------" << std::endl << std::endl;
        for (unsigned short row = 0; row < dimension; row++) {
            for (unsigned short col = 0; col < dimension; col++) {
                std::cout << std::setw(6) << board[row][col] << std::setw(6);
            }
            std::cout << std::endl << std::endl;
        }
        std::cout << "----------------------------------------------------------------" << std::endl;
    }
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

    for (unsigned short row = 0; row < dimension; row++) {
        delete[] board[row];
    }

    delete[] board;
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

bool moveUp(unsigned int** board, unsigned short const dimension) {
    bool isElement2048 = false;

    for (unsigned short row = 1; row < dimension; row++) {
        for (unsigned short col = 0; col < dimension; col++) {
            unsigned int element = board[row][col];
            
            if (element == 0) {
                continue;
            }

            unsigned short i = row - 1;
            bool shouldRemove = true;
            while (true) {
                unsigned int element2 = board[i][col];

                if (element2 == element) {
                    board[i][col] += element;
                    break;
                }
                else if (element2 != 0) {
                    board[i + 1][col] = element;
                    if (i + 1 == row) {
                        shouldRemove = false;
                    }
                    break;
                }
                else if (i == 0) {
                    board[i][col] = element; 
                    break;
                }

                i--;
            }

            if (shouldRemove) {
                board[row][col] = 0;
            }

            unsigned int element2 = board[i][col];
            if (element2 >= 2048) {
                isElement2048 = true;
                return isElement2048;
            }
        }
    }

    return isElement2048;
}

bool moveLeft(unsigned int** board, unsigned short const dimension) {
    bool isElement2048 = false;

    for (unsigned short row = 0; row < dimension; row++) {
        for (unsigned short col = 1; col < dimension; col++) {
            unsigned int element = board[row][col];

            if (element == 0) {
                continue;
            }

            unsigned short i = col - 1;
            bool shouldRemove = true;
            while (true) {
                unsigned int element2 = board[row][i];

                if (element2 == element) {
                    board[row][i] += element;
                    break;
                }
                else if (element2 != 0) {
                    board[row][i + 1] = element;
                    if (i + 1 == col) {
                        shouldRemove = false;
                    }
                    break;
                }
                else if (i == 0) {
                    board[row][i] = element;
                    break;
                }

                i--;
            }

            if (shouldRemove) {
                board[row][col] = 0;
            }

            unsigned int element2 = board[row][i];
            if (element2 >= 2048) {
                isElement2048 = true;
                return isElement2048;
            }
        }
    }

    return isElement2048;
}

bool moveDown(unsigned int** board, unsigned short const dimension) {
    bool isElement2048 = false;

    short row = dimension - 2;
    while (row >= 0) {
        for (unsigned short col = 0; col < dimension; col++) {
            unsigned int element = board[row][col];

            if (element == 0) {
                continue;
            }

            unsigned short i = row + 1;
            bool shouldRemove = true;
            while (true) {
                unsigned int element2 = board[i][col];

                if (element2 == element) {
                    board[i][col] += element;
                    break;
                }
                else if (element2 != 0) {
                    board[i - 1][col] = element;
                    if (i - 1 == row) {
                        shouldRemove = false;
                    }
                    break;
                }
                else if (i == dimension - 1) {
                    board[i][col] = element;
                    break;
                }

                i++;
            }
            
            if (shouldRemove) {
                board[row][col] = 0;
            }

            unsigned int element2 = board[i][col];
            if (element2 >= 2048) {
                isElement2048 = true;
                return isElement2048;
            }
        }

        row--;
    }

    return isElement2048;
}

bool moveRight(unsigned int** board, unsigned short const dimension) {
    bool isElement2048 = false;

    for (unsigned short row = 0; row < dimension; row++) {
        short col = dimension - 2;

        while (col >= 0) {
            unsigned int element = board[row][col];
           
            if (element == 0) {
                col--;
                continue;
            }

            unsigned short i = col + 1;
            bool shouldRemove = true;
            while (true) {
                unsigned int element2 = board[row][i];

                if (element2 == element) {
                    board[row][i] += element;
                    break;
                }
                else if (element2 != 0) {
                    board[row][i - 1] = element;
                    if (i - 1 == col) {
                        shouldRemove = false;
                    }
                    break;
                }
                else if (i == dimension - 1) {
                    board[row][i] = element;
                    break;
                }

                i++;
            }
           
            if (shouldRemove) {
                board[row][col] = 0;
            }

            unsigned int element2 = board[row][i];
            if (element2 >= 2048) {
                isElement2048 = true;
                return isElement2048;
            }

            col--;
        }
    }

    return isElement2048;
}

void addPlayerToLeaderboard(unsigned const int** const board, unsigned const char* const playerName, unsigned short const dimension) {
    std::string fileName = "Leaderboard" + std::to_string(dimension) + 'x' + std::to_string(dimension) + ".txt"; 
    std::ofstream outputFile(fileName);

    // Check if the file is open
    if (!outputFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return;
    }

    unsigned int sumPlayerPoints = playerPoints(board, dimension);

    // Write data to the file
    outputFile << playerName << " - " << sumPlayerPoints << std::endl;

    // Close the file
    outputFile.close();
}

unsigned int playerPoints(unsigned const int** const board, unsigned short dimension) {
    unsigned int sumPlayerPoints = 0;
    
    for (unsigned short row = 0; row < dimension; row++) {
        for (unsigned short col = 0; col < dimension; col++) {
            unsigned int element = board[row][col];

            if (element != 0) {
                sumPlayerPoints += element;
            }
        }
    }

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
}

void printLeaderboard(unsigned short const dimension) {
    std::string fileName = "Leaderboard" + std::to_string(dimension) + 'x' + std::to_string(dimension) + ".txt";
    std::ifstream inputFile(fileName);

    // Check if the file is open
    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(inputFile, line)) {
        lines.push_back(line);
    }

    // Sort the vector
    std::sort(lines.begin(), lines.end());

    unsigned short count = 1;
    std::cout << "-------------------------------------------------------" << std::endl;
    // Read and print each line from the file
    while (std::getline(inputFile, line)) {
        std::cout << "| " << count << ". " << line << std::endl;
        count++;

        if (count > 5) {
            break;
        }
    }
    std::cout << "-------------------------------------------------------" << std::endl;
    std::cout << std::endl;

    // Close the file
    inputFile.close();
}