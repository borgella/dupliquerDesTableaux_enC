#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "fonction.h"
#include "util.h"
#include "domaine.h"

int* remplirTableau(FILE *fp,Tableau *t){
	int c = 0,i = 0, j = 0, espace = 0,antislash = 0,colonne = 0,entier = 0;
	int tailleChaine = 10;
	char *chaine = malloc(tailleChaine*sizeof(char));
	int * ptr = calloc(t->taille,sizeof(int));
	while((c = fgetc(fp))!=EOF){
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
					}
				}
				if((colonne < t->colonnes)  )
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

int nombreLigne(FILE *fichier){
	int nbre = 0, i = 0, slash = 0, c;
 	while((c = fgetc(fichier))!= EOF){
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


int nombreColonne(FILE *fichier){
	int c = 0, cpt = 0,max = 0,n = 0;
		while((c= fgetc(fichier))!= EOF){
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


void dupliquerLaColonne(Tableau *t){
	t->tab = dupliquerC(t);
	mettreAjourApresDupC(&t->taille,t->lignes,&t->colonnes);
}
void dupliquerLesColonnesOuLignesDeAaN(Tableau *t,int intervalle,char c){
	while(t->indice < intervalle){
		if(c == 'C'){
			dupliquerLaColonne(t);
			t->indice++;
		}else{
			dupliquerLaLigne(t);
			t->indice++;
			}
	}
}

int* dupliquerC(Tableau *t){
	int *ptr = calloc((t->taille + t->lignes),sizeof(int));
	int (*ptrligne)[t->colonnes] = (int(*)[t->colonnes])t->tab;
	int *colonneADupliquer = calloc(t->lignes,sizeof(int));
	int i = 0,j = 0,k = 0,cpt = 0;

	for(i = 0; i < t->lignes; i++){
		colonneADupliquer[i] = ptrligne[i][t->indice];
	}

	for( i = 0 ; i < (t->taille + t->lignes) ; ++i){
		if(cpt != t->colonnes){
			ptr[i] = t->tab[j++];
			cpt++;
		}else{
			ptr[i] = colonneADupliquer[k++];
			cpt = 0;
		}
	}
	t->tab = ptr;
	return t->tab;
}

void mettreAjourApresDupC(int *taille,int ligne,int *colonne){
	int *ptrTaille = taille;
	int *ptrColonne = colonne;
	*ptrTaille = *ptrTaille + ligne;
	*ptrColonne = *ptrColonne + 1;

}
void permuterLesColonnes(Tableau *t,int premier, int deuxieme){
	int (*ptrpremier) [t->colonnes] = (int (*)[t->colonnes]) t->tab;
	int * temporaire1 = malloc(t->lignes * sizeof(int));
	int * temporaire2 = malloc(t->lignes * sizeof(int));

	for(int i = 0 ; i < t->lignes ; i++){
		temporaire1[i] = ptrpremier[i][premier];
		temporaire2[i] = ptrpremier[i][deuxieme];
		ptrpremier[i][premier] = temporaire2[i];
		ptrpremier[i][deuxieme] = temporaire1[i];
	}
	free(temporaire1);
	free(temporaire2);
}

void permuterLesLignes(Tableau *t,int premier,int deuxieme){
	int (*ptrpremier) [t->colonnes] = (int (*)[t->colonnes]) t->tab;
	int (*ptrdeuxieme)[t->colonnes] = (int (*)[t->colonnes]) t->tab;
	int	*temporaire = calloc(t->colonnes,sizeof(int));
	for(int i = 0; i < t->colonnes; i++){
		if(i < t->colonnes){
			temporaire[i] = ptrpremier[premier][i];
			ptrpremier[premier][i]= ptrdeuxieme[deuxieme][i];
			ptrdeuxieme[deuxieme][i] = temporaire[i];
			}
	}
	free(temporaire);
}

void dupliquerLaLigne(Tableau *t){
	t->tab = dupliquerL(t);
	mettreAjourApresDupL(&t->taille, &t->lignes, t->colonnes);
}

int* dupliquerL(Tableau *t){
	int *ptr = calloc((t->taille + t->colonnes),sizeof(int));
	int (*ptrligne)[t->colonnes] = (int(*)[t->colonnes])t->tab;
	int *ligneADupliquer = calloc(t->colonnes,sizeof(int));
	int i,j = 0;

	for(i = 0; i < t->colonnes; i++){
		ligneADupliquer[i] = ptrligne[t->indice][i];
	}

	for( i = 0 ; i < (t->taille + t->colonnes) ; i++){
		if(i < t->taille){
			ptr[i] =t->tab[i];
		}else{
			ptr[i] = ligneADupliquer[j++];
		}
	}
	t->tab = ptr;

	return t->tab;
}


void mettreAjourApresDupL(int *taille ,int *ligne, int colonne){
	int *ptrTaille = taille;
	int *ptrLigne = ligne;
	*ptrTaille = *ptrTaille + colonne;
	*ptrLigne = *ptrLigne + 1;
}

struct tab2D initialiserTab2d(Tableau *t){
	struct tab2D table;
	table.lignes = t->lignes;
	table.colonnes = t->colonnes;
	table.ptr = t->tab;
	return table;
}

char* agrandirLeTableau(char *letableau,int taille){
	char *ptr_tableau = calloc((taille*2),sizeof(char));
	for(int i = 0; i < taille; i++){
		ptr_tableau[i] = letableau[i];
	}
	return ptr_tableau;
}
