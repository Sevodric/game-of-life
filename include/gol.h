#ifndef GOL__H
#define GOL__H

// Key codes as returned by sg_get_key() (see X11/keysim)
#define KEY_SPACE       32
#define KEY_C           99
#define KEY_E           101
#define KEY_Q           113
#define KEY_LEFT        65361
#define KEY_UP          65362
#define KEY_RIGHT       65363
#define KEY_DOWN        65364
#define KEY_BACKSPACE   65288
#define KEY_ESC         65307

// Some colors
#define EINGRAU COLOR(22, 22, 29)
#define IVORY   COLOR(200, 200, 200)
#define GREEN   COLOR(53, 157, 65)

typedef struct board board;

//  board_init: creates a board objects. Returns a pointer to the object created
//    upon success, NULL otherwise.
extern board *board_init(void);

//  board_update: updates the board pointed to by ptr.
extern void board_update(board *ptr);

//  board_upgrade: upgrade the board pointed to by ptr.
extern void board_upgrade(board *ptr);

//  board_draw: draw the board pointed to by ptr.
extern void board_draw(const board *ptr);

//  alive_total: returns the total amount of living cells on the board pointed
//    to by ptr.
extern size_t alive_total(const board *ptr);

//  board_edit: enters the editing mode for the board pointed to by ptr.
extern void board_edit(board *ptr);

//  board_dispose: free the alocated memory to *pp and give *pp the NULL value.
extern void board_dispose(board **pp);

void board_displaycheckup(const board *ptr);

// === SOME INITIAL CONFIGURATIONS ============================================

// Oscillators
extern void ic_blinker(board *ptr, int x, int y);
extern void ic_toad(board *ptr, int x, int y);
extern void ic_beacon(board *ptr, int x, int y);
extern void ic_pulsar(board *ptr, int x, int y);

// Spaceships
extern void ic_glider(board *ptr, int x, int y);
extern void ic_lwss(board *ptr, int x, int y);
extern void ic_mwss(board *ptr, int x, int y);
extern void ic_hwss(board *ptr, int x, int y);

// Methuselahs
extern void ic_rpentomino(board *ptr, int x, int y);
extern void ic_diehard(board *ptr, int x, int y);
extern void ic_acorn(board *ptr, int x, int y);

// Random
extern void ic_rand(board *ptr);
#endif
