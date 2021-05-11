#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "reels.h"

int *reels[N_REELS];

// LM962 SYMBOL COUNTS PER REEL AND REEL SIZES
const int reel_sizes[N_REELS] = {47, 46, 48, 50, 50};

static const int reel_cnts[N_REELS][SYM_SET_SIZE] = {
    {2, 4, 4, 6, 5, 6, 6, 5, 5, 2, 2},
    {2, 4, 4, 4, 4, 4, 6, 6, 5, 5, 2},
    {1, 3, 5, 4, 6, 5, 5, 5, 6, 6, 2},
    {4, 4, 4, 4, 6, 6, 6, 6, 8, 0, 2},
    {2, 4, 5, 4, 7, 7, 6, 6, 7, 0, 2}};

// LOCAL FUNCTIONS
static int *make_reel (size_t capacity)
{
  int *rmem = (int *) calloc (capacity, sizeof (int));
  assert(rmem != NULL);
  return (rmem);
}

static void populate_reel (int *reel, int reel_idx)
{
  assert(reel != NULL);
  assert(reel_idx > -1 && reel_idx < N_REELS);
  int *rptr = reel;
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

static void print_reel (int *reel, int reel_idx)
{
  assert(reel != NULL);
  assert(reel_idx > -1 && reel_idx < N_REELS);
  int slots = reel_sizes[reel_idx];
  printf ("Reel %d: ", reel_idx);
  for (int i = 0; i < slots; i++)
    printf ("%-3s", print_sym (reel[i]));
  printf ("\n");
}

// Utility function to swap elements `a[i]` and `a[j]` in an array
static void swap (int a[], int i, int j)
{
  int temp = a[i];
  a[i] = a[j];
  a[j] = temp;
}

// Function to shuffle an array `a[]` of `n` elements
static void shuffle_reel (int a[], int n)
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
  for (int i = 0; i < N_REELS; i++)
    {
      int *reel = make_reel (reel_sizes[i]);
      populate_reel (reel, i);
      reels[i] = reel;
    }
}

char *print_sym (int i)
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
