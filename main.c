#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "general.h"
#include "arbre.h"


int main(int argc, char *argv[]){
	int i = 0 ;
	struct noeud* arbre;
	FILE* fichier = NULL;
    char ligne[MAX_LEN] ;
	int c=0;

    cree_racine(&arbre);
	rempli_arbre(&arbre,argv[1]);


    fichier = fopen(argv[2], "r");
    while  (fgets(ligne, MAX_LEN,fichier) != NULL) { /*fin de fichier non atteinte*/
		i++;
		ligne[strcspn(ligne,"\n")]=0;
		if (recherche(&arbre,ligne)==1){
			printf("%s\n",ligne);
			c++;
		}
	}
	printf("%i\n",c);

	
	/*
	//Affichage de l'arbre
	char str[MAX_LEN];
	display_arbre(&arbre,str);
	*/

	/*
	//Affichage de tout les suffixe
	printf("Tout les suffixe : \n");
	display_all_suffixe(&arbre);
	*/
	
	
	//display_all_suffixe(&arbre);
	/*
	char mot[]="edge";
	printf("%s est dans l'abre : %i.\n",mot,recherche(&arbre,mot));
	*/
	
}