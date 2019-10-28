#include <stdlib.h>
#include <time.h>
#include "gol.h"
#include "ic.h"

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
