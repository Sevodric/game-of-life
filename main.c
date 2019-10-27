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

// Propriétés de la fenêtre
#define WIDTH 1000
#define HEIGHT 1000
#define BGCOLOR EINGRAU
#define FGCOLOR IVORY

// Instructions
#define USAGE "('space' = next gen, 'e' = editor, 'q' = quit)"

int main(void) {
  
  // Initialise le plateau et les éventuelles configurations initiales
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
  
  // Compte le nombre de cellules vivantes initiales
  b.curr_total = alive_total(&b);
  b.next_total = b.curr_total;
  
  // Initialise la touche pressée à SPACE pour éxécuter une première boucle
  int key = KEY_SPACE;
  
  // Initialise le titre de la fenêtre, ouvre cette dernière et dessine le
  //    plateau initial
  char title[100];  
  sprintf(title, "Life : %uth generation , %u cells alive " USAGE, b.gen,
      b.curr_total);
  sg_open(WIDTH, HEIGHT, BGCOLOR, FGCOLOR, title);
  board_draw(&b);
  
  // Boucle principale
  while (1) {
    if (key == KEY_Q) {
      break;
    }
    
    // Si la touche KEY_E est pressée, entre dans le mode d'édition
    if (key == KEY_E) {
      board_edit(&b);
      sprintf(title, "Life : %uth generation , %u cells alive " USAGE, b.gen,
          b.curr_total);
      sg_set_title(title);
      key = 0;
    }
    
    // Actualise le plateau si la touche SPACE est pressée
    if (key == KEY_SPACE) {
      board_update(&b);
      board_upgrade(&b);
      board_draw(&b);
      sprintf(title, "Life : %uth generation , %u cells alive " USAGE, b.gen,
          b.curr_total);
      sg_set_title(title);
    }
    
    // Actualise la touche pressée
    key = sg_get_key();
  }
  
  sg_close();
  return EXIT_SUCCESS;
}
