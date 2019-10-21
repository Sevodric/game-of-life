#ifndef GOL__H
#define GOL__H

#define BOARD_SIZE 30
#define CELL_SIZE 30

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

//  ----------------------------------------------------------------------------

//  Quelques configurations initiales du jeu de la vie :
//  (https://en.wikipedia.org/wiki/Conway's_Game_of_Life#Examples_of_patterns)

//  Les fonctions ci-après défninies crééent des configurations initiales 
//    remarquables, dont un aperçu est donné au bout du lien ci-dessus, 
//    centrées, si possible, autour de la cellule de coordonnées x, y

void ic_blinker(board *ptr, int x, int y);

void ic_toad(board *ptr, int x, int y);

void ic_beacon(board *ptr, int x, int y);

void ic_pulsar(board *ptr, int x, int y);

void ic_glider(board *ptr, int x, int y);

void ic_lwss(board *ptr, int x, int y);

void ic_mwss(board *ptr, int x, int y);

void ic_hwss(board *ptr, int x, int y);

#endif
