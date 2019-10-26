#ifndef GOL__H
#define GOL__H

#define BOARD_SIZE 100
#define CELL_SIZE 10

typedef struct {
  int curr_gen[BOARD_SIZE][BOARD_SIZE];
  int next_gen[BOARD_SIZE][BOARD_SIZE];
  unsigned int gen;
  unsigned int curr_total;
  unsigned int next_total;
} board;

//  board_init : initialise le plateau pointé par ptr avec des celulles mortes
extern void board_init(board *ptr);

//  board_update : prépare la mise à jour du plateau pointé par ptr selon les
//    règles précisées précedemment
extern void board_update(board *ptr);

//  board_upgrade : applique la mise à jour effectuée par board_update sur le
//    plateau pointé par ptr
extern void board_upgrade(board *ptr);

//  board_draw : dessine le plateau pointé par ptr
extern void board_draw(board *ptr);

//  alive_neighbors : renvoie le nombre de cellules voisines vivantes de la
//    cellule de coordonnées x, y du plateau pointé par ptr
extern int alive_neighbors(board *ptr, int x, int y);

//  alive_total : renvoie le nombre de cellules vivantes du plateau pointé par
//    ptr
unsigned int alive_total(board *ptr);

//  ----------------------------------------------------------------------------

//  Quelques configurations initiales du jeu de la vie :
//  (https://en.wikipedia.org/wiki/Conway's_Game_of_Life#Examples_of_patterns)
//  Les fonctions suivantes crééent des configurations initiales remarquables,
//    dont un aperçu est donné au bout du lien ci-dessus. Les figures sont
//    centrées, si possible, autour de la cellule de coordonnées x, y

//  Oscillateurs
extern void ic_blinker(board *ptr, int x, int y);
extern void ic_toad(board *ptr, int x, int y);
extern void ic_beacon(board *ptr, int x, int y);
extern void ic_pulsar(board *ptr, int x, int y);

//  Vaisseaux
extern void ic_glider(board *ptr, int x, int y);
extern void ic_lwss(board *ptr, int x, int y);
extern void ic_mwss(board *ptr, int x, int y);
extern void ic_hwss(board *ptr, int x, int y);

//  Mathusalems
extern void ic_rpentomino(board *ptr, int x, int y);
extern void ic_diehard(board *ptr, int x, int y);
extern void ic_acorn(board *ptr, int x, int y);

//  Configuration initiale aléaoire
extern void ic_rand(board *ptr);

#endif
