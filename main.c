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

#define NCELL 100   // Nombre de cellules par lignes/colonnes
#define SCELL 10    // Taille d'une cellule en pixels

// Une cellule est définie par son coin supérieur gauche et son état binaire
//    0 = morte, 1 = vivante
typedef struct {
  double x;
  double y;
  int state;
} cell;

// board_init : initialise le plateau avec des cellules mortes
void board_init(cell board[][NCELL]);

// board_draw : dessine le plateau
void board_draw(cell board[][NCELL]);

// --- FONCTION PRINCIPALE
// -----------------------------------------------------------------------------

int main(void) {
  // Initialisation
  srand((unsigned int) time(NULL));
  cell board[NCELL][NCELL];
  board_init(board);
  sg_open(WIDTH, HEIGHT, BGCOLOR, FGCOLOR, TITLE);
  do {
    board_draw(board);
  } while (sg_get_key() != 'q');
  sg_close();
  return EXIT_SUCCESS;
}

// --- DEVELOPPEMMENTS
// -----------------------------------------------------------------------------

// --- board_init
void board_init(cell board[][NCELL]) {
  double x = 12;
  double y = 12;
  for (size_t i = 0; i < NCELL; i++) {
    for (size_t j = 0; j < NCELL; j++) {
      board[i][j] = (cell) {
        x, y, 0
      };
      x += SCELL;
    }
    x = 12;
    y += SCELL;
  }
}

void board_draw(cell board[][NCELL]) {
  for (int i = 0; i < NCELL; i++) {
    for (int j = 0; j < NCELL; j++) {
      if (board[i][j].state == 1) {
        sg_fill_rectangle((int) board[i][j].x, (int) board[i][j].y, SCELL,
            SCELL);
      }
    }
  }
}
