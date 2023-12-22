#include <iostream>
#include <random>

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
short enterDimension();
int** createBoard(short const dimension);
void addNumToBoard(int** board, int const moveCount);
short randomIndexGenerator();
short randomNumberGenerator(int const moveCount);
void printBoard(int** board, short dimension);
void playGame(int** board, short const dimension, int& moveCount);
bool isBoardFull(int** board, short const dimension);
bool moveUp(int** board, short const dimension);
bool moveLeft(int** board, short const dimension);
bool moveDown(int** board, short const dimension);
bool moveRight(int** board, short const dimension);
void printLeaderboard();

int main()
{
    // Start Game
    gameMenu();
}

void gameMenu() {
    // Print Game Menu
    printGameMenu();

    short answer;
    std::cin >> answer;

    if (answer == 1 ) {  // Start New Game
        startNewGame();
    }
    else if (answer == 2) {  // Leaderboard
        printLeaderboard();
    } 
    else if (answer == 3) {  // Quit
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
    char playerName[MAX_INPUT_SIZE];
    std::cin >> playerName;

    // Enter Dimention
    short dimension = enterDimension();
    
    // Board
    int moveCount = 0;
    int** board = createBoard(dimension);
    addNumToBoard(board, moveCount);
    printBoard(board, dimension);
    playGame(board, dimension, moveCount);
}

void printStartNewGameTitle() {
    std::cout << std::endl;
    std::cout << "-------------------2048 Game-----------------" << std::endl;
}

short enterDimension() {
    std::cout << "Enter dimension (Dimention should be between 4 and 10): ";
    short dimension;
    std::cin >> dimension;

    if (dimension < 4 || dimension > 10) {
        std::cout << "Wrong dimention! (Dimention should be between 4 and 10)";
        std::cout << std::endl;

        gameMenu();
    }

    return dimension;
}

int** createBoard(short const dimension) {
    int** board = new int*[dimension];

    for (int row = 0; row < dimension; row++) {
        for (int col = 0; col < dimension; col++) {
            board[row][col] = 0;
        }
    }

    return board;
}

void addNumToBoard(int** board, int const moveCount) {
    short randRow = randomIndexGenerator();
    short randCol = randomIndexGenerator();

    if (board[randRow][randCol] == 0) {
        short randNum = randomNumberGenerator(moveCount);
        board[randRow][randCol] = randNum;
    }
    else {
        addNumToBoard(board, moveCount);
    }
}

short randomIndexGenerator() {
    // Create a random number engine
    std::random_device random;
    std::mt19937 generator(random());

    // Define a distribution (e.g., uniform distribution between 0 and 9)
    std::uniform_int_distribution<int> distribution(0, 9);

    // Generate a random number
    int randomNumber = distribution(generator);

    return randomNumber;
}

short randomNumberGenerator(int moveCount) {
    // Create a random number engine
    std::random_device random;
    std::mt19937 generator(random());

    // Define a distribution (e.g., uniform distribution between 1 and 3)
    std::uniform_int_distribution<int> distribution(1, 3);

    // Generate a random number
    int randomNumber = distribution(generator);
    if (randomNumber == 1) {
        randomNumber = 2;
    }
    else if (randomNumber == 2) {
        randomNumber = 4;
    }
    else if (moveCount >= 8) {
        randomNumber = 8;
    }
    else {
        randomNumberGenerator(moveCount);
    }

    return randomNumber;
}

void printBoard(int** board, short dimension) {
    std::cout << "----------Board----------" << std::endl;
    for (int row = 0; row < dimension; row++) {
        for (int col = 0; col < dimension; col++) {
            std::cout << board[row][col] << ' ';
        }
    }
    std::cout << "-------------------------" << std::endl;
}

void playGame(int** board, short const dimension, int& moveCount) {
    bool isWin = false;

    while (!isBoardFull(board, dimension)) {
        std::cout << std::endl;
        std::cout << "Enter diretction (Direction should be w, a, s or d): " << std::endl;
        char direction;
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
        addNumToBoard(board, moveCount);
        printBoard(board, dimension);
    }
   
    if (isWin) {
        std::cout << "You win!" << std::endl;
    }
    else {
        std::cout << "You lose! Try again!" << std::endl;
    }
}

bool isBoardFull(int** board, short const dimension) {
    for (int row = 0; row < dimension; row++) {
        for (int col = 0; col < dimension; col++) {
            int element = board[row][col];

            if (element == 0) {
                return false;
            }
        }
    }
    
    return true;
}

bool moveUp(int** board, short const dimension) {
    bool isElement2048 = false;

    for (int row = 1; row < dimension; row++) {
        for (int col = 0; col < dimension; col++) {
            int element = board[row][col];
            
            if (element == 0) {
                continue;
            }

            short i = 0;
            while (true) {
                if (board[i][col] == element) {
                    board[i][col] += element;
                    break;
                }
                else if (board[i][col] == 0) {
                    board[i][col] = element;
                    break;
                }

                i++;
            }
            board[row][col] = 0;

            int element2 = board[i][col];
            if (element2 >= 2048) {
                isElement2048 = true;
                return isElement2048;
            }
        }
    }

    return isElement2048;
}

bool moveLeft(int** board, short const dimension) {
    bool isElement2048 = false;

    for (int row = 0; row < dimension; row++) {
        for (int col = 1; col < dimension; col++) {
            int element = board[row][col];

            if (element == 0) {
                continue;
            }

            short i = 0;
            while (true) {
                if (board[row][i] == element) {
                    board[row][i] += element;
                    break;
                }
                else if (board[row][i] == 0) {
                    board[row][i] = element;
                    break;
                }

                i++;
            }
            board[row][col] = 0;

            int element2 = board[row][i];
            if (element2 >= 2048) {
                isElement2048 = true;
                return isElement2048;
            }
        }
    }

    return isElement2048;
}

bool moveDown(int** board, short const dimension) {
    bool isElement2048 = false;

    for (int row = 0; row < dimension - 1; row++) {
        for (int col = 0; col < dimension; col++) {
            int element = board[row][col];

            if (element == 0) {
                continue;
            }

            short i = dimension - 1;
            while (true) {
                if (board[i][col] == element) {
                    board[i][col] += element;
                    break;
                }
                else if (board[i][col] == 0) {
                    board[i][col] = element;
                    break;
                }

                i--;
            }
            board[row][col] = 0;

            int element2 = board[i][col];
            if (element2 >= 2048) {
                isElement2048 = true;
                return isElement2048;
            }
        }
    }

    return isElement2048;
}

bool moveRight(int** board, short const dimension) {
    bool isElement2048 = false;

    for (int row = 0; row < dimension; row++) {
        for (int col = 0; col < dimension - 1; col++) {
            int element = board[row][col];
           
            if (element == 0) {
                continue;
            }

            short i = dimension - 1;
            while (true) {
                if (board[row][i] == element) {
                    board[row][i] += element;
                    break;
                }
                else if (board[row][i] == 0) {
                    board[row][i] = element;
                    break;
                }

                i--;
            }
            board[row][col] = 0;

            int element2 = board[row][i];
            if (element2 >= 2048) {
                isElement2048 = true;
                return isElement2048;
            }
        }
    }

    return isElement2048;
}

void printLeaderboard() {
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;
    std::cout << "| 1. " << LeaderboardName1 << ": " << LeaderboardPoints1 << std::endl;
    std::cout << "| 2. " << LeaderboardName2 << ": " << LeaderboardPoints2 << std::endl;
    std::cout << "| 3. " << LeaderboardName3 << ": " << LeaderboardPoints3 << std::endl;
    std::cout << "| 4. " << LeaderboardName4 << ": " << LeaderboardPoints4 << std::endl;
    std::cout << "| 5. " << LeaderboardName5 << ": " << LeaderboardPoints5 << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;
    std::cout << std::endl;
}