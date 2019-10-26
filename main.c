//  À FAIRE :
//    - Implanter un éditeur de plateau basique permettant de définir
//      manuellement, directement depuis la fenêtre, l'état des cellules
//    - Passage à la génération suivante automatique et à vitesse variable
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

#include <stdlib.h>
#include <stdio.h>
#include "sg.h"
#include "gol.h"

#define EINGRAU COLOR(22, 22, 29)
#define IVORY   COLOR(200, 200, 200)

// Codes ASCII
#define Q 113
#define SPACE 32

// Propriétés de la fenêtre
#define WIDTH 1000
#define HEIGHT 1000
#define BGCOLOR EINGRAU
#define FGCOLOR IVORY
#define INST "('space' = next gen, 'q' = quit)"

int main(void) {
  // Initialisation du plateau et des éventuelles configurations initiales
  board b;
  board_init(&b);
  ic_blinker(&b, 10, 10);
  ic_toad(&b, 20, 10);
  ic_beacon(&b, 30, 10);
  ic_pulsar(&b, 45, 10);
  ic_glider(&b, 10, 25);
  ic_lwss(&b, 20, 25);
  ic_mwss(&b, 20, 35);
  ic_hwss(&b, 20, 45);
  b.curr_total = alive_total(&b);
  b.next_total = b.curr_total;
  
  char title[100];
  int key = SPACE;
  sprintf(title, "Life : %uth generation , %u cells alive " INST, b.gen,
      b.curr_total);
  sg_open(WIDTH, HEIGHT, BGCOLOR, FGCOLOR, title);

  // Boucle principale
  while (1) {
    if (key == Q) {
      sg_close();
    }
    
    if (key == SPACE) {
      board_draw(&b);
      sprintf(title, "Life : %uth generation , %u cells alive " INST, b.gen,
          b.curr_total);
      sg_set_title(title);
      board_update(&b);
      board_upgrade(&b);
    }
    
    key = sg_get_key();
  }
  return EXIT_SUCCESS;
}
