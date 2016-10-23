#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "fonction.h"


char* conversionApresMoins(char *chaine){
	char *ptr = malloc((strlen(chaine)+1)*sizeof(char));
	int i = 0,j = 0;
		while(i < strlen(chaine) && chaine[i]!= '-')
			i++;

		while(++i < strlen(chaine)){
			ptr[j] = chaine[i];
			j++;
		}
	ptr[j] = '\0';
	return ptr;
}


int agrv3NeContientPasDeSigne(char *agrv){
	char* chaine = agrv;
	int i = 0;
	while(i < strlen(chaine) &&  chaine[i]!='-')
		i++;

	return i == strlen(chaine);
}

int sontDesEntiers(char *agrv){
	int i = 0;
	while(i < strlen(agrv)){
	    if(isdigit(agrv[i])){
			i++;
		}
	}
	return i == strlen(agrv);
}

int verifierLeNombreDeSigne(char *chaine){
	int signe = 0;
	for(int i = 0 ; i < strlen(chaine); i++){
		if(isdigit(chaine[i]) || chaine[i] =='-'){
			if(chaine[i] == '-')
				signe++;
		}else
		    return 0;
	}
	return signe == 1 && strlen(chaine) > 1;
}


int trouverLindice(char *chaine){
	int indice = 0,i = 0;
	if(chaine[i]!='-'){
		indice = atoi(chaine);
	}
	return indice;
}

int trouverIntervalle(char *chaine,int colonneInitial){
	char* ch ;
	int intervalle = -1,i = 0;
	while(chaine[i]!='-')
		i++;
	if(++i < strlen(chaine)){
		ch = conversionApresMoins(chaine);
		intervalle = atoi(ch);
	}
	if(intervalle > colonneInitial || intervalle == -1)
		intervalle = colonneInitial;
	else
		intervalle++;
	return intervalle;
}

int caractereValide(char c){
	return  c == ' ' || c == '-' || c == '\n' || c =='\t';
}
