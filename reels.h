#ifndef _REELS_H_
#define _REELS_H_

/**
* @file reels.h
* @brief Provides data structures and functions for creating and manipulating a reel and sets of reels
*
* @author Jim Morrissey
*
* @date 5/11/2021
*/

#define SYM_SET_SIZE 11 /** Number of distinct symbols */
#define N_REELS 5 /** Number of reels to generate */

typedef unsigned long ulong;
typedef unsigned int uint;
typedef unsigned char uchar;

/**
 * Enum declaring FALSE (0) or TRUE (1).
 */
typedef enum {
    FALSE, TRUE
} bool;

/**
 * Enum declaring all possible symbol values (0 through 10).
 */
typedef enum {
    WS, LM, BU, BO, LH, TU, CL, SG, SF, LO, LT
} symbol; // All 11 game symbols

/**
 * Array of pointers to each reel created.
 */
extern symbol *reels[N_REELS];

/**
 * Array of reel sizes.
 */
extern const int reel_sizes[N_REELS];

/**
 * Creates each reel of the specified size (from reel_sizes[]) in the heap memory.
 * Adds a pointer to each reel in the reels[]. Populates each reel with the correct
 * number of each symbol in every reel.
 */
void init_reels ();

/**
 * Prints all symbols from all reels in index order, each as a 2 character code.
 */
void print_reels ();

/**
 * Frees the dynamically allocated memory for ALL reels created. Call this function
 * when you are finished with all reels.
 */
void free_reels ();

/**
 * Returns a pointer to a C string 2 character code that corresponds to each symbol
 * entry found in the symbols anonymous enum typedef.
 * @param i A 2 char identifier from symbols.
 * @return  Pointer to the equivalent 2 character C string.
 */
char *print_sym (symbol i);

/**
 * Shuffles (randomizes) the position of all symbols within each reel, and across all
 * reels.
 */
void shuffle_reels ();

#endif
