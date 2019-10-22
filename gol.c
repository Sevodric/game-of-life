#include <stdlib.h>
#include <time.h>
#include "sg.h"
#include "gol.h"

#define ALIVE 1
#define DEAD 0
#define FOR_EACH_CELL(X)                                                       \
  for (int x = 0; x < BOARD_SIZE; ++x) {                                       \
    for (int y = 0; y < BOARD_SIZE; ++y) {                                     \
      X                                                                        \
    }                                                                          \
  }


void board_init(board *ptr) {
  FOR_EACH_CELL(
    ptr->curr_gen[x][y] = DEAD;
    ptr->next_gen[x][y] = DEAD;
    )
  ptr->gen = 0;
}

void board_update(board *ptr) {
  FOR_EACH_CELL(
    if (ptr->curr_gen[x][y] == ALIVE) {
      if (alive_neighbors(ptr, x, y) == 2 || alive_neighbors(ptr, x, y) == 3) {
        ptr->next_gen[x][y] = ALIVE;
      } else {
        ptr->next_gen[x][y] = DEAD;
      }
    } else if (ptr->curr_gen[x][y] == DEAD) {
      if (alive_neighbors(ptr, x, y) == 3) {
        ptr->next_gen[x][y] = ALIVE;
      } else {
        ptr->next_gen[x][y] = DEAD;
      }
    } else {
      ptr->next_gen[x][y] = ptr->curr_gen[x][y];
    }
  )
}

void board_upgrade(board *ptr) {
  FOR_EACH_CELL(
    ptr->curr_gen[x][y] = ptr->next_gen[x][y];
  )
  ptr->gen += 1;
}

void board_draw(board *ptr) {
  sg_clear();
  FOR_EACH_CELL(
    if (ptr->curr_gen[x][y] == ALIVE) {
      sg_fill_rectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE);
    }
  )
}

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

void ic_blinker(board *ptr, int x, int y) {
  ptr->curr_gen[x - 1][y] = 1;
  ptr->curr_gen[x][y] = 1;
  ptr->curr_gen[x + 1][y] = 1;
}

void ic_toad(board *ptr, int x, int y) {
  ptr->curr_gen[x][y] = 1;
  ptr->curr_gen[x + 1][y] = 1;
  ptr->curr_gen[x + 2][y] = 1;
  ptr->curr_gen[x - 1][y + 1] = 1;
  ptr->curr_gen[x][y + 1] = 1;
  ptr->curr_gen[x + 1][y + 1] = 1;
}

void ic_beacon(board *ptr, int x, int y) {
  ptr->curr_gen[x][y] = 1;
  ptr->curr_gen[x - 1][y] = 1;
  ptr->curr_gen[x - 1][y - 1] = 1;
  ptr->curr_gen[x][y -1] = 1;
  ptr->curr_gen[x + 1][y + 1] = 1;
  ptr->curr_gen[x + 2][y + 1] = 1;
  ptr->curr_gen[x + 2][y + 2] = 1;
  ptr->curr_gen[x + 1][y + 2] = 1;
}

void ic_pulsar(board *ptr, int x, int y) {
  ptr->curr_gen[x - 1][y - 2] = 1;
  ptr->curr_gen[x - 1][y - 3] = 1;
  ptr->curr_gen[x - 1][y - 4] = 1;
  ptr->curr_gen[x - 2][y - 1] = 1;
  ptr->curr_gen[x - 3][y - 1] = 1;
  ptr->curr_gen[x - 4][y - 1] = 1;
  ptr->curr_gen[x - 6][y - 2] = 1;
  ptr->curr_gen[x - 6][y - 3] = 1;
  ptr->curr_gen[x - 6][y - 4] = 1;
  ptr->curr_gen[x - 2][y - 6] = 1;
  ptr->curr_gen[x - 3][y - 6] = 1;
  ptr->curr_gen[x - 4][y - 6] = 1;
 
  ptr->curr_gen[x + 1][y - 2] = 1;
  ptr->curr_gen[x + 1][y - 3] = 1;
  ptr->curr_gen[x + 1][y - 4] = 1;
  ptr->curr_gen[x + 2][y - 1] = 1;
  ptr->curr_gen[x + 3][y - 1] = 1;
  ptr->curr_gen[x + 4][y - 1] = 1;
  ptr->curr_gen[x + 6][y - 2] = 1;
  ptr->curr_gen[x + 6][y - 3] = 1;
  ptr->curr_gen[x + 6][y - 4] = 1;
  ptr->curr_gen[x + 2][y - 6] = 1;
  ptr->curr_gen[x + 3][y - 6] = 1;
  ptr->curr_gen[x + 4][y - 6] = 1;
  
  ptr->curr_gen[x + 1][y + 2] = 1;
  ptr->curr_gen[x + 1][y + 3] = 1;
  ptr->curr_gen[x + 1][y + 4] = 1;
  ptr->curr_gen[x + 2][y + 1] = 1;
  ptr->curr_gen[x + 3][y + 1] = 1;
  ptr->curr_gen[x + 4][y + 1] = 1;
  ptr->curr_gen[x + 6][y + 2] = 1;
  ptr->curr_gen[x + 6][y + 3] = 1;
  ptr->curr_gen[x + 6][y + 4] = 1;
  ptr->curr_gen[x + 2][y + 6] = 1;
  ptr->curr_gen[x + 3][y + 6] = 1;
  ptr->curr_gen[x + 4][y + 6] = 1;
  
  ptr->curr_gen[x - 1][y + 2] = 1;
  ptr->curr_gen[x - 1][y + 3] = 1;
  ptr->curr_gen[x - 1][y + 4] = 1;
  ptr->curr_gen[x - 2][y + 1] = 1;
  ptr->curr_gen[x - 3][y + 1] = 1;
  ptr->curr_gen[x - 4][y + 1] = 1;
  ptr->curr_gen[x - 6][y + 2] = 1;
  ptr->curr_gen[x - 6][y + 3] = 1;
  ptr->curr_gen[x - 6][y + 4] = 1;
  ptr->curr_gen[x - 2][y + 6] = 1;
  ptr->curr_gen[x - 3][y + 6] = 1;
  ptr->curr_gen[x - 4][y + 6] = 1;
}

void ic_glider(board *ptr, int x, int y) {
  ptr->curr_gen[x][y - 1] = 1;
  ptr->curr_gen[x + 1][y] = 1;
  ptr->curr_gen[x + 1][y + 1] = 1;
  ptr->curr_gen[x][y + 1] = 1;
  ptr->curr_gen[x - 1][y + 1] = 1;
}

void ic_lwss(board *ptr, int x, int y);
void ic_mwss(board *ptr, int x, int y);
void ic_hwss(board *ptr, int x, int y);

void ic_rpentomino(board *ptr, int x, int y);
void ic_diehard(board *ptr, int x, int y);

void ic_acorn(board *ptr, int x, int y) {
  ptr->curr_gen[x - 1][y - 1] = 1;
  ptr->curr_gen[x - 1][y + 1] = 1;
  ptr->curr_gen[x - 2][y + 1] = 1;
  ptr->curr_gen[x + 1][y] = 1;
  ptr->curr_gen[x + 2][y + 1] = 1;
  ptr->curr_gen[x + 3][y + 1] = 1;
  ptr->curr_gen[x + 4][y + 1] = 1;
}

void ic_rand(board *ptr) {
  srand((unsigned int) time(NULL));
  FOR_EACH_CELL(
    ptr->curr_gen[x][y] = rand() % 2;
  )
}



