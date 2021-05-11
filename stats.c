// File: stats.c
// Created by jpm on 5/8/21.
//

#include <stdio.h>
#include "stats.h"
#include "engine.h"

// COUNTERS
long num_spins;
long num_hits;
long num_line_wins;
long num_bonuses;
long num_scatters;
long num_jackpots;
long cum_line_wins;
long cum_bonus_wins;
long cum_scatter_wins;
long cum_jackpot_wins;

// CALCULATED
double hit_rate;
double rtp;

// GLOBAL FUNCTIONS
void reset_stats ()
{
  num_spins = 0;
  num_hits = 0;
  num_bonuses = 0;
  num_scatters = 0;
  num_jackpots = 0;
  cum_line_wins = 0;
  cum_bonus_wins = 0;
  cum_scatter_wins = 0;
  cum_jackpot_wins = 0;
}

void print_stats ()
{
  long total_hits = num_hits + num_scatters + num_bonuses;
  long total_winnings = cum_line_wins + cum_scatter_wins + cum_bonus_wins;
  hit_rate = (double) total_hits / ((double) num_spins * (double) N_ACTIVE_PAYLINES) * 100.0;
  rtp = (double) total_winnings / ((double) num_spins * (double) N_ACTIVE_PAYLINES) * 100.0;
  printf ("Spins: %ld  Hits: %ld  Hit Rate: %0.1f%%  Payback: %0.1f%%", num_spins, num_hits, hit_rate, rtp);
}
