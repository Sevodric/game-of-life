#include "sg.h"
#include "gol.h"

#define FOR_EACH_CELL(X)                                                       \
  for (int x = 0; x < BOARD_SIZE; ++x) {                                       \
    for (int y = 0; y < BOARD_SIZE; ++y) {                                     \
      X                                                                        \
    }                                                                          \
  }

//  --- board_init
void board_init(board *ptr) {
  FOR_EACH_CELL(
    ptr->curr_gen[x][y] = 0;
    ptr->next_gen[x][y] = 0;
    )
  ptr->gen = 0;
}

//  --- board_update
void board_update(board *ptr) {
  FOR_EACH_CELL(
    if (ptr->curr_gen[x][y] == 1) {
      if (alive_neighbors(ptr, x, y) == 2 || alive_neighbors(ptr, x, y) == 3) {
        ptr->next_gen[x][y] = 1;
      } else {
        ptr->next_gen[x][y] = 0;
      }
    } else if (ptr->curr_gen[x][y] == 0) {
      if (alive_neighbors(ptr, x, y) == 3) {
        ptr->next_gen[x][y] = 1;
      } else {
        ptr->next_gen[x][y] = 0;
      }
    } else {
      ptr->next_gen[x][y] = ptr->curr_gen[x][y];
    }
  )
}

//  --- board_upgrade
void board_upgrade(board *ptr) {
  FOR_EACH_CELL(
    ptr->curr_gen[x][y] = ptr->next_gen[x][y];
  )
  ptr->gen += 1;
}

//  --- board_draw
void board_draw(board *ptr) {
  sg_clear();
  FOR_EACH_CELL(
    if (ptr->curr_gen[x][y] == 1) {
      sg_fill_rectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE);
    }
  )
}

//  --- alive_neighbors
int alive_neighbors(board *ptr, int x, int y) {
  int n = 0;
  for (int i = x - 1; i <= x + 1; ++i) {
    for (int j = y - 1; j <= y + 1; ++j) {
      n += ptr->curr_gen[i][j];
    }
  }
  n -= ptr->curr_gen[x][y];
  return n;
}

//  ----------------------------------------------------------------------------

//  --- ic_blinker
void ic_blinker(board *ptr, int x, int y) {
  ptr->curr_gen[x - 1][y] = 1;
  ptr->curr_gen[x][y] = 1;
  ptr->curr_gen[x + 1][y] = 1;
}

//  --- ic_glider
void ic_glider(board *ptr, int x, int y) {
  ptr->curr_gen[x][y - 1] = 1;
  ptr->curr_gen[x + 1][y] = 1;
  ptr->curr_gen[x + 1][y + 1] = 1;
  ptr->curr_gen[x][y + 1] = 1;
  ptr->curr_gen[x - 1][y + 1] = 1;
}
