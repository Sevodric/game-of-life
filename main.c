#include <stdlib.h>
#include "sg.h"

#define WIDTH 1280
#define HEIGHT 900
#define BGCOLOR BLACK
#define FGCOLOR WHITE
#define TITLE "Game of Life"

int main(void) {
  sg_open(WIDTH, HEIGHT, BGCOLOR, FGCOLOR, TITLE);
  while (sg_get_key() != 'q') {
    
  }
  sg_close();
  return EXIT_SUCCESS;
}
