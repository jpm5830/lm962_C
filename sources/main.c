// main.c
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "gameboard/gameboard.h"
#include "stats/stats.h"
#include "engine/engine.h"

int main ()
{
  print_game_info = FALSE;
  use_fixed_reels = TRUE;
  //ulong spins = 26000000000; // 26B
  //ulong spins = 26000000000; // 2.6B
  ulong spins = 300000000; // 300M
  //ulong spins = 10000000; // 10M
  ulong start_t = time (0);
  srand (time (0));
  init_engine ();
  //print_reels ();
  spin_n_times (spins);
  print_stats ();
  if (use_fixed_reels == FALSE)
    free_reels ();
  ulong end_t = time (0);
  ulong delta_seconds = end_t - start_t;
  printf ("\n%lu spins completed in %lu seconds.\n", spins, delta_seconds);
  return 0;
}
