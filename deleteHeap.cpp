#include "deleteHeap.h"

void deleteHeap(unsigned int** board, unsigned short const dimension) {
    for (unsigned short row = 0; row < dimension; row++) {
        delete[] board[row];
    }

    delete[] board;
}