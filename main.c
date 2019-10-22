//  À FAIRE :
//    - Faire en sorte de rendre le plateau infini en "enroulant" les bords
//    - Ajouter des fonctions d'initialisation de configurations de départ
//    - Afficher la génération actuelle et le nombre de cellules vivantes dans
//      la barre de titre
//    - Définir une structure contenant les informations utiles (n-ième
//      génération, nombre de cellules vivantes, etc)
//    - Optimiser la complexité en mettant à jour et en redessinant uniquement
//      les parties affectées du plateau

//  ----------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "sg.h"
#include "gol.h"

#define EINGRAU COLOR(22, 22, 29)
#define IVORY   COLOR(191, 191, 191)

#define WIDTH 900
#define HEIGHT 900
#define BGCOLOR EINGRAU
#define FGCOLOR IVORY
#define TITLE "Game of Life"

int main(void) {
  srand((unsigned int) time(NULL));
  sg_open(WIDTH, HEIGHT, BGCOLOR, FGCOLOR, TITLE);
  board b;
  board_init(&b);
  ic_blinker(&b, 10, 10);
  ic_toad(&b, 20, 10);
  ic_beacon(&b, 30, 10);
  ic_pulsar(&b, 45, 10);
  
  board_draw(&b);
  printf("Génération %d\n", b.gen);
  while (sg_get_key() != 'q') {
    board_update(&b);
    board_upgrade(&b);
    board_draw(&b);
    printf("Génération %d\n", b.gen);
  }
  sg_close();
  return EXIT_SUCCESS;
}
