#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <stdbool.h>

void initializeBoard(char board[3][3]);
void playerMove(char board[3][3]);
void computerMove(char board[3][3]);
int checkWinner(char board[3][3]);
bool checkFreeSpaces(char board[3][3]);

#endif
