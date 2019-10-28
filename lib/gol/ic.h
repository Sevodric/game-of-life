//  Quelques configurations initiales du jeu de la vie :
//  (https://en.wikipedia.org/wiki/Conway's_Game_of_Life#Examples_of_patterns)
//  Les fonctions suivantes crééent des configurations initiales remarquables,
//    dont un aperçu est donné au bout du lien ci-dessus. Les figures sont
//    centrées, si possible, autour de la cellule de coordonnées x, y

#ifndef IC__H
#define IC__H

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
