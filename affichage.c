#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include "affichage.h"

void signaler_erreur(int err)
{
    switch (err)
    {
    case OUVERTURE_FICHIER_ERREUR:
        fprintf(stderr,"Erreur d'ouverture du fichier.\n");
        break;
    case FICHIER_SANS_DONNEE_ERREUR:
        fprintf(stderr,"Le fichier ne comporte aucun entier.\n");
        break;
    case SYNTAX_APPEL_ERREUR:
        fprintf(stderr,"Erreur de syntaxe.\n");
        break;
    case  FICHIER_CORROMPU_ERREUR:
        fprintf(stderr,"Fichier corrompu.\n");
        break;
    case  MEMOIRE_INSUFFISANTE_ERREUR:
        fprintf(stderr,"Memoire insuffisante.\n");
        break;
    case  DOMAINES_NON_DISJOINTS:
        fprintf(stderr,"Domaines non disjoints.\n");
        break;        
    case  AUTRE_ERREUR:
        fprintf(stderr,"Autre erreur.\n");
        break;
    default:
        break;
    }
}


void affiche_Tab2D(struct tab2D mat)
{
    if (mat.lignes>0 && mat.colonnes>0 && mat.ptr!=NULL)
    {
        int (*lignePtr)[mat.colonnes];
        lignePtr = (int  (*)[mat.colonnes]) mat.ptr;
        for (int i = 0 ; i < mat.lignes ; i++)
        {
            for (int j = 0 ; j < mat.colonnes ; j++)
            {
                printf("%5d ",lignePtr[i][j]);
            }
            printf("\b\n");
        }
    }
    else
    {
        signaler_erreur(FICHIER_SANS_DONNEE_ERREUR);
    }
}
