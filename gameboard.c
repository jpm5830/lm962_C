// gameboard.c
// Define gameboard and lines

#include <stdio.h>
#include <stdlib.h>
#include "gameboard.h"

// GLOBAL VARIABLES
symbol gboard[N_ROWS][N_REELS];
symbol lines[MAX_LINES][N_REELS];

// LOCAL FUNCTIONS
static void print_line (ulong linenum)
{
  printf ("Line %-3d: ", linenum);
  for (ulong i = 0; i < N_REELS; i++)
    printf ("%-3s", print_sym (lines[linenum][i]));
  printf ("\n");
}

static void update_lines (void)
{
  lines[0][0] = gboard[1][0];
  lines[0][1] = gboard[1][1];
  lines[0][2] = gboard[1][2];
  lines[0][3] = gboard[1][3];
  lines[0][4] = gboard[1][4];
  lines[1][0] = gboard[0][0];
  lines[1][1] = gboard[0][1];
  lines[1][2] = gboard[0][2];
  lines[1][3] = gboard[0][3];
  lines[1][4] = gboard[0][4];
  lines[2][0] = gboard[2][0];
  lines[2][1] = gboard[2][1];
  lines[2][2] = gboard[2][2];
  lines[2][3] = gboard[2][3];
  lines[2][4] = gboard[2][4];
  lines[3][0] = gboard[0][0];
  lines[3][1] = gboard[1][1];
  lines[3][2] = gboard[2][2];
  lines[3][3] = gboard[1][3];
  lines[3][4] = gboard[0][4];
  lines[4][0] = gboard[2][0];
  lines[4][1] = gboard[1][1];
  lines[4][2] = gboard[0][2];
  lines[4][3] = gboard[1][3];
  lines[4][4] = gboard[2][4];
  lines[5][0] = gboard[2][0];
  lines[5][1] = gboard[2][1];
  lines[5][2] = gboard[1][2];
  lines[5][3] = gboard[0][3];
  lines[5][4] = gboard[0][4];
  lines[6][0] = gboard[0][0];
  lines[6][1] = gboard[0][1];
  lines[6][2] = gboard[1][2];
  lines[6][3] = gboard[2][3];
  lines[6][4] = gboard[2][4];
  lines[7][0] = gboard[1][0];
  lines[7][1] = gboard[2][1];
  lines[7][2] = gboard[1][2];
  lines[7][3] = gboard[0][3];
  lines[7][4] = gboard[1][4];
  lines[8][0] = gboard[1][0];
  lines[8][1] = gboard[0][1];
  lines[8][2] = gboard[1][2];
  lines[8][3] = gboard[2][3];
  lines[8][4] = gboard[1][4];
  lines[9][0] = gboard[2][0];
  lines[9][1] = gboard[1][1];
  lines[9][2] = gboard[1][2];
  lines[9][3] = gboard[1][3];
  lines[9][4] = gboard[0][4];
  lines[10][0] = gboard[0][0];
  lines[10][1] = gboard[1][1];
  lines[10][2] = gboard[1][2];
  lines[10][3] = gboard[1][3];
  lines[10][4] = gboard[2][4];
  lines[11][0] = gboard[1][0];
  lines[11][1] = gboard[2][1];
  lines[11][2] = gboard[2][2];
  lines[11][3] = gboard[1][3];
  lines[11][4] = gboard[0][4];
  lines[12][0] = gboard[1][0];
  lines[12][1] = gboard[0][1];
  lines[12][2] = gboard[0][2];
  lines[12][3] = gboard[1][3];
  lines[12][4] = gboard[2][4];
  lines[13][0] = gboard[1][0];
  lines[13][1] = gboard[1][1];
  lines[13][2] = gboard[2][2];
  lines[13][3] = gboard[1][3];
  lines[13][4] = gboard[0][4];
  lines[14][0] = gboard[1][0];
  lines[14][1] = gboard[1][1];
  lines[14][2] = gboard[0][2];
  lines[14][3] = gboard[1][3];
  lines[14][4] = gboard[2][4];
}

// GLOBAL FUNCTIONS
void print_all_lines (void)
{
  printf ("\n");
  for (int i = 0; i < MAX_LINES; i++)
    print_line (i);
  printf ("\n");

}

void update_gboard (void)
{
  //shuffle_reels();
  for (int i = 0; i < N_REELS; i++)
    {
      ulong chosen_slot = (ulong) (random () % reel_sizes[i]);
      gboard[0][i] = reels[i][chosen_slot];
      chosen_slot++;
      if (chosen_slot < reel_sizes[i])
        gboard[1][i] = reels[i][chosen_slot];
      else
        {
          chosen_slot = 0;
          gboard[1][i] = reels[i][chosen_slot];
        }
      chosen_slot++;
      if (chosen_slot < reel_sizes[i])
        gboard[2][i] = reels[i][chosen_slot];
      else
        gboard[2][i] = reels[i][0];
    }
  update_lines ();
}

void print_gboard (ulong game_num)
{
  printf ("\n");
  printf ("GAMEBOARD %ld\n", game_num);
  printf ("---------\n");
  for (int i = 0; i < N_ROWS; i++)
    {
      for (int j = 0; j < N_REELS; j++)
        printf ("%-3s", print_sym (gboard[i][j]));
      printf ("\n");
    }
  printf ("\n");
}

void init_gboard (void)
{
  init_reels ();
  shuffle_reels ();
  print_reels ();
  update_gboard ();
}
