// gameboard.h
#ifndef _GAMEBOARD_H_
#define _GAMEBOARD_H_

#include "reels.h"

#define MAX_LINES 15

extern int gboard[N_ROWS][N_REELS];
extern int lines[MAX_LINES][N_REELS];

void init_gboard (void);
void update_gboard (void);
void print_gboard (long gamenum);
void print_lines (void);

#endif
