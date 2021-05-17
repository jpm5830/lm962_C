// gameboard.h
#ifndef _GAMEBOARD_H_
#define _GAMEBOARD_H_

#include "../reels/reels.h"

#define N_ROWS 3
#define MAX_LINES 15

extern symbol gboard[N_ROWS][N_REELS];
extern symbol lines[MAX_LINES][N_REELS];

void init_gboard ();
void update_gboard ();
void print_gboard (ulong game_num);
void print_all_lines ();

#endif
