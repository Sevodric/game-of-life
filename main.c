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
#define TITLE "Game of Life"

int main(void) {
  sg_open(WIDTH, HEIGHT, BGCOLOR, FGCOLOR, TITLE);
  board b;
  board_init(&b);  
  
  // Quelques configurations initiales
  ic_blinker(&b, 10, 10);
  ic_toad(&b, 20, 10);
  ic_beacon(&b, 30, 10);
  ic_pulsar(&b, 45, 10);
  ic_glider(&b, 10, 25);
  ic_lwss(&b, 20, 25);
  ic_mwss(&b, 20, 35);
  ic_hwss(&b, 20, 45);
  
  board_draw(&b);
  printf("Génération %d\n", b.gen);
  while (sg_get_key() != 'q') {
    board_update(&b);
    board_upgrade(&b);
    board_draw(&b);
    printf("Génération %d\n", b.gen);
  }
  sg_close();
  return EXIT_SUCCESS;
}
