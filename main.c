#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "general.h"
#include "arbre.h"


int main(){
	struct noeud* arbre;

	/*
	pour mémo 
	complement("test","tes")="t"
	complement("tes","test")=""
	*/

	
    cree_racine(&arbre);
	rempli_arbre(&arbre,"f2.txt");
	
	
	//Affichage de l'arbre
	char str[MAX_LEN];
	printf("Contenu de l'arbre : \n");
	display_arbre(&arbre,str);
	
	/*
	//Affichage de tout les suffixe
	printf("Tout les suffixe : \n");
	display_all_suffixe(&arbre);
	*/
	
	
	//display_all_suffixe(&arbre);
	char mot[]="addressing";
	printf("Est dans l'abre : %i.\n",recherche(&arbre,mot));
	
}