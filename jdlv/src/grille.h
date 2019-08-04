#ifndef AFFICHE_GRILLE_H_
#define AFFICHE_GRILLE_H_

#define NOIR 0xffd700 
#define BLANC 0xFFFFFF


typedef struct 
{
	char** grille;
	int nombredeligne;
	int nombredecolonne;	
}Grille;


Grille* alloue_grille(int, int);
void libere_grille( Grille*);
void debug( Grille*);
void sauver( Grille* g,char* file);
void redefine_fenetre(int* fenetre);

Grille* lecteur( Grille*,char* file);
void affiche_grille( Grille*, int h, int c);
void copie_grille( Grille*, Grille*);
int compte_voisin( Grille*,int i, int j);
void applique( Grille*);
void applique_n_fois( Grille*,int n);
int calcule_cote ( Grille* variable,int w, int h);
#endif
