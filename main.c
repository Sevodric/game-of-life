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

// Couleurs de fond et des cellules
#define EINGRAU COLOR(22, 22, 29)
#define IVORY   COLOR(200, 200, 200)

// Codes ASCII des touches ammenées à êtres pressées
#define Q 113
#define SPACE 32

// Propriétés de la fenêtre
#define WIDTH 1000
#define HEIGHT 1000
#define BGCOLOR EINGRAU
#define FGCOLOR IVORY

// Instructions
#define USAGE "('space' = next gen, 'q' = quit)"

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
  int key = SPACE;
  
  // Initialise le titre de la fenêtre et ouvre cette dernière
  char title[100];  
  sprintf(title, "Life : %uth generation , %u cells alive " USAGE, b.gen,
      b.curr_total);
  sg_open(WIDTH, HEIGHT, BGCOLOR, FGCOLOR, title);

  // Boucle principale
  while (1) {
    if (key == Q) {
      break;
    }
    
    // Passe à la génération suivante si la touche ESPACE est pressée
    if (key == SPACE) {
      board_draw(&b);
      sprintf(title, "Life : %uth generation , %u cells alive " USAGE, b.gen,
          b.curr_total);
      sg_set_title(title);
      board_update(&b);
      board_upgrade(&b);
    }
    
    key = sg_get_key();
  }
  
  // Ferme la fenêtre et le programme
  sg_close();
  return EXIT_SUCCESS;
}
