// File: reels.c

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "reels.h"

// PUBLIC VARIABLES

// Use fixed reels (pre-shuffled w/ correct symbol counts) or not
bool use_fixed_reels = TRUE;

// Pointers to each reel
symbol *reels[N_REELS];

//  Reel sizes for each reel.
const int reel_sizes[N_REELS] = {47, 46, 48, 50, 50};

// PRIVATE VARS

// LM962 symbol counts per reel
static const int reel_cnts[N_REELS][SYM_SET_SIZE] = {
    {2, 4, 4, 6, 5, 6, 6, 5, 5, 2, 2},
    {2, 4, 4, 4, 4, 4, 6, 6, 5, 5, 2},
    {1, 3, 5, 4, 6, 5, 5, 5, 6, 6, 2},
    {4, 4, 4, 4, 6, 6, 6, 6, 8, 0, 2},
    {2, 4, 5, 4, 7, 7, 6, 6, 7, 0, 2}};

// Fixed reel definitions (used only when use_fixed_reels == TRUE)
static symbol fr_0[47] = {CL, SF, LM, CL, BU, LT, LH, LH, LH, BO, LH, LO, TU, TU, BO, SG, TU, WS, LM, WS, SG, CL, TU,
                          BO, BO, LM,
                          SG, LT, SF, LH, SF, BU, CL, SF, CL, CL, BO, SG, LO, LM, BO, BU, TU, SG, SF, TU, BU};

static symbol fr_1[46] = {TU, WS, BU, LM, LO, LM, SG, LT, SF, CL, BU, CL, LH, SF, SG, LM, TU, LO, BO, WS, TU, BU, LH,
                          SF, BU, LM,
                          BO, TU, SF, BO, SG, SG, BO, CL, LT, SG, CL, LO, CL, SF, LH, LH, CL, LO, SG, LO};

static symbol fr_2[48] = {CL, LO, BU, CL, SG, TU, TU, LH, SG, BU, BU, LM, CL, BO, CL, TU, BO, BO, SF, WS, TU, SG, SG,
                          BU, LO, LO,
                          SG, BO, LT, LO, SF, SF, LH, SF, SF, LH, TU, LO, LT, LO, LM, LM, BU, LH, LH, LH, CL, SF};

static symbol fr_3[50] = {BO, WS, LT, WS, TU, LH, SF, SF, SF, SG, LH, LM, BU, SG, SF, TU, LH, SF, TU, CL, BU, TU, LH,
                          BU, LH, CL,
                          CL, LM, BO, SF, SG, LT, SF, SG, BO, TU, BO, TU, LM, SF, SG, BU, WS, LM, CL, WS, LH, SG, CL,
                          CL};

static symbol fr_4[50] = {SG, LH, SF, SG, LH, BO, CL, SF, SF, CL, SG, SF, TU, LM, BU, LH, BU, SG, TU, LT, TU, LH, BO,
                          BU, LM, BU,
                          TU, SG, TU, CL, SF, BO, TU, LM, SF, LT, LH, SG, LH, LH, BO, TU, BU, LM, CL, SF, WS, CL, WS,
                          CL};

static bool reels_are_initialized = FALSE;

// PRIVATE FUNCTIONS

// Return a pointer to a reel (symbol[] of capacity elements)
static symbol *make_reel (size_t capacity)
{
  assert(use_fixed_reels == FALSE);
  assert(capacity > 0);
  symbol *rmem = (symbol *) calloc (capacity, sizeof (int));
  assert(rmem != NULL);
  return (rmem);
}

// Sets the reels[] with pointers to each fixed reel
static void set_fixed_reels ()
{
  assert(use_fixed_reels == TRUE);
  reels[0] = fr_0;
  reels[1] = fr_1;
  reels[2] = fr_2;
  reels[3] = fr_3;
  reels[4] = fr_4;
}

// Populate a single pre-allocated reel with the correct number of symbols per reel.
// Should only be called when use_fixed_reels is FALSE
// Params: reel -> pointer to a dynamically created reel from make_reel()
//         reel_idx -> 0 based index of the reel to populate
static void populate_reel (symbol *reel, int reel_idx)
{
  assert(use_fixed_reels == FALSE);
  assert (reel != NULL);
  assert ((reel_idx > -1) && (reel_idx < N_REELS));
  symbol *rptr = reel;
  for (int i = 0; i < SYM_SET_SIZE; i++)
    {
      // Get symbol cnt for each symbol for this reel
      int cnt = reel_cnts[reel_idx][i];
      // Duplicate the symbol cnt times
      for (int j = 0; j < cnt; j++)
        {
          *rptr = i;
          rptr++;
        }
    }
}
// Print out a single reel using 2 char codes.
// Params: reel -> pointer to the reel to be printed.
//         reel_idx -> integer between 0 and N_REELS-1, used to get reel size from reel_sizes[]
static void print_reel (symbol *reel, int reel_idx)
{
  assert(reel != NULL);
  assert((reel_idx > -1) && (reel_idx < N_REELS));
  int slots = reel_sizes[reel_idx];
  printf ("Reel %d: { ", reel_idx);
  for (int i = 0; i < slots - 1; i++)
    printf ("%s, ", print_sym (reel[i]));
  printf ("%s }\n", print_sym (reel[slots - 1]));
}

// Utility function to swap elements `a[i]` and `a[j]` in an array
static void swap (symbol a[], int i, int j)
{
  assert(a != NULL);
  assert((i >= 0) && (j >= 0));
  symbol temp = a[i];
  a[i] = a[j];
  a[j] = temp;
}

// Function to shuffle an array `a[]` of `n` elements
// Implements the Fisher-Yates algorithm
static void shuffle_reel (symbol a[], int n)
{
  assert(a != NULL);
  assert((n >= 0) && (n <= MAX_REEL_SIZE));
  // read array from the highest index to lowest
  for (int i = n - 1; i >= 1; i--)
    {
      // generate a random number `j` such that `0 <= j <= i`
      int j = (int) (random () % (i + 1));

      // swap the current element with the randomly generated index
      swap (a, i, j);
    }
}

// PUBLIC FUNCTIONS

// Initializes all reels before use. Call this function 1st.
// If use_fixed_reels == FALSE, be sure to call free_reels() when finished with them
// to free up allocated heap memory.
void init_reels ()
{
  if (use_fixed_reels)
    {
      set_fixed_reels ();
    }
  else
    {
      for (int i = 0; i < N_REELS; i++)
        {
          symbol *reel = make_reel (reel_sizes[i]); // Create a single reel of correct size
          populate_reel (reel, i); // Populate this reel with correct number of symbols.
          shuffle_reel (reel, reel_sizes[i]);
          reels[i] = reel; // Store a pointer to this reel in the reels[] array.
        }
    }
  reels_are_initialized = TRUE;
}

// Return a 2 char C string pointer equivalent to its symbol_t enum value
char *print_sym (symbol i)
{
  assert((i >= WS) && (i <= LT));
  char *ch;
  switch (i)
    {
      case 0:
        ch = "WS";
      break;
      case 1:
        ch = "LM";
      break;
      case 2:
        ch = "BU";
      break;
      case 3:
        ch = "BO";
      break;
      case 4:
        ch = "LH";
      break;
      case 5:
        ch = "TU";
      break;
      case 6:
        ch = "CL";
      break;
      case 7:
        ch = "SG";
      break;
      case 8:
        ch = "SF";
      break;
      case 9:
        ch = "LO";
      break;
      case 10:
        ch = "LT";
      break;
      default:
        ch = "??";
    }
  return (ch);
}

// Print all reels in the reels[] array
void print_reels ()
{
  assert(reels_are_initialized);
  printf ("\n");
  for (int i = 0; i < N_REELS; i++)
    print_reel (reels[i], i);
}

// Free dynamically allocated heap memory when use_fixed_reels global variable is FALSE
void free_reels ()
{
  assert(use_fixed_reels == FALSE);
  for (int i = 0; i < N_REELS; i++)
    free (reels[i]);
  reels_are_initialized = FALSE;
}

// Randomize the position of all symbols of all reels in place.
void shuffle_reels ()
{
  assert(reels_are_initialized);
  for (int i = 0; i < N_REELS; i++)
    shuffle_reel (reels[i], reel_sizes[i]);
}
