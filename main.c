#include <stdlib.h>
#include <time.h>
#include "sg.h"

// --- DEFINITIONS DIVERSES
// -----------------------------------------------------------------------------

// Propriétés de la fenêtre
#define WIDTH 1024
#define HEIGHT 1024
#define BGCOLOR BLACK
#define FGCOLOR WHITE
#define TITLE "Game of Life"

// Nombre de cellules par lignes/colonnes
#define NCELL 20

typedef struct {
  double x;
  double y;
  int state;
} cell;

// board_init : initialise les éléments du tableau à deux dimensions de taille n
//    pointé par base.
void board_init(cell *base, size_t n);

// --- FONCTION PRINCIPALE
// -----------------------------------------------------------------------------

int main(void) {
  // Initialisation
  srand((unsigned int) time(NULL));
  cell board[NCELL];
  board_init(board, NCELL);
  sg_open(WIDTH, HEIGHT, BGCOLOR, FGCOLOR, TITLE);
  while (sg_get_key() != 'q') {
    for (int i = 0; i < NCELL; i++) {
      if (board[i].state == 1) {
        sg_fill_rectangle((int) board[i].x, (int) board[i].y, 50, 50);
      } else {
        sg_draw_rectangle((int) board[i].x, (int) board[i].y, 50, 50);
      }
    }
  }
  sg_close();
  return EXIT_SUCCESS;
}

// --- DEVELOPPEMMENTS
// -----------------------------------------------------------------------------

// --- board_init
void board_init(cell *base, size_t n) {
  double x = 12;
  double y = 12;
  for (size_t i = 0; i < n; i++) {
    base[i] = (cell) {
      x, y, 0
    };
    x += 50;
  }
}
