#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "traitementDuTableau.h"
#include "util.h"


int leNombreLigne(char *letableau){
	int nbre = 0, i = 0, slash = 0, k = 0, c;
 	while((c = letableau[k++])!= EOF){
		if(isdigit(c))
			i++;
		if( c == '\n' && slash < 1){
			if(i > 0){
				nbre++;
				slash++;
			}
			i = 0;
		}else
			slash = 0;
			
   	} 
	return nbre;
}




int leNombreColonne(char *letableau){
	int c = 0, cpt = 0,max = 0,n = 0,i = 0;
		while((c = letableau[i++])!= EOF){
			if(c!='\n'){
				if((isdigit(c))&& n == 0){
					n = 1;
					cpt++;	
				}else if(c ==' '){
					n = 0;
				}
			} else {
				if(cpt > max)
					max = cpt;
					cpt = 0;
					n = 0;
				}	
		}
	return max;

}

int *remplirLeTableau(char* letableau,Tableau *t){
	int c = 0,i = 0, j = 0, espace = 0,antislash = 0,colonne = 0,entier = 0;
	int tailleChaine = 10, k = 0;
	char *chaine = malloc(tailleChaine*sizeof(char));
	int * ptr = calloc(t->taille,sizeof(int));
	while((c = letableau[k++])!=EOF ){
		 if((isdigit(c)) || caractereValide(c)){
			if((isdigit(c)) || c == '-'){
				entier++;  
				if(i < tailleChaine){
					chaine[i++] = c;
				}else{
					chaine = agrandirLeTableau(chaine,tailleChaine);
					chaine[i++] = c;
					tailleChaine*=2;
				}
					espace = antislash = 0;		
			}else if((c == ' '|| c == '\t') && espace < 1){
					if(entier > 0){
						chaine[i] = '\0';
						ptr[j++] = atoi(chaine);
						i = 0;
						espace++;
						colonne++;
						entier = 0;
					}
			}
			if(c == '\n' && antislash < 1){
				antislash++;
				if(espace == 0){
					if(entier > 0){
						chaine[i] = '\0';
						ptr[j++] = atoi(chaine);
						i = 0;		
						espace++;
						colonne++;
						entier = 0;
					}			
				}
				if((colonne < t->colonnes) && entier > 0 )
					j += (t->colonnes - colonne);
				
				colonne = 0;
			}
			 
		}else{
			ptr = NULL;
			break;	
		 }
		
	}
	free(chaine);
	return ptr;
}
