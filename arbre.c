#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arbre.h"
#include "general.h"

void cree_racine(Arbre *racine){
    int i;
	*racine = (Arbre)malloc(sizeof(struct noeud));
    for (i = 0 ; i < MAX_LEN ; i++){         
        (*racine)->noeuds[i] = NULL;
    }
	(*racine)->complet=FALSE;
	(*racine)->suffixe[0]='\0';

}

void cree_arbre(Arbre *racine,char* mot){
	int i;
	*racine = (Arbre)malloc(sizeof(struct noeud)); 
	(*racine)->complet=FALSE;
	
	 for (i = 0 ; i < MAX_LEN ; i++){         
        (*racine)->noeuds[i] = NULL;
    }
    strcpy((*racine)->suffixe,mot);
}

void insert_mot_arbre(Arbre *racine, char* suffixe){
	int i = 0;
	int j = 0;
	int c = 0;
	char* old_suffixe;

	for(i=0;i<MAX_LEN;i++){
		if ((*racine)->noeuds[i]!=NULL){
			//si le noeud est compatible on y insert la feuille
			//plusiers cas en fonction du suffixe à insérer
			if (strlen(plus_long_prefixe((*racine)->noeuds[i]->suffixe , suffixe )) != 0){
				
				c++;

				old_suffixe = (char*)malloc(MAX_LEN*sizeof(char));
				strcpy(old_suffixe,(*racine)->noeuds[i]->suffixe);

				//cas d'égalité
				if (strcmp(suffixe,old_suffixe)==0){
					(*racine)->noeuds[i]->complet=TRUE;
					free(old_suffixe);
					break;
				}

				//cas suffixe inclu dans old_suffixe
				if(strlen(complement(suffixe,old_suffixe))==0){
					int k=0;
					while((*racine)->noeuds[k]!=NULL){
						k++; //compteur pour trouver un noeud nul pour créer la nouvelle arborescence
					}	
					cree_arbre(&(*racine)->noeuds[k],suffixe);

					(*racine)->noeuds[k]->noeuds[0]=(*racine)->noeuds[i];
					(*racine)->noeuds[k]->complet = TRUE;
					strcpy((*racine)->noeuds[k]->noeuds[0]->suffixe,complement(old_suffixe,suffixe)) ;
					(*racine)->noeuds[i]=NULL;
					free(old_suffixe);
					break;
				}

				//cas old_suffixe inclu dans suffixe
				if(strlen(complement(old_suffixe,suffixe))==0){
						insert_mot_arbre(&(*racine)->noeuds[i], complement(suffixe,old_suffixe));
						//(*racine)->noeuds[i]->complet=TRUE;
						free(old_suffixe);
						break;
				}
				
				//cas ou les deux complements sont non nulles
				if((strlen(complement(old_suffixe,suffixe))>0)&&(strlen(complement(suffixe,old_suffixe))>0)){
					int k=0;
					while((*racine)->noeuds[k]!=NULL){
						k++;
					}	
					cree_arbre( &(*racine)->noeuds[k] , plus_long_prefixe( (*racine)->noeuds[i]->suffixe , suffixe ));
					(*racine)->noeuds[k]->complet=FALSE;
					(*racine)->noeuds[k]->noeuds[0]=(*racine)->noeuds[i];
					strcpy((*racine)->noeuds[k]->noeuds[0]->suffixe,complement(old_suffixe,suffixe)) ;

					(*racine)->noeuds[i]=NULL;

					cree_arbre(&(*racine)->noeuds[k]->noeuds[1],complement(suffixe,old_suffixe));
					(*racine)->noeuds[k]->noeuds[1]->complet=TRUE;
					free(old_suffixe);
					break;
				}
				
			}
			//Si le noeud est incompatible et non nul on ne fait rien
		}
		//Si le noeud est nul, on enregistre sa position
		else{
					j=i; //j correspond alors à une place libre dans le cas ou aucun noeud compatible est trouvé
			}
	}
	//si on a pas trouvé de noeud compatible, on place le suffixe dans un noeud libre
	if(c==0){
		cree_arbre(&(*racine)->noeuds[j],suffixe);
		(*racine)->noeuds[j]->complet=TRUE;
		}
}

int is_leaf(Arbre *racine){
	int i;
	int c=0;
	for(i=0;i<MAX_LEN;i++){
		if ((*racine)->noeuds[i]!=NULL){
				c++;
		}
	}
	if(c==0)
		return TRUE;
	else 
		return FALSE;
}

void display_arbre(Arbre *racine, char* str){
	char* new_str;
	int i;

	if ((*racine)->complet==TRUE)
			printf("%s\n",str);
	

	for(i=0;i<MAX_LEN;i++){
		if ((*racine)->noeuds[i]!=NULL){
			new_str = (char*)malloc(MAX_LEN*sizeof(char));
			strcpy(new_str,str);
			strcat(new_str,(*racine)->noeuds[i]->suffixe);
			display_arbre(&(*racine)->noeuds[i],new_str);
		}
	}
}


void display_all_suffixe(Arbre *racine){
	int i=0;
	for(i=0;i<MAX_LEN;i++){
		if ((*racine)->noeuds[i]!=NULL){
			 display_all_suffixe(&(*racine)->noeuds[i]);
			 printf("suffixe : %s   noeud : %i   complet : %i\n",(*racine)->noeuds[i]->suffixe,i,(*racine)->noeuds[i]->complet);
		}
	}
}

void rempli_arbre(Arbre *racine,char* nom_fichier){
	FILE* fichier = NULL;
    fichier = fopen(nom_fichier, "r");
	int i = 0 ;
    char ligne[MAX_LEN] ;

    while ( (fgets(ligne, MAX_LEN,fichier) != NULL) && (i<20000000)){ /*fin de fichier non atteinte*/
		i++;
		ligne[strcspn(ligne,"\n")]=0;
		insert_mot_arbre(racine,ligne);
	}
}

int recherche(Arbre *racine,char* mot){
	int i;
	char* suffixe;
	for(i=0;i<MAX_LEN;i++){
		if((*racine)->noeuds[i]!=NULL){
			suffixe = (char*)malloc(MAX_LEN*sizeof(char));
			strcpy(suffixe,(*racine)->noeuds[i]->suffixe);
			if ((strcmp(mot,suffixe)==0)&&((*racine)->noeuds[i]->complet==TRUE)){
				return TRUE;
			}
			else if ((strcmp(mot,suffixe)==0)&&((*racine)->noeuds[i]->complet==FALSE)){
				return FALSE;
			}	
			else{
				if (strlen(plus_long_prefixe(suffixe, mot)) != 0){
					return recherche(&(*racine)->noeuds[i],complement(mot,suffixe));
				}
			}
		}
	}
	return FALSE;
}