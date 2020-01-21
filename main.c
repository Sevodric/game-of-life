/* TODO: 
 *  -> Adapt the board's size to a given argument
 *  -> Create a --help command
 *  -> Revamp the history system: save each boards and symply points to them
 */

#include <stdlib.h>
#include <stdio.h>
#include "sg.h"
#include "gol.h"

// Some colors
#define EINGRAU COLOR(22, 22, 29)
#define IVORY   COLOR(200, 200, 200)
#define GREEN   COLOR(53, 157, 65)

// Window properties
#define WIDTH 900
#define HEIGHT 900
#define BGCOLOR EINGRAU
#define FGCOLOR IVORY

int main(void) {
  // Initializes the board and the initial configurations
  board *b = board_init();
  if (b == NULL) {
    goto error_capacity;
  }
  //ic_blinker(b, 10, 10);
  //ic_toad(b, 20, 10);
  //ic_beacon(b, 30, 10);
  //ic_pulsar(b, 45, 10);
  //ic_glider(b, 10, 25);
  //ic_lwss(b, 20, 25);
  //ic_mwss(b, 20, 35);
  //ic_hwss(b, 20, 45);
  //ic_diehard(b, 50, 50);
  ic_rand(b);

  // Initializes the pressed key to SPACE in order to execute the first loop
  int key = 0;
  
  // Initializes the window's title, opens it  and draws the initial board
  sg_open(WIDTH, HEIGHT, BGCOLOR, FGCOLOR, "Game of Life");
  board_draw(b);
  
  // Main loop 
  while (1) {
    if (key == KEY_ESC) {
      break;
    }
    
    // If KEY_E is pressed down, enters the editing mode
    if (key == KEY_E) {
      board_edit(b);
      key = 0;
    }
    
    // If KEY_SPACE is pressed down, updates the board
    if (key == KEY_SPACE) {
      board_update(b);
      board_upgrade(b);
      board_draw(b);
    }
    
    // Displays information on the standard output
    board_displaycheckup(b);
    
    // Updates the pressed key
    key = sg_get_key();
  }
  
  int r = EXIT_SUCCESS;
  goto dispose;

error_capacity:
  fprintf(stderr, "*** Error: not enough memory\n");
  r = EXIT_FAILURE;
dispose:
  board_dispose(&b);
  sg_close();
  return r;
}
