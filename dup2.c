#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include "fonction.h"
#include "domaine.h"
#include "util.h"
#include "affichage.h"
#include "traitementDuTableau.h"

int main(int agrc, char *argv[]){
	FILE *fichier = NULL;
	Tableau *t = malloc(sizeof(Tableau));
	int taille_t = 10;
	char *letableau = NULL;
	char *chaine ;
	char undomaine = ' ';
	int ligneInitial = 0, colonneInitial = 0,intervalle = 0;
	int nombre_domaine = 0, permutation = 0, premier, deuxieme = 0,compteurEntier = 0 ;
	struct tab2D table ;

	if((strlen(argv[1]) == 2) && ( argv[1][1] =='C' || argv[1][1] == 'L')){
		letableau = malloc(taille_t * sizeof(char));
		undomaine = argv[1][1];
    int i = 0;
		char c;
		while((c = getchar())!= EOF){
			if(i < taille_t){
				letableau[i++] = c ;
			}else{
				letableau = agrandirLeTableau(letableau,taille_t);
				letableau[i++] = c ;
				taille_t *= 2;
			}
		}
		letableau[i++] = c;
	}else if(!leDomaineEstValide(agrc,argv) && agrc > 2){
			signaler_erreur(3);
			exit(1);
	}

	if(letableau != NULL){
		t->colonnes = leNombreColonne(letableau);
		colonneInitial = t->colonnes;
		t->lignes = leNombreLigne(letableau);
		ligneInitial = t->lignes;
		t->taille = t->lignes * t->colonnes;

		if(!t->taille){
			signaler_erreur(2);
			free(letableau);
			exit(2);
		}
		t->tab  = remplirLeTableau(letableau,t);
		if(t->tab == NULL){
			signaler_erreur(4);
			free(letableau);
			exit(1);
		}

	}else if((fichier = fopen(argv[1],"r")) != NULL){
				t->lignes = nombreLigne(fichier);
				ligneInitial = t->lignes;
				rewind(fichier);
				t->colonnes = nombreColonne(fichier);
				colonneInitial = t->colonnes;
				rewind(fichier);
				t->taille = t->lignes * t->colonnes;
				if(!t->taille){
					signaler_erreur(2);
					exit(2);
				}
				t->tab  = remplirTableau(fichier,t);

				if(t->tab == NULL){
					signaler_erreur(4);
					exit(1);
				}
	}else{
		signaler_erreur(1);
		exit(1);
	}

	if(agrc >= 2){//00
		if(agrc > 2){
			for(int i = 2; i < agrc; i++){
					chaine = argv[i];
					if(chaineEstUnDomaine(chaine)){
						undomaine = chaine[1];
						if(undomaine == 'P')
							permutation++;
						else if(undomaine != 'A')
								nombre_domaine++;
					}else if(permutation == 0){
						if(agrv3NeContientPasDeSigne(chaine)){//if00
							t->indice = atoi(chaine);
							if(undomaine == 'C'){
								if(nombre_domaine > 1)
									colonneInitial = (nombre_domaine > 0 )? t->colonnes : colonneInitial;
								if(t->indice < colonneInitial){
									dupliquerLaColonne(t);
								}
							}else if(undomaine == 'L'){
								if(nombre_domaine > 1)
									ligneInitial = (nombre_domaine > 0 )? t->lignes : ligneInitial;
								if(t->indice < ligneInitial){
									dupliquerLaLigne(t);
								}
							}
						}else{//else00
							if(undomaine == 'C'){
								t->indice = trouverLindice(chaine);
								intervalle = trouverIntervalle(chaine,colonneInitial) ;
								if(nombre_domaine > 1)
									colonneInitial = (nombre_domaine > 0 )? t->colonnes : colonneInitial;
								if(t->indice < colonneInitial){
									dupliquerLesColonnesOuLignesDeAaN(t,intervalle,'C');
								}
							}else{
								t->indice = trouverLindice(chaine);
								intervalle = trouverIntervalle(chaine,ligneInitial) ;
								if(nombre_domaine > 1)
									ligneInitial = (nombre_domaine > 0 )? t->lignes : ligneInitial;
								if(t->indice < ligneInitial){
									dupliquerLesColonnesOuLignesDeAaN(t,intervalle,'L');
								}
							}
						}
					}else{
						compteurEntier ++;
						if(compteurEntier >= 2){
							deuxieme = atoi(chaine);
							// si deuxieme a un tiret on va prendre le plus grand indice.
							if( permutation > 0){
								if(undomaine == 'C'){
									if(nombre_domaine > 1)
										colonneInitial = (nombre_domaine > 0 )? t->colonnes : colonneInitial;
										if((premier<colonneInitial) && (deuxieme < colonneInitial))
											permuterLesColonnes(t,premier,deuxieme);
								}else{
									if(nombre_domaine > 1)
										ligneInitial = (nombre_domaine > 0 )? t->lignes : ligneInitial;
										if((premier < ligneInitial)&&(deuxieme < ligneInitial))
											permuterLesLignes(t,premier,deuxieme);
								}
								if(chaineEstUnDomaine(chaine) )
										permutation = 0;
										compteurEntier = 0;
							}

						}else{
							premier = atoi(chaine);
							//apres on va s'arrurer de voir si la chaine contient des entiers ou pas
							//si c est le cas on va prendre le plus petit indice.
						}
					}
		    }//fin for
		}
	}
	table = initialiserTab2d(t);
	affiche_Tab2D(table);
	if(letableau!=NULL){
		free(letableau);
	}else{
		fclose(fichier);
	}
	free(t->tab);
	free(t);
	return 0;
}
