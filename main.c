// main.c
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "gameboard.h"
#include "stats.h"
#include "engine.h"

int main ()
{
  print_game_info = FALSE;
  long spins = 1000000;
  unsigned long start_t = time (0);
  srand (time (0));
  init_engine ();
  spin_n_times (spins);
  print_stats ();
  free_reels (); // allocated heap memory
  unsigned long end_t = time (0);
  unsigned long delta_seconds = end_t - start_t;
  printf ("\n%ld spins completed in %ld seconds.\n", spins, delta_seconds);
  return 0;
}
