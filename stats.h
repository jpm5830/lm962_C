// File: stats.h
// Created by jpm on 5/8/21.
//

#ifndef _STATS_H_
#define _STATS_H_

// COUNTERS
extern long num_spins;
extern long num_hits;
extern long num_line_wins; // regular line wins only (no LO or LT)
extern long num_bonuses;
extern long num_scatters;
extern long num_jackpots;
extern long cum_line_wins;
extern long cum_bonus_wins;
extern long cum_scatter_wins;
extern long cum_jackpot_wins;

// CALCULATED
extern double hit_rate;
extern double rtp;

// GLOBAL FUNCTIONS
void reset_stats ();
void print_stats ();

#endif //_STATS_H_
