#pragma once

void addPlayerToLeaderboard(unsigned int** board, unsigned char* playerName, unsigned short const dimension);

unsigned int playerPoints(unsigned int** board, unsigned short dimension);

void leaderboard();