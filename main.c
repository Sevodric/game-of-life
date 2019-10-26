#include <stdlib.h>
#include <stdio.h>
#include "sg.h"
#include "gol.h"

#define EINGRAU COLOR(22, 22, 29)
#define IVORY   COLOR(200, 200, 200)

#define WIDTH 1000
#define HEIGHT 1000
#define BGCOLOR EINGRAU
#define FGCOLOR IVORY
#define INST "('space' = next gen, 'q' = quit)"

int main(void) {
  // Initialisation du plateau et des éventuelles configurations initiales
  board b;
  board_init(&b);
  ic_blinker(&b, 10, 10);
  ic_toad(&b, 20, 10);
  ic_beacon(&b, 30, 10);
  ic_pulsar(&b, 45, 10);
  ic_glider(&b, 10, 25);
  ic_lwss(&b, 20, 25);
  ic_mwss(&b, 20, 35);
  ic_hwss(&b, 20, 45);
  b.curr_total = alive_total(&b);
  
  char title[100];
  int key = 0;
  sprintf(title, "Life : %uth generation , %u alive cells", b.gen,
      b.curr_total);
  sg_open(WIDTH, HEIGHT, BGCOLOR, FGCOLOR, title);

  // Boucle principale
  do (key != 'q') {
    board_update(&b);
    board_upgrade(&b);
    board_draw(&b);
    sprintf(title, "Life : %uth generation , %u aliv cells", b.gen,
        b.curr_total);
    sg_set_title(title);
    key = sg_get_key();
  } while
  sg_close();
  return EXIT_SUCCESS;
}
