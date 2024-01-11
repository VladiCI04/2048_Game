#pragma once

unsigned int** createBoard(unsigned short const dimension);

void addNumToBoard(unsigned int** board, unsigned int const moveCount, unsigned short const dimension);

bool isBoardFull(unsigned int** board, unsigned short const dimension);