#include "sg.h"
#include "gol.h"

void board_init(board *ptr) {
  for (int x = 0; x < BOARD_SIZE; ++x) {
    for (int y = 0; y < BOARD_SIZE; ++y) {
      ptr->current_gen[x][y] = 0;
    }
  }
  ptr->gen = 0;
}

void board_update(board *ptr) {
  for (int x = 0; x < BOARD_SIZE; ++x) {
    for (int y = 0; y < BOARD_SIZE; ++y) {
      if (alive_neighbors(ptr, x, y) == 2 || alive_neighbors(ptr, x, y) == 3) {
        ptr->next_gen[x][y] = 1;
      } else {
        ptr->next_gen[x][y] = 0;
      }
    }
  }
  for (int x = 0; x < BOARD_SIZE; ++x) {
    for (int y = 0; y < BOARD_SIZE; ++y) {
      ptr->current_gen[x][y] = ptr->next_gen[x][y];
    }
  }
  ptr->gen += 1;
}

void board_draw(board *ptr) {
  sg_clear();
  for (int x = 0; x < BOARD_SIZE; ++x) {
    for (int y = 0; y < BOARD_SIZE; ++y) {
       if (ptr->current_gen[x][y] == 0){
        sg_draw_rectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE);
      } else if (ptr->current_gen[x][y] == 1) {
        sg_fill_rectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE);
      }
    }
  }
}

int alive_neighbors(board *ptr, int x, int y) {
  int n = 0;
  for (int i = x - 1; i <= x + 1; ++i) {
    for (int j = y - 1; j <= y + 1; ++j) {
      n += ptr->current_gen[i][j];
    }
  }
  n -= 1;
  return n;
}

//  ----------------------------------------------------------------------------

void ic_blinker(board *ptr, int x, int y) {
  ptr->current_gen[x - 1][y] = 1;
  ptr->current_gen[x][y] = 1;
  ptr->current_gen[x + 1][y] = 1;
}
