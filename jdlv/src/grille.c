#define _GNU_SOURCE
#include <stdio.h>
#include <math.h>
#include "grille.h"
#include <graphics.h>
#include <stdlib.h>

/*
   Fonction debug permettant d'afficher d'afficher les grilles
   */
void debug(Grille* variable){
	{
		int i, j;

		for (i = 0; i != variable->nombredeligne; i++)
		{/*Pour chaque ligne*/

			printf ("\n");

			for (j = 0; j != variable->nombredecolonne; j++)
			{/*On affiche la colonne*/
				printf ("%c",variable->grille[i][j]);
			}
		}
	}
}

/*
   Fin de fonction debug
   */

/*
   Fonction applique_n_fois qui permet d'appliquer n fois la fonction applique
   */
void applique_n_fois(Grille* variable,int n){
	int i;
	for(i=0;i<n;i++){
		applique (variable);
	}
}

/*
   Fin de fonction applique_n_fois
   */

/*
   Fonction lecture qui permet de lire un fichier passé en paramètre et de le stocker dans la grille passée elle aussi en paramètre
   */
/*void lecteur_suite(Grille* grille,int nbc,char* file){
  int i=0;
  FILE * fichier;
  fichier = fopen(file,"r+");
  if(fichier == NULL){
  printf("Y a pas de grille \n");
  }
  else{
  while(fgets(grille->grille[i],nbc+1,fichier) != NULL)		i++;
  fclose(fichier);
  }
  }
*/

int count_nb_line(FILE* stream)
{
	int ch=0;
	int nbline=0;
	if (stream == NULL)
		exit(1);
	while(!feof(stream))
	{
		ch = fgetc(stream);
		if(ch == '\n')
		{
			nbline++;
		}

	}
	rewind(stream);	
	return nbline;

}

void copy(char* line_tmp,char *grille){
	int i=0;
	while(*(line_tmp+i)!='\n'){
		grille[i]=line_tmp[i];
		i++;
	}
}


Grille* lecteur(Grille* grilledelecture,char* file){

	int nbl;
	int nbc=0;
	size_t taille_buf=0;
	
	FILE * stream;
	char * line_tmp=NULL;
	int i;

	stream = fopen(file,"r+");
	nbl = count_nb_line(stream);
	nbc = getline(&line_tmp,&taille_buf,stream)  ;
	if(nbc == -1){
		fprintf(stderr,"fichier malformé ?\n");
		exit(1);
	}
	nbc--;
	grilledelecture=alloue_grille(nbl,nbc);
	copy(line_tmp,grilledelecture->grille[0]); /* fonction a ecrire, qui enleve le \n et le \0 */
	for (i=1;i<nbl;i++)
	{
			int taille ;
			taille = getline(&line_tmp,&taille_buf,stream);
			if(nbc!=taille-1){
				/* il y a un probleme, il faut quitter le programme */
				printf("Il y a eu un pb\n");
				exit(1);
			}
			copy(line_tmp,grilledelecture->grille[i]); /* fonction a ecrire, qui enleve le \n et le \0 */
	}

	free(line_tmp);
	fclose(stream);
	return grilledelecture;
}

/*
   Fin de fonction lecture
   */

/*
   Fonction sauver qui permet de sauver la grille passée en paramètre dans un fichier file lui aussi un fichier passé en paramètre et de le stocker dans la grille passée elle aussi en paramètre
   */

void sauver(Grille* g,char* file){
	int i=0;
	FILE * fichier;
	fichier = fopen(file,"w+");
	if(fichier == NULL){
		printf("Le fichier n'existe pas\n");
	}
	else{
		for(;i<g->nombredeligne;i++){
			fputs(g->grille[i],fichier);
			fputs("\n",fichier);
		}
		fclose(fichier);
	}
}

/*
   Fin de fonction sauver
   */


/*
   Fonction calcul_cote permet de calculer la largeur et la longueur d'un côté pour que celui ci rentre dans une fenêtre
   */

int calcule_cote (Grille* variable,int w, int h)
{
	int c = 0;
	while (w > (variable->nombredecolonne)*c && h > (variable->nombredeligne) * c)
		c += 1;
	return c;
}

/*
   Fin fonction calcul_cote
   */

/*
   Fonction redefine_fenetre Permet à l'utilisateur d'entrée les valeurs de la fenêtre qu'il souhaite
   */
void redefine_fenetre (int *fenetre)
{
	int LARGEUR;
	int HAUTEUR;
	printf ("Veuillez entrer la largeur : ");
	scanf ("%d", &LARGEUR);
	printf ("Veuillez entrer la hauteur : ");
	scanf ("%d", &HAUTEUR);
	*fenetre = LARGEUR;
	*(fenetre + 1) = HAUTEUR;
}
/*
   Fin de fonction redefine_fenetre
   */

/*
   Fonction affiche_grille permet d'afficher en fonction de la lecture de la grille la couleur correspondant dans la fenêtre si "n" alors noir ...
   */
void affiche_grille (Grille* variable, int h, int c)
{	

	int i, j, k, l;
	char a;

	for (j = h - c, l = 0; l != (variable->nombredeligne); j -= c, l++)
	{
		for (i = 0, k = 0; k != (variable->nombredecolonne); i += c, k++)
		{
			a = variable->grille[l][k];
			if (a == 'n')
			{
				gr_set_color (NOIR);
				gr_fill_rect (i, j, c, c);
			}
			else
			{


				gr_set_color (BLANC);
				gr_fill_rect (i, j, c, c);


			}

		}

	}

}
/*
   Fin de fonction affiche_grille
   */

/*
   Fonction copie_grille permet de copier une grille de la grille1 vers la grille2
   */
void copie_grille (Grille* variable, Grille* variable1)
{
	int l, c;
	for (l = 0; l != (variable->nombredeligne); l++)
	{
		for (c = 0; c != (variable->nombredecolonne); c++)
		{
			variable1->grille[l][c] = variable->grille[l][c];
		}
	}
}

/*
   Fin de fonction copie_grille
   */

/*
   Fonction compte_voisin permet de compter le nombre de case noir autour de la case étudiée en paramètre
   */
int compte_voisin (Grille* variable, int i, int j)
{
	int compteurnoir = 0;

	if( i == 0 && j ==0){
		if (variable->grille[i - 0][j + 1] == 'n')
			compteurnoir += 1;
		if (variable->grille[i + 1][j + 1] == 'n')
			compteurnoir += 1;
		if (variable->grille[i + 1][j - 0] == 'n')
			compteurnoir += 1;
		return compteurnoir;
	}


	else if(i==variable->nombredeligne-1 && j==0 ){
		if (variable->grille[i - 0][j + 1] == 'n')
			compteurnoir += 1;
		if (variable->grille[i - 1][j + 1] == 'n')
			compteurnoir += 1;
		if (variable->grille[i - 1][j + 0] == 'n')
			compteurnoir += 1;
		return compteurnoir;	
	}

	else if(i==0 && j== variable->nombredecolonne-1){
		if (variable->grille[i - 0][j - 1 ] == 'n')
			compteurnoir += 1;
		if (variable->grille[i + 1][j - 1] == 'n')
			compteurnoir += 1;
		if (variable->grille[i + 1][j + 0] == 'n')
			compteurnoir += 1;
		return compteurnoir;	
	}

	else if(i==variable->nombredeligne-1 && j== variable->nombredecolonne-1){
		if (variable->grille[i - 0][j - 1] == 'n')
			compteurnoir += 1;
		if (variable->grille[i - 1][j - 1] == 'n')
			compteurnoir += 1;
		if (variable->grille[i - 1][j - 0] == 'n')
			compteurnoir += 1;
		return compteurnoir;	
	}

	else if(i == 0){
		if (variable->grille[i - 0][j - 1] == 'n')
			compteurnoir += 1;
		if (variable->grille[i - 0][j + 1] == 'n')
			compteurnoir += 1;	
		if (variable->grille[i + 1][j - 1] == 'n')
			compteurnoir += 1;
		if (variable->grille[i + 1][j - 0] == 'n')
			compteurnoir += 1;
		if (variable->grille[i + 1][j + 1] == 'n')
			compteurnoir += 1;
		return compteurnoir;

	}

	else if(j==0){
		if (variable->grille[i - 1][j - 0] == 'n')
			compteurnoir += 1;
		if (variable->grille[i - 1][j + 1] == 'n')
			compteurnoir += 1;
		if (variable->grille[i + 0][j + 1] == 'n')
			compteurnoir += 1;
		if (variable->grille[i + 1][j + 1] == 'n')
			compteurnoir += 1;
		if (variable->grille[i + 1][j + 0] == 'n')
			compteurnoir += 1;
		return compteurnoir;	
	}

	else if(i==variable->nombredeligne-1){
		if (variable->grille[i + 0][j - 1] == 'n')
			compteurnoir += 1;
		if (variable->grille[i - 1][j - 1] == 'n')
			compteurnoir += 1;
		if (variable->grille[i - 1][j + 0] == 'n')
			compteurnoir += 1;
		if (variable->grille[i - 1][j + 1] == 'n')
			compteurnoir += 1;
		if (variable->grille[i + 0][j + 1] == 'n')
			compteurnoir += 1;
		return compteurnoir;	
	}

	else if(j== variable->nombredecolonne-1){
		if (variable->grille[i - 1][j - 0] == 'n')
			compteurnoir += 1;
		if (variable->grille[i - 1][j - 1] == 'n')
			compteurnoir += 1;
		if (variable->grille[i - 0][j - 1] == 'n')
			compteurnoir += 1;
		if (variable->grille[i + 1][j - 1] == 'n')
			compteurnoir += 1;
		if (variable->grille[i + 1][j + 0] == 'n')
			compteurnoir += 1;
		return compteurnoir;			
	}
	else{
		if (variable->grille[i - 1][j - 1] == 'n')
			compteurnoir += 1;
		if (variable->grille[i - 1][j - 0] == 'n')
			compteurnoir += 1;
		if (variable->grille[i - 1][j + 1] == 'n')
			compteurnoir += 1;
		if (variable->grille[i - 0][j - 1] == 'n')
			compteurnoir += 1;
		if (variable->grille[i - 0][j + 1] == 'n')
			compteurnoir += 1;
		if (variable->grille[i + 1][j - 1] == 'n')
			compteurnoir += 1;
		if (variable->grille[i + 1][j - 0] == 'n')
			compteurnoir += 1;
		if (variable->grille[i + 1][j + 1] == 'n')
			compteurnoir += 1;
		return compteurnoir;
	}
}

/*
   Fin de fonction compte_voisin
   */

/*
   Fonction applique permet de modifier la grille en fonction des instructions données dans le TP3
   */ 
void applique (Grille* variable)
{
	int l, c, casenoir;
	Grille* copie;
	copie = alloue_grille(variable->nombredeligne,variable->nombredecolonne);	
	copie_grille(variable, copie);
	for (l = 0; l != variable->nombredeligne; l++)
	{
		for (c = 0; c 	!= variable->nombredecolonne; c++)
		{
			casenoir = compte_voisin (copie, l, c);
			switch (casenoir)
			{
				case 3:
					variable->grille[l][c] = 'n';
					break;
				case 2:
					break;
				default:
					variable->grille[l][c]= ' ';
					break;
			}
		}
	}
}

/*
   Fin de fonction applique
   */

/*
   Fonction alloue_grille qui permet d'allouer une structure de type grille dans le tas en prenant en paramètre son nombre de ligne (n) et son nombre de colonne(m)
   */ 
Grille* alloue_grille(int n, int m)
{
	int i;
	Grille* variable;

	variable = (Grille*)malloc(sizeof(Grille));
	if(variable==NULL){fprintf(stderr,"pb d'allocation 1 dans alloue grille\n");exit(1);}

	variable->grille=(char**)malloc(sizeof(char*)*n);
	if(variable->grille==NULL){fprintf(stderr,"pb d'allocation 2 dans alloue grille\n");exit(1);}

	for (i=0;i<n;i++){ 
		variable-> grille[i]=(char*)malloc(m*sizeof(char));
		if(variable->grille[i]==NULL){fprintf(stderr,"pb d'allocation 3 dans alloue grille\n");exit(1);}
	}
	variable->nombredeligne = n;
	variable->nombredecolonne = m;
	return variable;
}

void libere_grille(Grille* variable){
	int i;
	for(i=0;i!=(variable->nombredeligne);i++){
		free(variable -> grille[i]);
	}
	free(variable);
}

/*
   Fin de fonction alloue_grille
   */

