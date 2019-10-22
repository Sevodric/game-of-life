//  Le jeu de la vie, selon les règles de John Conway :
//    "À chaque étape, l’évolution d’une cellule est entièrement déterminée par
//    l’état de ses huit voisines de la façon suivante :
//
//    - Une cellule morte possédant exactement trois voisines vivantes devient
//        vivante (elle naît).
//    - Une cellule vivante possédant deux ou trois voisines vivantes le reste,
//        sinon elle meurt."
//    (https://en.wikipedia.org/wiki/Conway's_Game_of_Life)

#ifndef GOL__H
#define GOL__H

#define BOARD_SIZE 9
#define CELL_SIZE 100

typedef struct {
  int curr_gen[BOARD_SIZE][BOARD_SIZE];
  int next_gen[BOARD_SIZE][BOARD_SIZE];
  int gen;
} board;

//  board_init : initialise le plateau pointé par ptr avec des celulles mortes
void board_init(board *ptr);

//  board_update : prépare la mise à jour du plateau pointé par ptr selon les
//    règles précisées précedemment
void board_update(board *ptr);

//  board_upgrade : applique la mise à jour effectuée par board_update sur le
//    plateau pointé par ptr
void board_upgrade(board *ptr);

//  board_draw : dessine le plateau pointé par ptr
void board_draw(board *ptr);

//  alive_neighbors : renvoie le nombre de cellules voisines vivantes de la
//    cellule de coordonnées x, y du plateau pointé par ptr
int alive_neighbors(board *ptr, int x, int y);

//  ----------------------------------------------------------------------------

//  Quelques configurations initiales du jeu de la vie :
//  (https://en.wikipedia.org/wiki/Conway's_Game_of_Life#Examples_of_patterns)

//  Les fonctions ci-après définies crééent des configurations initiales
//    remarquables, dont un aperçu est donné au bout du lien ci-dessus.
//    Les figures sont centrées, si possible, autour de la cellule de
//    coordonnées x, y

void ic_blinker(board *ptr, int x, int y);

void ic_toad(board *ptr, int x, int y);

void ic_beacon(board *ptr, int x, int y);

void ic_pulsar(board *ptr, int x, int y);

void ic_glider(board *ptr, int x, int y);

void ic_lwss(board *ptr, int x, int y);

void ic_mwss(board *ptr, int x, int y);

void ic_hwss(board *ptr, int x, int y);

#endif
