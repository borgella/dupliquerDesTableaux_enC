#ifndef FONCTION_H
#define FONCTION_H
#include "affichage.h"

typedef struct Tableau
{
	int *tab;
	int taille;
	int indice;
	int lignes;
	int colonnes;
}Tableau;

void initialiserLaTable(struct tab2D table,Tableau *t);

int *remplirTableau(FILE *fichier,  Tableau *t);

int nombreLigne(FILE *fichier);

int nombreColonne(FILE *fichier);

void dupliquerLesColonnesOuLignesDeAaN(Tableau *t,int intervalle,char c);

void dupliquerLaColonne(Tableau *t);

int * dupliquerC(Tableau *t);

void mettreAjourApresDupC(int *taille,int ligne,int *colonne);

void permuterLesColonnes(Tableau *t,int premier,int deuxieme);

void dupliquerLaLigne(Tableau *t);

int *dupliquerL(Tableau *t);

void mettreAjourApresDupL(int *taille, int *ligne,int colonne);

void permuterLesLignes(Tableau *t,int premier,int deuxieme);

struct tab2D initialiserTab2d(Tableau *t);

char* agrandirLeTableau(char *tableau,int taille);
#endif
