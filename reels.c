#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "reels.h"

// Use fixed reels (pre-shuffled w/ correct symbol counts) or not
bool use_fixed_reels = TRUE;

// Pointers to each reel
symbol *reels[N_REELS];

//  REEL SIZES FOR EACH REEL
const int reel_sizes[N_REELS] = {47, 46, 48, 50, 50};

// LM962 SYMBOL COUNTS PER REEL
static const int reel_cnts[N_REELS][SYM_SET_SIZE] = {
    {2, 4, 4, 6, 5, 6, 6, 5, 5, 2, 2},
    {2, 4, 4, 4, 4, 4, 6, 6, 5, 5, 2},
    {1, 3, 5, 4, 6, 5, 5, 5, 6, 6, 2},
    {4, 4, 4, 4, 6, 6, 6, 6, 8, 0, 2},
    {2, 4, 5, 4, 7, 7, 6, 6, 7, 0, 2}};

// FIXED REEL DEFINITIONS
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

// LOCAL FUNCTIONS
static symbol *make_reel (size_t capacity)
{
  symbol *rmem = (symbol *) calloc (capacity, sizeof (int));
  assert(rmem != NULL);
  return (rmem);
}

static void set_fixed_reels ()
{
  reels[0] = fr_0;
  reels[1] = fr_1;
  reels[2] = fr_2;
  reels[3] = fr_3;
  reels[4] = fr_4;
}

static void populate_reel (symbol *reel, int reel_idx)
{
  assert (reel != NULL);
  assert ((reel_idx > -1) && (reel_idx < N_REELS));
  symbol *rptr = reel;
  for (int i = 0; i < SYM_SET_SIZE; i++)
    {
      int cnt = reel_cnts[reel_idx][i];
      for (int j = 0; j < cnt; j++)
        {
          *rptr = i;
          rptr++;
        }
    }
}

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
  symbol temp = a[i];
  a[i] = a[j];
  a[j] = temp;
}

// Function to shuffle an array `a[]` of `n` elements
static void shuffle_reel (symbol a[], int n)
{
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
          symbol *reel = make_reel (reel_sizes[i]);
          populate_reel (reel, i);
          reels[i] = reel;
        }
    }
}

char *print_sym (symbol i)
{
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

void print_reels ()
{
  printf ("\n");
  for (int i = 0; i < N_REELS; i++)
    print_reel (reels[i], i);
}

void free_reels ()
{
  for (int i = 0; i < N_REELS; i++)
    free (reels[i]);
}

void shuffle_reels ()
{
  for (int i = 0; i < N_REELS; i++)
    shuffle_reel (reels[i], reel_sizes[i]);
}
