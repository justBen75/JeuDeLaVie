#include <stdio.h>
#include "grille.h"
#include "pile.h"
#include <graphics.h>
#include <stdlib.h>
#include <getopt.h>

const char *program_name;

/* Envoie les informations sur l'utilisation de la commande vers STREAM
(typiquement stdout ou stderr) et quitte le programme avec EXIT_CODE.
Ne retourne jamais. */
void print_usage (FILE * stream, int exit_code)
{
	fprintf (stream, "Utilisation : %s options [fichierentrée ...]\n", program_name);
	fprintf (stream,
	" -h --help               Affiche ce message.\n"
	"-i --input               Pour insérer une grille manuellement.\n"
	"-o --output		Pour sauver la grille vers un fichier.\n"
	"-n --nultiplier		Pour appliquer n fois la fonction applique.\n"
	);
	exit (exit_code);
	}


int main (int argc, char *argv[])
{
	int next_option;
	/* Chaîne listant les lettres valides pour les options courtes. Les deux points signifient que l'option peut prendre des arguments */
	const char *const short_options = "hi:o:n:";
	/* Tableau décrivant les options longues valides. */	
	const struct option long_options[] = {
		{"help", 0, NULL, 'h'},		/*Definition de help qui ne prend pas d'argument "0" et son raccourci sera h */
		{ "input", 1,NULL, 'i' },	/*Definition de input qui prendra un argument "1" et son raccourci sera i */
		{ "output",1, NULL, 'o'},	/*Definition de output qui prendra un argument "1" et son raccourci sera i */
		{ "nultiplier",1, NULL, 'n'},   /*Definition de l'option nultiplier qui prendra un arugment "1" et son raccourci sera n */
		{NULL, 0, NULL, 0}		/* Requis à la fin du tableau.  */};
	int fenetre[2];
	Tampon t; /*Va permettre de stocker la grille et la et la position de la liste pour pouvoir modifier les valeurs de celles-ci*/ 
	List List = NULL;
	Grille* grille = NULL;
	int check_i =0; /*Permet de vérifier si l'option i est là*/
	/*int check_o=0;Permet de vérifier si l'option o est là*/
	program_name = argv[0]; /* Nom du programme (jeu) */
	if(check_i == 0){/*Est ce que l'option i a été saisi ?Si non*/
	grille=lecteur(grille,"default_grille");
}
	do
	{
		next_option = getopt_long (argc, argv, short_options,long_options, NULL);
		/* On regarde si l'utilisateur à entrée des options/paramètres */
		switch (next_option){
			case 'h':
			/* -h or --help */
			/* L'utilisateur a demandé l'aide-mémoire. L'affiche sur la sortie
			standard et quitte avec le code de sortie 0 (fin normale). */
			print_usage (stdout, 0);
			break;
			case 'n' :
			/* -n or --nultiplier */
			/* On appelle n fois la fonction applique_n_fois */
/*if(check_o == 0){fprintf(stderr,"l'option -o n'est psa présente\n");exit(1);}*/ 
		if(check_i == 0) grille=lecteur(grille,"default_grille");
		else{
			check_i = next_option;
			grille=lecteur(grille,argv[2]);
		}		
			applique_n_fois(grille,atoi(optarg));
			List = add_first(List,grille);
			break;
			case 'i':
			 /*-i or --input */
			/* On appelle la fonction lecture sur le fichier passé en argument*/		
		check_i = next_option;
		grille=lecteur(grille,optarg);
			
			break;
			/* Permet de changer la grille à partir d'un fichier txt */
			case 'o':
			/* -o or --output */
			/* On appelle la fonction sauver sur le fichier passé en argument*/
			sauver(grille,optarg);
			break;
			/* Permet de sauver la grille dans un fichier save */
			case '?':		/* L'utilisateur a saisi une option invalide. */
			/* Affiche l'aide-mémoire sur le flux d'erreur et sort avec le code
			de sortie un (indiquant une fin anormale). */
			print_usage (stderr, 1);
			break;
			case -1:		/* Fin des options.  */
			break;
			default:	
			abort ();
			}
		}
	while (next_option != -1);
	/* On demande à l'utisateur la taille de la fênetre qu'il souhaite afficher puis on l'affiche */

	redefine_fenetre (fenetre);
	gr_open_graph (" fenetre[0]xfenetre[1]");
	/* Par défaut tant qu'on appuie pas sur q on supprime tout ce qui est affiché et on affiche la grille en fonction de la fenetre actuelle*/
	do
	{	
		gr_clear_graph ();
		affiche_grille (grille, gr_size_y (),
		calcule_cote (grille,gr_size_x (), gr_size_y ()));
		/* On regarde la touche sur laquelle l'utilisateur va appuier et on effecture des conditions en fonction de ce sur quoi il appuie */
		switch (gr_read_key ())
		{
			/* Si on appuie sur r alors on appelle la fonction affiche_grille*/
			case 'r':
			affiche_grille (List->g, gr_size_y (),
			calcule_cote (List->g,gr_size_x (), gr_size_y ()));
			break;
			/* Si on appuie sur n alors on appelle la fonction applique*/
			case 'n':
			List = add_first(List,grille);
			applique (grille);


			break;
			/* Si on appuie sur s alors on appelle la fonction sauver*/
			case 's':
			sauver(grille,"save");
			break;
			/* Par défaut on réaffiche la grille avec la fenetre courante*/
			case 'b':
			if(List != NULL){
			t = remove_first(List);
			List=t.liste;
			grille= t.grille;
			}
			break;
			default:
			affiche_grille (grille, gr_size_y (),
			calcule_cote (grille,gr_size_x (), gr_size_y ()));
			}
		
		}
	/* Si on appuie sur q alors on quitte le jeu et on sauve la grille dans un fichier save*/
	while (gr_read_key () != 'q');
	sauver(grille,"save");
	libere_grille(grille);
	free_list(List);
	return 0;
	}
