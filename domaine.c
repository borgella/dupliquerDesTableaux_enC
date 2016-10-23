#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "domaine.h"
#include "util.h"

 int leDomaineEstValide(int agrc,char *agrv[]){
	return(verifierDomaine(agrc,agrv) > 0);
}

int verifierDomaine(int argc,char *agrv[]) {
	char *chaine,undomaine,*premier,*deuxieme;
	int retour = 0,compteur_entier = 0,permutation = 0;
	for(int i = 2 ; i < argc ; i++) {
		chaine = agrv[i];
		if(strlen(chaine) == 2 && isalpha(chaine[1])){
			retour = verifierCommande(chaine);
				if(retour == 0)
					break;
			undomaine = chaine[1];
			if(undomaine == 'P')
				permutation++;
		}else if(permutation == 0){
			if(valeurPermise(chaine)){
				if(agrv3NeContientPasDeSigne(chaine)){
					retour = sontDesEntiers(chaine); 
				}else{
					retour = verifierLeNombreDeSigne(chaine);
					if(retour == 0)
						break;					
				}		
			}else{
				retour = 0;
			}
		}else{
			if(valeurPermise(chaine)){
				compteur_entier++;
				if(compteur_entier < 2)
					premier = chaine;
				deuxieme = chaine;
				//ici on traitera le cas ou les domaines sont disjoints
			}
		}
		
	}
    return retour > 0 && compteur_entier >= 2 ;
}

int chaineEstUnDomaine(char *chaine){
	return strlen(chaine) == 2 && verifierCommande(chaine) > 0;
 }

int verifierCommande(char *chaine) {
	int i = 0, retour = 0;
	if(chaine[i++] == '-'){
		if(domainePermise(chaine[i]))
			retour = 1;
	}
   return retour;
}

int domainePermise(char carac){
	return carac == 'C' || carac == 'L'
		   || carac == 'A' || carac == 'P';	
}


int valeurPermise(char *chaine){
	int retour = 0;
		for(int i = 0 ; i < strlen(chaine); i++){
			if(isdigit(chaine[i]) || chaine[i] =='-'){
				retour = 1;
			}else{
				retour = 0;
			}
		}
	return retour;
}

