#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "sg.h"
#include "gol.h"

// Board and cells' size in pixels
#define CELL_SIZE 10

// Cell state
#define ALIVE true
#define DEAD false

// Some shortcuts
#define CURR(ptr, x, y) (ptr)->curr_gen[(x)][(y)]
#define NEXT(ptr, x, y) (ptr)->next_gen[(x)][(y)]

#define BOARD_SIZE 90

struct board {
  bool curr_gen[BOARD_SIZE][BOARD_SIZE];
  bool next_gen[BOARD_SIZE][BOARD_SIZE];
  size_t gen;
  size_t curr_total;
  size_t next_total;
};

//  alive__nghb: returns the amount of living cells in the neighborhood of the
//    cell of coordinate x, y on the board pointed to by ptr.
static int alive__nghb(board *ptr, int x, int y) {
  int n = 0;
  if (x == 0) {
    n += CURR(ptr, BOARD_SIZE - 1, y - 1);
    n += CURR(ptr, BOARD_SIZE - 1, y);
    n += CURR(ptr, BOARD_SIZE - 1, y + 1);
    n += CURR(ptr, x, y - 1);
    n += CURR(ptr, x + 1, y - 1);
    n += CURR(ptr, x + 1, y);
    n += CURR(ptr, x + 1, y + 1);
    n += CURR(ptr, x, y + 1);
  } else if (x == BOARD_SIZE - 1) {
    n += CURR(ptr, x, y - 1);
    n += CURR(ptr, x - 1, y - 1);
    n += CURR(ptr, x - 1, y);
    n += CURR(ptr, x - 1, y + 1);
    n += CURR(ptr, x, y + 1);
    n += CURR(ptr, 0, y + 1);
    n += CURR(ptr, 0, y);
    n += CURR(ptr, 0, y - 1);
  } else {
    for (int i = x - 1; i <= x + 1; ++i) {
      for (int j = y - 1; j <= y + 1; ++j) {
        n += CURR(ptr, i, j);
      }
    }
    n -= CURR(ptr, x, y);
  }
  return n;
}

board *board_init(void) {
  board *ptr = malloc(sizeof(*ptr));
  if (ptr == NULL) {
    return NULL;
  }
  for (int x = 0; x < BOARD_SIZE; ++x) {
    for (int y = 0; y < BOARD_SIZE; ++y) {
      CURR(ptr, x, y) = DEAD;
      NEXT(ptr, x, y) = DEAD;
    }
  }
  ptr->gen = 0;
  ptr->curr_total = 0;
  ptr->next_total = 0;
  return ptr;
}

void board_update(board *ptr) {
  for (int x = 0; x < BOARD_SIZE; ++x) {
    for (int y = 0; y < BOARD_SIZE; ++y) {
      int n = alive__nghb(ptr, x, y);
      if (CURR(ptr, x, y) == ALIVE) {
        if (n == 2 || n == 3) {
          NEXT(ptr, x, y) = ALIVE;
        } else {
          NEXT(ptr, x, y) = DEAD;
          ptr->next_total -= 1;
        }
      } else if (CURR(ptr, x, y) == DEAD) {
        if (n == 3) {
          NEXT(ptr, x, y) = ALIVE;
          ptr->next_total += 1;
        } else {
          NEXT(ptr, x, y) = DEAD;
        }
      } else {
        NEXT(ptr, x, y) = CURR(ptr, x, y);
      }
    }
  }
}

void board_upgrade(board *ptr) {
  for (int x = 0; x < BOARD_SIZE; ++x) {
    for (int y = 0; y < BOARD_SIZE; ++y) {
      CURR(ptr, x, y) = NEXT(ptr, x, y);
    }
  }
  ptr->gen += 1;
  ptr->curr_total = ptr->next_total;
}

void board_draw(const board *ptr) {
  sg_clear();
  for (int x = 0; x < BOARD_SIZE; ++x) {
    for (int y = 0; y < BOARD_SIZE; ++y) {
      if (CURR(ptr, x, y) == ALIVE) {
        sg_fill_rectangle(x * CELL_SIZE + 1, y * CELL_SIZE + 1, CELL_SIZE - 1,
            CELL_SIZE - 1);
      }
    }
  }
}

size_t alive_total(const board *ptr) {
  return ptr->curr_total;
}

void board_edit(board *ptr) {
  // Initiliazes the key pressed and defines the cursor coordonates at the
  //    midle of the board
  int key = 0;
  int x = BOARD_SIZE / 2;
  int y = BOARD_SIZE / 2;
  
  while (1) {
    // Draws the cursor
    sg_set_fgcolor(RED);
    sg_draw_rectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE);
    
    key = sg_get_key();
   
    // If KEY_SPACE is pressed, changes the cell's state to the opposite
    if (key == KEY_SPACE) {
      if (CURR(ptr, x, y) == ALIVE) {
        CURR(ptr, x, y) = DEAD;
        ptr->curr_total -= 1;
        ptr->next_total -= 1;
        sg_set_fgcolor(EINGRAU);
        sg_fill_rectangle(x * CELL_SIZE + 1, y * CELL_SIZE + 1, CELL_SIZE,
            CELL_SIZE);
        sg_set_fgcolor(IVORY);
      } else {
        CURR(ptr, x, y) = ALIVE;
        ptr->curr_total += 1;
        ptr->next_total += 1;
        sg_set_fgcolor(GREEN);
        sg_fill_rectangle(x * CELL_SIZE + 1, y * CELL_SIZE + 1, CELL_SIZE,
            CELL_SIZE);
      }
    }

    // If KEY_C is pressed, clears the whole board
    if (key == KEY_C) {
      sg_set_fgcolor(EINGRAU);
      for (int x = 0; x < BOARD_SIZE; ++x) {
        for (int y = 0; y < BOARD_SIZE; ++y) {
          ptr->curr_gen[x][y] = DEAD;
          sg_fill_rectangle(x * CELL_SIZE + 1, y * CELL_SIZE + 1, CELL_SIZE,
              CELL_SIZE);
        }
      }
      ptr->curr_total = 0;
      ptr->next_total = 0;
    }

    // Erases the previous cursor
    sg_set_fgcolor(EINGRAU);
    sg_draw_rectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE);

    switch (key) {
      case KEY_RIGHT:
        x = (x == BOARD_SIZE - 1) ? 0 : x + 1;
        break;
      case KEY_LEFT:
        x = (x == 0) ? BOARD_SIZE - 1 : x - 1;
        break;
      case KEY_DOWN:
        y = (y == BOARD_SIZE - 1) ? 0 : y + 1;
        break;
      case KEY_UP:
        y = (y == 0) ? BOARD_SIZE - 1 : y - 1;
        break;
      case KEY_ESC: // exit the editing mode
        sg_set_fgcolor(IVORY);
        return;
    }
  }
}

void board_dispose(board **pp) {
  if (*pp == NULL) {
    return;
  }
  free(*pp);
  *pp = NULL;
}

void board_displaycheckup(const board *ptr) {
  printf("CHECKUP: GEN = %zu; ALIVE CELLS = %zu\n", ptr->gen, ptr->curr_total);
  return;
}

// =============================================================================

void ic_blinker(board *ptr, int x, int y) {
  ptr->curr_gen[x - 1][y] = ALIVE;
  ptr->curr_gen[x][y] = ALIVE;
  ptr->curr_gen[x + 1][y] = ALIVE;
}

void ic_toad(board *ptr, int x, int y) {
  ptr->curr_gen[x][y] = ALIVE;
  ptr->curr_gen[x + 1][y] = ALIVE;
  ptr->curr_gen[x + 2][y] = ALIVE;
  ptr->curr_gen[x - 1][y + 1] = ALIVE;
  ptr->curr_gen[x][y + 1] = ALIVE;
  ptr->curr_gen[x + 1][y + 1] = ALIVE;
}

void ic_beacon(board *ptr, int x, int y) {
  ptr->curr_gen[x][y] = ALIVE;
  ptr->curr_gen[x - 1][y] = ALIVE;
  ptr->curr_gen[x - 1][y - 1] = ALIVE;
  ptr->curr_gen[x][y -1] = ALIVE;
  ptr->curr_gen[x + 1][y + 1] = ALIVE;
  ptr->curr_gen[x + 2][y + 1] = ALIVE;
  ptr->curr_gen[x + 2][y + 2] = ALIVE;
  ptr->curr_gen[x + 1][y + 2] = ALIVE;
}

void ic_pulsar(board *ptr, int x, int y) {
  ptr->curr_gen[x - 1][y - 2] = ALIVE;
  ptr->curr_gen[x - 1][y - 3] = ALIVE;
  ptr->curr_gen[x - 1][y - 4] = ALIVE;
  ptr->curr_gen[x - 2][y - 1] = ALIVE;
  ptr->curr_gen[x - 3][y - 1] = ALIVE;
  ptr->curr_gen[x - 4][y - 1] = ALIVE;
  ptr->curr_gen[x - 6][y - 2] = ALIVE;
  ptr->curr_gen[x - 6][y - 3] = ALIVE;
  ptr->curr_gen[x - 6][y - 4] = ALIVE;
  ptr->curr_gen[x - 2][y - 6] = ALIVE;
  ptr->curr_gen[x - 3][y - 6] = ALIVE;
  ptr->curr_gen[x - 4][y - 6] = ALIVE;
 
  ptr->curr_gen[x + 1][y - 2] = ALIVE;
  ptr->curr_gen[x + 1][y - 3] = ALIVE;
  ptr->curr_gen[x + 1][y - 4] = ALIVE;
  ptr->curr_gen[x + 2][y - 1] = ALIVE;
  ptr->curr_gen[x + 3][y - 1] = ALIVE;
  ptr->curr_gen[x + 4][y - 1] = ALIVE;
  ptr->curr_gen[x + 6][y - 2] = ALIVE;
  ptr->curr_gen[x + 6][y - 3] = ALIVE;
  ptr->curr_gen[x + 6][y - 4] = ALIVE;
  ptr->curr_gen[x + 2][y - 6] = ALIVE;
  ptr->curr_gen[x + 3][y - 6] = ALIVE;
  ptr->curr_gen[x + 4][y - 6] = ALIVE;
  
  ptr->curr_gen[x + 1][y + 2] = ALIVE;
  ptr->curr_gen[x + 1][y + 3] = ALIVE;
  ptr->curr_gen[x + 1][y + 4] = ALIVE;
  ptr->curr_gen[x + 2][y + 1] = ALIVE;
  ptr->curr_gen[x + 3][y + 1] = ALIVE;
  ptr->curr_gen[x + 4][y + 1] = ALIVE;
  ptr->curr_gen[x + 6][y + 2] = ALIVE;
  ptr->curr_gen[x + 6][y + 3] = ALIVE;
  ptr->curr_gen[x + 6][y + 4] = ALIVE;
  ptr->curr_gen[x + 2][y + 6] = ALIVE;
  ptr->curr_gen[x + 3][y + 6] = ALIVE;
  ptr->curr_gen[x + 4][y + 6] = ALIVE;
  
  ptr->curr_gen[x - 1][y + 2] = ALIVE;
  ptr->curr_gen[x - 1][y + 3] = ALIVE;
  ptr->curr_gen[x - 1][y + 4] = ALIVE;
  ptr->curr_gen[x - 2][y + 1] = ALIVE;
  ptr->curr_gen[x - 3][y + 1] = ALIVE;
  ptr->curr_gen[x - 4][y + 1] = ALIVE;
  ptr->curr_gen[x - 6][y + 2] = ALIVE;
  ptr->curr_gen[x - 6][y + 3] = ALIVE;
  ptr->curr_gen[x - 6][y + 4] = ALIVE;
  ptr->curr_gen[x - 2][y + 6] = ALIVE;
  ptr->curr_gen[x - 3][y + 6] = ALIVE;
  ptr->curr_gen[x - 4][y + 6] = ALIVE;
}

void ic_glider(board *ptr, int x, int y) {
  ptr->curr_gen[x][y - 1] = ALIVE;
  ptr->curr_gen[x + 1][y] = ALIVE;
  ptr->curr_gen[x + 1][y + 1] = ALIVE;
  ptr->curr_gen[x][y + 1] = ALIVE;
  ptr->curr_gen[x - 1][y + 1] = ALIVE;
}

void ic_lwss(board *ptr, int x, int y) {
  ptr->curr_gen[x][y - 1] = ALIVE;
  ptr->curr_gen[x - 1][y - 1] = ALIVE;
  ptr->curr_gen[x + 1][y - 1] = ALIVE;
  ptr->curr_gen[x + 2][y - 1] = ALIVE;
  ptr->curr_gen[x - 2][y] = ALIVE;
  ptr->curr_gen[x + 2][y] = ALIVE;
  ptr->curr_gen[x + 2][y + 1] = ALIVE;
  ptr->curr_gen[x + 1][y + 2] = ALIVE;
  ptr->curr_gen[x - 3][y + 2] = ALIVE;
}

void ic_mwss(board *ptr, int x, int y) {
  ptr->curr_gen[x][y - 1] = ALIVE;
  ptr->curr_gen[x - 1][y - 1] = ALIVE;
  ptr->curr_gen[x + 1][y - 1] = ALIVE;
  ptr->curr_gen[x + 2][y - 1] = ALIVE;
  ptr->curr_gen[x + 3][y - 1] = ALIVE;
  ptr->curr_gen[x - 2][y] = ALIVE;
  ptr->curr_gen[x + 3][y] = ALIVE;
  ptr->curr_gen[x + 3][y + 1] = ALIVE;
  ptr->curr_gen[x + 2][y + 2] = ALIVE;
  ptr->curr_gen[x - 3][y + 2] = ALIVE;
  ptr->curr_gen[x][y + 3] = ALIVE;
}

void ic_hwss(board *ptr, int x, int y) {
  ptr->curr_gen[x - 3][y - 1] = ALIVE;
  ptr->curr_gen[x - 2][y - 2] = ALIVE;
  ptr->curr_gen[x - 1][y - 2] = ALIVE;
  ptr->curr_gen[x][y - 2] = ALIVE;
  ptr->curr_gen[x + 1][y - 2] = ALIVE;
  ptr->curr_gen[x + 2][y - 2] = ALIVE;
  ptr->curr_gen[x + 3][y - 2] = ALIVE;
  ptr->curr_gen[x + 3][y - 1] = ALIVE;
  ptr->curr_gen[x + 3][y] = ALIVE;
  ptr->curr_gen[x + 2][y + 1] = ALIVE;
  ptr->curr_gen[x][y + 2] = ALIVE;
  ptr->curr_gen[x - 1][y + 2] = ALIVE;
  ptr->curr_gen[x - 3][y + 1] = ALIVE;
}

void ic_rpentomino(board *ptr, int x, int y) {
  ptr->curr_gen[x - 1][y] = ALIVE;
  ptr->curr_gen[x + 1][y - 1] = ALIVE;
  ptr->curr_gen[x][y - 1] = ALIVE;
  ptr->curr_gen[x][y] = ALIVE;
  ptr->curr_gen[x][y + 1] = ALIVE;
}

void ic_diehard(board *ptr, int x, int y) {
  ptr->curr_gen[x - 2][y] = ALIVE;
  ptr->curr_gen[x - 3][y] = ALIVE;
  ptr->curr_gen[x - 2][y + 1] = ALIVE;
  ptr->curr_gen[x + 3][y - 1] = ALIVE;
  ptr->curr_gen[x + 2][y + 1] = ALIVE;
  ptr->curr_gen[x + 3][y + 1] = ALIVE;
  ptr->curr_gen[x + 4][y + 1] = ALIVE;
}

void ic_acorn(board *ptr, int x, int y) {
  ptr->curr_gen[x - 1][y - 1] = ALIVE;
  ptr->curr_gen[x - 1][y + 1] = ALIVE;
  ptr->curr_gen[x - 2][y + 1] = ALIVE;
  ptr->curr_gen[x + 1][y] = ALIVE;
  ptr->curr_gen[x + 2][y + 1] = ALIVE;
  ptr->curr_gen[x + 3][y + 1] = ALIVE;
  ptr->curr_gen[x + 4][y + 1] = ALIVE;
}

void ic_rand(board *ptr) {
  srand((unsigned int) time(NULL));
  for (int x = 0; x < BOARD_SIZE; ++x) {
    for (int y = 0; y < BOARD_SIZE; ++y) {
      ptr->curr_gen[x][y] = rand() % 2;
    }
  }
}
