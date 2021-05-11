#ifndef _REELS_H_
#define _REELS_H_

// CONSTANTS
#define SYM_SET_SIZE 11
#define N_REELS 5
#define N_ROWS 3

typedef enum {
    FALSE, TRUE
} bool;
typedef enum {
    WS, LM, BU, BO, LH, TU, CL, SG, SF, LO, LT
} symbols; // All 11 game symbols

extern int *reels[N_REELS];
extern const int reel_sizes[N_REELS];

// GLOBAL FUNCTIONS
void init_reels (void);

void print_reels (void);

void free_reels (void);

char *print_sym (int i);

void shuffle_reels ();

#endif
