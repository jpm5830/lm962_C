// File: stats.h
// Created by jpm on 5/8/21.
//

#ifndef _STATS_H_
#define _STATS_H_

typedef unsigned long ulong;

ulong num_spins; // +1 for each new game
ulong num_line_hits; // +1 for each line win (includes bonuses)
ulong num_scatter_hits; // +1 for each scatter win
ulong cum_line_wins; // cumulative credits won for line wins
ulong cum_scatter_wins; // cumulative credits won for scatter wins

// CALCULATED
extern double hit_rate;
extern double rtp;

// GLOBAL FUNCTIONS
void reset_stats ();
void print_stats ();

#endif //_STATS_H_
