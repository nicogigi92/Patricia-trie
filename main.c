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
	rempli_arbre(&arbre,"f1.txt");
	
	//Affichage de l'arbre
	//char str[MAX_LEN];
	//printf("Contenu de l'arbre : \n");
	//display_arbre(&arbre,str);
	
	
	//display_all_suffixe(&arbre);
	char mot[]="edge";
	printf("Est dans l'abre : %i.\n",recherche(&arbre,mot));
	
}