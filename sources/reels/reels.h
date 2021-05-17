#ifndef _REELS_H_
#define _REELS_H_

/**
* @file reels.h
* @brief Provides data structures and functions for working with multiple reels.
*
* @author Jim Morrissey
*
* @date 5/11/2021
*/

#define SYM_SET_SIZE 11 /** Number of distinct symbols */
#define N_REELS 5 /** Number of reels to generate */
#define MAX_REEL_SIZE 50 /** Max size of any reel used */

typedef unsigned long ulong;

/**
 * @brief  Enum declaring FALSE (0) or TRUE (1).
 */
typedef enum bool_t {
    FALSE, TRUE
} bool;

/**
 * @brief  Enum declaring all possible symbol values (0 through 10).
 */
typedef enum symbol_t {
    WS, LM, BU, BO, LH, TU, CL, SG, SF, LO, LT
} symbol; // All 11 game symbols

/**
 * @brief  Use fixed reels or not
 * @desc  Fixed reels are pre-allocated, shuffled reels with correct symbol counts for
 * the 96.2% payback game. The reels are allocated in program memory, so no dynamic memory
 * allocation is needed. If this parameter is set to FALSE, dynamically allocated
 * reels on the heap will be used instead. If FALSE, be sure to call the free_reels()
 * function to free the dynamically allocated memory.
 */
extern bool use_fixed_reels;

/**
 * @brief  Array of pointers to each reel.
 * @desc  This is an array of pointers to each of the N_REELS reel arrays. Each reel array pointed to
 * here consists of symbol elements. Each reel can have a different number of symbol elements,
 * and the size of each reel array is specified in the reel_sizes integer array below.
 */
extern symbol *reels[N_REELS];

/**
 * @brief  Array of reel sizes.
 * @desc  This array specifies the number of symbol elements in each of the N_REELS reels. A particular
 * index position within a reel is also known as a slot.
 */
extern const int reel_sizes[N_REELS];

/**
 * @brief  Creates and/or initializes each of the N_REELS.
 * @desc  This function MUST be called before attempting to use any reels externally. The boolean variable
 * use_fixed_reels chooses between using a fixed reel configuration for each reel, or dynamically
 * allocating heap memory for each reel and populating each reel with the correct number of symbols.
 * If use_fixed_reels == FALSE, you MUST remember to call function free_reels() to release the heap
 * memory allocated by init_reels(). For use_fixed_reels == TRUE, no dynamic memory is allocated,
 * and hence there is no need to call the free_reels() function on exit.
 */
void init_reels ();

/**
 * @brief  Prints the symbols from each reel in index order, as 2 character codes.
 * @desc  The 2 char codes are defined in the symbol_t enum.
 */
void print_reels ();

/**
 * @brief  Frees the dynamically allocated reel memory.
 * @desc  If the boolaen variable use_fixed_reels == FALSE, then you MUST call this function to free
 * the dynamically allocated memory on exit. If you are using fixed reels instead, that memory
 * is NOT dynamically allocated, so DO NOT CALL THIS function.
 */
void free_reels ();

/**
 * @brief  Returns a pointer to a 2 char C string representing the corresponding symbol_t enum.
 * @desc  Converts a symbol_t enum value into a 2 char printable string.
 * @param i  A two char identifier from the symbol_t enum.
 * @return   Pointer to the equivalent 2 character C string.
 */
char *print_sym (symbol i);

/**
 * @brief  Shuffles the positions of all symbols within all reels in place.
 * @desc  Each of the N_REELS reels is shuffled in place randomly. Correct symbol counts
 * for each reel are maintained after shuffling. Uses the Fisher-Yates algorithm.
 */
void shuffle_reels ();

#endif
