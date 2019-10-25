//  À FAIRE :
//    - Afficher la génération actuelle et le nombre de cellules vivantes dans
//      la barre de titre
//    - Implanter un éditeur de plateau basique permettant de définir
//      manuellement, directement depuis la fenêtre, l'état des cellules
//    - Passage à la génération suivante automatique et à vitesse variable
//    - Définir une structure contenant les informations utiles (n-ième
//      génération, nombre de cellules vivantes, etc)
//    - Optimiser la complexité en mettant à jour et en redessinant uniquement
//      les parties affectées du plateau

//  Le jeu de la vie, selon les règles de John Conway :
//    À chaque étape, l’évolution d’une cellule est entièrement déterminée par
//    l’état de ses huit voisines de la façon suivante :
//
//    - Une cellule morte possédant exactement trois voisines vivantes devient
//        vivante (elle naît).
//    - Une cellule vivante possédant deux ou trois voisines vivantes le reste,
//        sinon elle meurt."
//    (https://en.wikipedia.org/wiki/Conway's_Game_of_Life)

#ifndef GOL__H
#define GOL__H

#define BOARD_SIZE 200
#define CELL_SIZE 5

typedef struct {
  int curr_gen[BOARD_SIZE][BOARD_SIZE];
  int next_gen[BOARD_SIZE][BOARD_SIZE];
  int gen;
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
