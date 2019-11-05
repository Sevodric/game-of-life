#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "sg.h"
#include "gol.h"

//  --- IMPLÉMENTATION DE LSNAP ------------------------------------------------

#define FUN_SUCCESS 0
#define FUN_FAILURE -1

lsnap *lsnap_empty(void) {
  lsnap *ptr = malloc(sizeof(lsnap));
  if (ptr != NULL) {
    ptr->head = NULL;
  }
  return ptr;
}

bool lsnap_is_empty(const lsnap *s) {
  return s->head == NULL;
}

int lsnap_get_head(const lsnap *s, board *ptr) {
  if (lsnap_is_empty(s)) {
    return FUN_FAILURE;
  }
  *ptr = s->head->value;
  return FUN_SUCCESS;
}

int lsnap_insert_head(lsnap *s, board *ptr) {
  snap *c = malloc(sizeof(snap));
  if (c == NULL) {
    return FUN_FAILURE;
  }
  c->value = *ptr;
  c->next = s->head;
  s->head = c;
  return FUN_SUCCESS;
}

int lsnap_remove_head(lsnap *s) {
  if (lsnap_is_empty(s)) {
    return FUN_FAILURE;
  }
  snap *t = s->head;
  s->head = s->head->next;
  free(t);
  return FUN_SUCCESS;
}

void lsnap_dispose(lsnap **sptr) {
  if (*sptr == NULL) {
    return;
  }
  snap *p = (*sptr)->head;
  while (p != NULL) {
    snap *t = p;
    p = p->next;
    free(t);
  }
  free(p);
  free(*sptr);
  *sptr = NULL;
}

//  --- IMPLÉMENTATION DE BOARD ------------------------------------------------

//  alive_neighbors : renvoie le nombre de cellules voisines vivantes de la
//    cellule de coordonnées x, y du plateau pointé par ptr
static int alive_neighbors(board *ptr, int x, int y) {
  int n = 0;
  //  Si la cellule à évaluer est située sur le bord gauche, prend en compte les
  //    cellules situées sur le bord droit du plateau en lieu en place des
  //    inexistantes cellules de gauche. Si la cellule à évaluer est située sur
  //    le bord droit, applique réciproquement le même comportement. Sinon, 
  //    évalue les 8 cellules voisines de manière standard
  if (x == 0) {
    n += ptr->curr_gen[BOARD_SIZE - 1][y - 1];
    n += ptr->curr_gen[BOARD_SIZE - 1][y];
    n += ptr->curr_gen[BOARD_SIZE - 1][y + 1];
    n += ptr->curr_gen[x][y - 1];
    n += ptr->curr_gen[x + 1][y - 1];
    n += ptr->curr_gen[x + 1][y];
    n += ptr->curr_gen[x + 1][y + 1];
    n += ptr->curr_gen[x][y + 1];
  } else if (x == BOARD_SIZE - 1) {
    n += ptr->curr_gen[x][y - 1];
    n += ptr->curr_gen[x - 1][y - 1];
    n += ptr->curr_gen[x - 1][y];
    n += ptr->curr_gen[x - 1][y + 1];
    n += ptr->curr_gen[x][y + 1];
    n += ptr->curr_gen[0][y + 1];
    n += ptr->curr_gen[0][y];
    n += ptr->curr_gen[0][y - 1];
  } else {
    for (int i = x - 1; i <= x + 1; ++i) {
      for (int j = y - 1; j <= y + 1; ++j) {
        n += ptr->curr_gen[i][j];
      }
    }
    n -= ptr->curr_gen[x][y];
  }
  return n;
}

void board_init(board *ptr) {
  FOR_EACH_CELL(
    ptr->curr_gen[x][y] = DEAD;
    ptr->next_gen[x][y] = DEAD;
  )
  ptr->gen = 0;
  ptr->curr_total = 0;
  ptr->next_total = 0;
}

void board_update(board *ptr) {
  FOR_EACH_CELL(
    if (ptr->curr_gen[x][y] == ALIVE) {
      if (alive_neighbors(ptr, x, y) == 2 || alive_neighbors(ptr, x, y) == 3) {
        ptr->next_gen[x][y] = ALIVE;
      } else {
        ptr->next_gen[x][y] = DEAD;
        ptr->next_total -= 1;
      }
    } else if (ptr->curr_gen[x][y] == DEAD) {
      if (alive_neighbors(ptr, x, y) == 3) {
        ptr->next_gen[x][y] = ALIVE;
        ptr->next_total += 1;
      } else {
        ptr->next_gen[x][y] = DEAD;
      }
    } else {
      ptr->next_gen[x][y] = ptr->curr_gen[x][y];
    }
  )
}

void board_upgrade(board *ptr) {
  FOR_EACH_CELL(
    ptr->curr_gen[x][y] = ptr->next_gen[x][y];
  )
  ptr->gen += 1;
  ptr->curr_total = ptr->next_total;
}

void board_draw(board *ptr) {
  sg_clear();
  FOR_EACH_CELL(
    if (ptr->curr_gen[x][y] == ALIVE) {
      sg_fill_rectangle(x * CELL_SIZE + 1, y * CELL_SIZE + 1, CELL_SIZE - 1,
          CELL_SIZE - 1);
    }
  )
}

unsigned int alive_total(board *ptr) {
  unsigned int n = 0;
  FOR_EACH_CELL(
    n += (unsigned int) ptr->curr_gen[x][y];
  )
  return n;
}

#define USAGE "('space' = on/off, 'c' = clear, arrows = move "                 \
    "'escape' = confirm)"

void board_edit(board *ptr) {
  // Initialise la touche pressée et définie les coodronnées du curseur au 
  //    milieu du plateau
  int key = 0;
  int x = BOARD_SIZE / 2;
  int y = BOARD_SIZE / 2;
  
  // Modifie le titre de la fenêtre
  sg_set_title("Live editing " USAGE);
  
  // Boucle de l'éditeur
  while (1) {
    // Dessine le curseur
    sg_set_fgcolor(RED);
    sg_draw_rectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE);
    
    // Actualise la touche pressée 
    key = sg_get_key();
    
    // Si la touche SPACE est pressée, modifie la valeur de la cellule de
    //    coordonnées x et y du plateau ptr à DEAD ou ALIVE, si la valeur de
    //    cette dernière est respectivment ALIVE ou DEAD. Dessine ensuite la
    //    cellule avec la couleur appropriée
    if (key == KEY_SPACE) {
      if (ptr->curr_gen[x][y] == ALIVE) {
        ptr->curr_gen[x][y] = DEAD;
        ptr->curr_total -= 1;
        ptr->next_total -= 1;
        sg_set_fgcolor(EINGRAU);
        sg_fill_rectangle(x * CELL_SIZE + 1, y * CELL_SIZE + 1, CELL_SIZE,
            CELL_SIZE);
        sg_set_fgcolor(IVORY);
      } else if (ptr->curr_gen[x][y] == DEAD) {
        ptr->curr_gen[x][y] = ALIVE;
        ptr->curr_total += 1;
        ptr->next_total += 1;
        sg_set_fgcolor(GREEN);
        sg_fill_rectangle(x * CELL_SIZE + 1, y * CELL_SIZE + 1, CELL_SIZE,
            CELL_SIZE);
      }
    }
    
    if (key == KEY_C) {
      sg_set_fgcolor(EINGRAU);
      FOR_EACH_CELL(
        ptr->curr_gen[x][y] = DEAD;
        sg_fill_rectangle(x * CELL_SIZE + 1, y * CELL_SIZE + 1, CELL_SIZE,
          CELL_SIZE);
      )
      ptr->curr_total = 0;
      ptr->next_total = 0;
    }
    
    // Efface le curseur précédent
    sg_set_fgcolor(EINGRAU);
    sg_draw_rectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE);
    
    // Si une des touches directionnelles est pressée, modifie la coordonnée
    //    correspondante. Dans le cas où le curseur devait sortir du plateau, il
    //    est téléporté de l'autre côté de ce dernier.
    if (key == KEY_RIGHT) {
      if (x == BOARD_SIZE - 1) {
        x = 0;
      } else {
        ++x;
      }
    }
    if (key == KEY_LEFT) {
      if (x == 0) {
        x = BOARD_SIZE - 1;
      } else {
        --x;
      }
    }
    if (key == KEY_DOWN) {
      if (y == BOARD_SIZE - 1) {
        y = 0;
      } else {
        ++y;
      }
    }
    if (key == KEY_UP) {
      if (y == 0) {
        y = BOARD_SIZE - 1;
      } else {
        --y;
      }
    }
    
    // Si la touche ESCAPE est pressée, réinitialise la couleur de dessin et
    //    sort du mode d'édition
    if (key == KEY_ESC) {
      sg_set_fgcolor(IVORY);
      return;
    }
  }
}

void board_back(board *ptr, lsnap *lptr) {
  lsnap_get_head(lptr, ptr);
  lsnap_remove_head(lptr);
}
