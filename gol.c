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
  ptr->curr_total = 0;
  ptr->next_total = 0;
}

void board_update(board *ptr) {
  FOR_EACH_CELL(
    if (ptr->curr_gen[x][y] == ALIVE) {
      if (alive_neighbors(ptr, x, y) == 2 || alive_neighbors(ptr, x, y) == 3) {
        ptr->next_gen[x][y] = ALIVE;
      } else {
        ptr->next_gen[x][y] = DEAD;
        ptr->next_total -= 1;
      }
    } else if (ptr->curr_gen[x][y] == DEAD) {
      if (alive_neighbors(ptr, x, y) == 3) {
        ptr->next_gen[x][y] = ALIVE;
        ptr->next_total += 1;
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
  ptr->curr_total = ptr->next_total;
}

void board_draw(board *ptr) {
  sg_clear();
  FOR_EACH_CELL(
    if (ptr->curr_gen[x][y] == ALIVE) {
      sg_fill_rectangle(x * CELL_SIZE + 1, y * CELL_SIZE + 1, CELL_SIZE - 1,
          CELL_SIZE - 1);
    }
  )
}

int alive_neighbors(board *ptr, int x, int y) {
  int n = 0;
  //  Si la cellule à évaluer est située sur le bord gauche, prend en compte les
  //    cellules situées sur le bord droit du plateau en lieu en place des
  //    inexistantes cellules de gauche. Si la cellule à évaluer est située sur
  //    le bord droit, applique réciproquement le même comportement. Sinon, 
  //    évalue les 8 cellules voisines de manière standard
  if (x == 0) {
    n += ptr->curr_gen[BOARD_SIZE - 1][y - 1];
    n += ptr->curr_gen[BOARD_SIZE - 1][y];
    n += ptr->curr_gen[BOARD_SIZE - 1][y + 1];
    n += ptr->curr_gen[x][y - 1];
    n += ptr->curr_gen[x + 1][y - 1];
    n += ptr->curr_gen[x + 1][y];
    n += ptr->curr_gen[x + 1][y + 1];
    n += ptr->curr_gen[x][y + 1];
  } else if (x == BOARD_SIZE - 1) {
    n += ptr->curr_gen[x][y - 1];
    n += ptr->curr_gen[x - 1][y - 1];
    n += ptr->curr_gen[x - 1][y];
    n += ptr->curr_gen[x - 1][y + 1];
    n += ptr->curr_gen[x][y + 1];
    n += ptr->curr_gen[0][y + 1];
    n += ptr->curr_gen[0][y];
    n += ptr->curr_gen[0][y - 1];
  } else {
    for (int i = x - 1; i <= x + 1; ++i) {
      for (int j = y - 1; j <= y + 1; ++j) {
        n += ptr->curr_gen[i][j];
      }
    }
    n -= ptr->curr_gen[x][y];
  }
  return n;
}

unsigned int alive_total(board *ptr) {
  unsigned int n = 0;
  FOR_EACH_CELL(
    n += (unsigned int) ptr->curr_gen[x][y];
  )
  return n;
}

//  ----------------------------------------------------------------------------

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
  FOR_EACH_CELL(
    ptr->curr_gen[x][y] = rand() % 2;
  )
}



