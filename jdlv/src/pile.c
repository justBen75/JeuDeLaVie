#include <stdio.h>
#include "pile.h"
#include <stdlib.h>
#include "grille.h"

/* Fonction qui permet d'ajouter une cellule en bas de pile*/
List add_first(List liste, Grille* g)

{
    Cell* nouvelCell = malloc(sizeof(Cell));
    Grille* newGrille = alloue_grille(g->nombredeligne,g->nombredecolonne);
    copie_grille(g,newGrille);
    nouvelCell->g = newGrille;
    nouvelCell->nxt = NULL;
    if(liste == NULL)
    {
	return nouvelCell;
    }
    else
    {
        Cell* temp=liste;
        while(temp->nxt != NULL)
        {
            temp = temp->nxt;
        }
        temp->nxt = nouvelCell;
	return liste;
    }
}
/*
   Fin de fonction add_first
   */

/* Fonction qui permet de retirer une cellule en bas de pile*/
Tampon remove_first(List liste)
{

    Cell* tmp = liste;
    Cell* ptmp = liste;
    Tampon t;
	t.liste= liste;
	t.grille=liste->g;
    if(liste == NULL)
	{
	t.liste = NULL;
	t.grille=liste->g;
	return t;
	}
    if(liste->nxt == NULL)
    {
	t.liste = NULL;
	t.grille = tmp->g;
        free(t.liste);
	return t;
    }

    while(tmp->nxt != NULL)
    {
        ptmp = tmp;
        tmp = tmp->nxt;
    }
    ptmp->nxt = NULL;
    free(tmp);
    t.liste= liste;
    t.grille=ptmp->g;
    return t;
}
/*
   Fin de fonction remove_first
   */

/* Fonction qui permet de libérer la pile dynamique*/
void free_list(List liste)
{
    if(liste == NULL)
    {
	exit(1);
    }
    else
    {
        free(liste);
    }
}
/*
   Fin de fonction free_list
   */

/* Fonction view qui permet de voir toutes les cellules de la pile passée en paramètre*/
void view(List liste)
{
    Cell *tmp = liste;
    while(tmp != NULL)
    {
        debug(tmp->g);
        tmp = tmp->nxt;
    }
}
/*
   Fin de fonction view
   */


