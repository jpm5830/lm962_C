// File: engine.c
// Created by jpm on 5/7/21.
//

#include <assert.h>
#include <stdio.h>
#include "../stats/stats.h"
#include "engine.h"

bool print_game_info = TRUE; // print gameboard and wins?

ulong payouts[MAX_MATCHES][SYM_SET_SIZE] =
    {
        {0,     0,    0,   0,   0,   0,   0,   0,   0,   0,   0},
        {5,     2,    0,   0,   0,   0,   0,   0,   0,   0,   0},
        {100,   40,   25,  25,  10,  10,  5,   5,   5,   331, 0},
        {500,   200,  100, 100, 50,  50,  30,  30,  30,  0,   0},
        {10000, 1000, 500, 500, 500, 250, 200, 200, 150, 0,   0}
    };

// PRIVATE FORWARD DECLARATIONS
static void print_win_line (int linenum, symbol sym, int count, ulong payout);
static void handle_any_scatter_wins ();
static void process_line (int linenum);

// GLOBAL FUNCTIONS
void init_engine ()
{
  init_gboard ();
  reset_stats ();
}

void spin_n_times (ulong n)
{
  for (ulong i = 0; i < n; i++)
    {
      num_spins++;
      update_gboard ();
      if (print_game_info)
        print_gboard (i);
      process_lines ();

      // Now handle board level scatter win
      handle_any_scatter_wins ();
    }
}

void process_lines ()
{
  for (int i = 0; i < N_ACTIVE_PAYLINES; i++)
    process_line (i);
}

// LOCAL FUNCTIONS
static void print_win_line (int linenum, symbol sym, int count, ulong payout)
{
  printf ("Line %2d: ", linenum);
  for (int j = 0; j < N_REELS; j++)
    printf ("%-3s", print_sym (lines[linenum][j]));
  printf (" => %d %s pays %lu credits.\n", count, print_sym (sym), payout);
}

static void handle_any_scatter_wins ()
{
  int count = 0;
  for (int i = 0; i < N_REELS; i++)
    for (int j = 0; j < N_ROWS; j++)
      if (gboard[j][i] == LT)
        {
          count++;
          break;
        }
  assert((count >= 0) && (count < 6));
  switch (count)
    {
      case 3:
        num_scatter_hits++;
      cum_scatter_wins += 5;
      if (print_game_info)
        printf ("[Scatter] => 3 scatters win 5 credits.\n");
      break;

      case 4:
        num_scatter_hits++;
      cum_scatter_wins += 25;
      if (print_game_info)
        printf ("[Scatter] => 4 scatters win 25 credits.\n");
      break;

      case 5:
        num_scatter_hits++;
      cum_scatter_wins += 200;
      if (print_game_info)
        printf ("[Scatter] => 5 scatters win 200 credits.\n");
      break;

      default:
        break;
    }
}

static void process_line (int linenum)
{
  symbol sym = lines[linenum][0];
  symbol alt_sym = WS;

  int count = 1; // count of matching symbols
  switch (sym)
    {
      case LO:
        for (int i = 1; i < 3; i++)
          if (sym == lines[linenum][i])
            count++;
      break;

      case LT:
        // Only set the count. All payoffs will be 0 in this function.
        // LT payouts are handled by function get_scatter_count
        for (int i = 1; i < N_REELS; i++)
          if (sym == lines[linenum][i])
            count++;
      break;

      case WS:
        for (int i = 1; i < N_REELS; i++)
          if ((lines[linenum][i] == sym) || (lines[linenum][i] == alt_sym))
            count++;
          else if ((lines[linenum][i] != LO) && (lines[linenum][i] != LT) && (alt_sym == WS))
            {
              alt_sym = lines[linenum][i];
              count++;
            }
          else
            break;

      sym = alt_sym; // count and sym are now set correctly

      // ANOMOLY FIXES
      // 3 wilds pay more than 4 of anything but lobstermania
      // 4 wilds pay more than 5 of anything but lobstermania
      // Take greatest win possible

      // Leading 4 wilds
      if ((lines[linenum][1] == WS) && (lines[linenum][2] == WS) && (lines[linenum][3] == WS)
          && (lines[linenum][4] != LM) && (lines[linenum][4] != WS))
        {
          sym = WS;
          count = 4;
        }

      // Leading 3 wilds
      if ((lines[linenum][1] == WS) && (lines[linenum][2] == WS) && (lines[linenum][3] != LM)
          && (lines[linenum][3] != WS) && (lines[linenum][4] != lines[linenum][3]) && (lines[linenum][4] != WS))
        {
          sym = WS;
          count = 3;
        }
      break; // case WS

      default:
        for (int i = 1; i < MAX_MATCHES; i++)
          {
            if ((lines[linenum][i] == sym) || (lines[linenum][i] == WS))
              count++;
            else
              break;
          }
    } // end switch

  // count variable now set for number of consecutive sym symbols (1 based)
  count--; // adjust for zero based indexing
  ulong payout = payouts[count][sym];

  if (payout > 0)
    {
      if (print_game_info)
        print_win_line (linenum, sym, count + 1, payout);

      num_line_hits++;
      cum_line_wins += payout;
    }
}
