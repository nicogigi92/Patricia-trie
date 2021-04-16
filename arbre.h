#ifndef _ARBRE_H
#define _ARBRE_

#define MAX_LEN 100


struct noeud
{
    int complet; //complet = 1 : mot complet, complet = 0 mot incomplet
	char suffixe[MAX_LEN];
	struct noeud* noeuds[MAX_LEN];
};

typedef struct noeud* Arbre;	

Arbre ex_arbre;

void cree_racine(Arbre *racine);
void cree_arbre(Arbre *racine,char* suffixe);
void insert_mot_arbre(Arbre *racine, char* suffixe);
int is_leaf(Arbre *racine);
void display_arbre(Arbre *racine, char* str);
void display_all_suffixe(Arbre *racine);
void rempli_arbre(Arbre *racine,char* nom_fichier);
int recherche(Arbre *racine,char* mot);
#endif