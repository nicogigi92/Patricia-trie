#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arbre.h"
#include "general.h"


int max(int int1,int int2){
	if (int1>=int2) 
		return int1;
	else 
		return int2;
}

int min(int int1,int int2){
	if (int1<=int2) 
		return int1;
	else 
		return int2;
}

char*  plus_long_prefixe(char* str1,char* str2){ 
	int len_min = min(strlen(str1),strlen(str2))+1;
	int i=0;
	char *prefixe=NULL;
	prefixe=malloc(len_min*sizeof(char));
	while (str1[i]==str2[i]){
		prefixe[i]=str1[i];
		i++;
	}
	prefixe[i]='\0';
	return prefixe;
}

char*  complement(char* str1,char* str2){ 
	int len_max = max(strlen(str1),strlen(str2))+1;
	int j;
	int i=0;
	char *prefixe=NULL;
	prefixe=malloc(len_max*sizeof(char));
	while (str1[i]==str2[i]){
		i++;
	}
	j=0;
	while (str1[i]!='\0'){
		prefixe[j]=str1[i];
		i++;
		j++;
	}	
	prefixe[j]='\0';
	return prefixe;
}
