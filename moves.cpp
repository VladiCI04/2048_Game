#include "moves.h"

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