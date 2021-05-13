// File: engine.h
// Created by jpm on 5/7/21.
//

/// Defines spin and payout functions

#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "gameboard.h"

#define MAX_MATCHES 5
#define N_ACTIVE_PAYLINES 1

extern bool print_game_info; // TRUE or FALSE

// GLOBAL FUNCTIONS
void init_engine ();
void spin_n_times (ulong n);
void process_lines ();

#endif //_ENGINE_H_
