// File: stats.c
// Created by jpm on 5/8/21.
//

#include <stdio.h>
#include "stats.h"
#include "../engine/engine.h"

// COUNTERS
ulong num_spins; // +1 for each new game
ulong num_line_hits; // +1 for each line win
ulong num_scatter_hits; // +1 for each scatter win
ulong cum_line_wins; // cumulative credits won for line wins
ulong cum_scatter_wins; // cumulative credits won for scatter wins

// CALCULATED
double hit_rate;
double rtp;

// GLOBAL FUNCTIONS
void reset_stats ()
{
}

void print_stats ()
{
  ulong total_hits = num_line_hits + num_scatter_hits;
  ulong total_winnings = cum_line_wins + cum_scatter_wins;
  ulong total_lines_played = N_ACTIVE_PAYLINES * num_spins;
  hit_rate = (double) total_hits / ((double) total_lines_played) * 100.0;
  rtp = (double) total_winnings / ((double) num_spins * (double) N_ACTIVE_PAYLINES) * 100.0;
  printf ("\nSpins: %lu  Lines Played: %lu  PAYLINES: %d\n", num_spins, total_lines_played, N_ACTIVE_PAYLINES);
  printf ("Hit Rate: %0.1f%%  Payback: %0.1f%%\n", hit_rate, rtp);
  printf ("HITS:  Line: %-12lu  Scatter: %-12lu  Total: %-12lu\n", num_line_hits, num_scatter_hits, total_hits);
  printf ("WINS:  Line: %-12lu  Scatter: %-12lu  Total: %-12lu\n", cum_line_wins, cum_scatter_wins, total_winnings);
}
