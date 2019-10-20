//  À FAIRE :
//    - Perfectionner la fonction board_update pour prendre en compte les bords
//      du plateau
//    - Ajouter des fonctions d'initialisation de configurations de départ
//    - Afficher la génération actuelle et le nombre de cellules vivantes dans
//      la barre de titre
//    - Définir une structure contenant les informations utiles (n-ième
//      génération, nombre de cellules vivantes, etc)
//  ----------------------------------------------------------------------------

// gol.c : Le jeu de la vie, selon les règles de John Conway :
//    "À chaque étape, l’évolution d’une cellule est entièrement déterminée par
//    l’état de ses huit voisines de la façon suivante :
//
//    - Une cellule morte possédant exactement trois voisines vivantes devient
//        vivante (elle naît).
//    - Une cellule vivante possédant deux ou trois voisines vivantes le reste,
//        sinon elle meurt."
//    (https://fr.wikipedia.org/wiki/Jeu_de_la_vie)

#include <stdlib.h>
#include <stdio.h>
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

// Taille du plateau
#define BOARD_SIZE 50

// Taile d'une cellule en pixels
#define CELL_SIZE 20

typedef struct {
  int current_gen[BOARD_SIZE][BOARD_SIZE];
  int next_gen[BOARD_SIZE][BOARD_SIZE];
  int gen;
} board;

//  board_init : initialise le plateau pointé par ptr avec des celulles mortes
void board_init(board *ptr);

//  board_update : met à jour le plateau pointé par ptr selon les règles
//    précisées précedemment
void board_update(board *ptr);

//  board_draw : dessine le plateau pointé par ptr
void board_draw(board *ptr);

//  alive_neighbors : renvoie le nombre de voisins vivants de la cellule de
//    coordonnées x, y du plateau pointé par ptr
int alive_neighbors(board *ptr, int x, int y);

// --- FONCTION PRINCIPALE
// -----------------------------------------------------------------------------

int main(void) {
  // Initialisation
  srand((unsigned int) time(NULL));
  sg_open(WIDTH, HEIGHT, BGCOLOR, FGCOLOR, TITLE);
  board b;
  board_init(&b);
  b.current_gen[10][9] = 1;
  b.current_gen[9][10] = 1;
  b.current_gen[10][10] = 1;
  b.current_gen[11][10] = 1;
  b.current_gen[9][11] = 1;
  b.current_gen[11][11] = 1;
  b.current_gen[10][12] = 1;
  while (sg_get_key() != 'q') {
    board_draw(&b);
    board_update(&b);
    printf("Génération %d\n", b.gen);
  }
  sg_close();
  return EXIT_SUCCESS;
}

// --- DEVELOPPEMMENTS
// -----------------------------------------------------------------------------

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
