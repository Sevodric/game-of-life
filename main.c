//  À FAIRE :
//    - PRIORITÉ : perfectionner la fonction board_update pour prendre en compte
//      les bords du plateau
//    - Ajouter des fonctions d'initialisation de configurations de départ
//    - Afficher la génération actuelle et le nombre de cellules vivantes dans
//      la barre de titre
//    - Définir une structure contenant les informations utiles (n-ième
//      génération, nombre de cellules vivantes, etc)
//    - Optimiser la complexité en mettant à jour et en redessinant uniquement
//      les parties affectées du plateau

//  ----------------------------------------------------------------------------

//  Le jeu de la vie, selon les règles de John Conway :
//    "À chaque étape, l’évolution d’une cellule est entièrement déterminée par
//    l’état de ses huit voisines de la façon suivante :
//
//    - Une cellule morte possédant exactement trois voisines vivantes devient
//        vivante (elle naît).
//    - Une cellule vivante possédant deux ou trois voisines vivantes le reste,
//        sinon elle meurt."
//    (https://en.wikipedia.org/wiki/Conway's_Game_of_Life)

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "sg.h"
#include "gol.h"

#define WIDTH 900
#define HEIGHT 900
#define BGCOLOR BLACK
#define FGCOLOR WHITE
#define TITLE "Game of Life"

int main(void) {
  srand((unsigned int) time(NULL));
  sg_open(WIDTH, HEIGHT, BGCOLOR, FGCOLOR, TITLE);
  board b;
  board_init(&b);
  ic_blinker(&b, 2, 2);
  while (sg_get_key() != 'q') {
    board_draw(&b);
    board_update(&b);
    printf("Génération %d\n", b.gen);
  }
  sg_close();
  return EXIT_SUCCESS;
}
