#include "grille.h"
#ifndef PILE_H
#define PILE_H
typedef struct _cell
{
    Grille * g;
    struct _cell *nxt;
}Cell;
 
/* Structure qui permet de renvoyer à la fois la liste courante et la grille courante pour plus tard la modifier dans la grille de jeu.c*/
typedef struct _result
{
	Cell* liste;
	Grille* grille;
}Tampon;

typedef Cell* List;

List add_first(List liste, Grille*);
void free_list(List liste);
Tampon remove_first(List liste);
void view(List liste);

#endif
