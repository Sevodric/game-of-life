#ifndef GOL__H
#define GOL__H

// Couleurs de fond et des cellules
#define EINGRAU COLOR(22, 22, 29)
#define IVORY   COLOR(200, 200, 200)
#define GREEN   COLOR(53, 157, 65)

// Codes des touches ammenées à êtres pressées, tels que renvoyés par la
//    la fonction sg_get_key() de la bibliothèque Simple Graph (voir X11/keysim)
#define KEY_E 101
#define KEY_Q 113
#define KEY_C 99
#define KEY_UP 65362
#define KEY_LEFT 65361
#define KEY_DOWN 65364
#define KEY_RIGHT 65363
#define KEY_SPACE 32
#define KEY_ESC 65307

// État des cellules
#define ALIVE 1
#define DEAD 0

// Macrofonction de la flemme
#define FOR_EACH_CELL(X)                                                       \
  for (int x = 0; x < BOARD_SIZE; ++x) {                                       \
    for (int y = 0; y < BOARD_SIZE; ++y) {                                     \
      X                                                                        \
    }                                                                          \
  }

// Taille du plateau et des cellules
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

//  alive_total : renvoie le nombre de cellules vivantes du plateau pointé par
//    ptr
extern unsigned int alive_total(board *ptr);

//  board_edit : entre dans le mode d'édition du plateau pointé par ptr
extern void board_edit(board *ptr);

#endif
