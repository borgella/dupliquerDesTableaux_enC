#ifndef AFFICHAGE_H
#define AFFICHAGE_H

//Erreur d'ouverture du fichier
#define OUVERTURE_FICHIER_ERREUR 1

//Fichier ne comporte aucune donn�e
#define FICHIER_SANS_DONNEE_ERREUR 2

// Erreur de syntaxe d'appel
// exemple Erreur de syntaxe dans l'un des domaines
// expmle Erreur concernant une option
// par exemple ./dup2 -P 3  car il faut avoir deux domaines pour -P
// par exemple ./dup2 -T 3  car -T n'existe pas
//
#define SYNTAX_APPEL_ERREUR 3


// exemple : les donn�es ne sont pas des entiers (par exemple 23a6 ou 23.6)
// exemple : la derni�re ligne avec entier (car celle qui contient au moins un entier) n'est pas termin� avec '\n' 
#define FICHIER_CORROMPU_ERREUR 4


//Echec d'allocation de m�moire
#define MEMOIRE_INSUFFISANTE_ERREUR 5

//Domaine de -P non disjoints
#define DOMAINES_NON_DISJOINTS 6

//A utiliser si vous rencontrer une erreur non pr�vue par les codes d'erreurs pr�c�dents
#define AUTRE_ERREUR 7

//Cette structure offre un type de donn�e rep�sentant un tableau 2D
struct tab2D{
  int lignes; //nombre de lignes du tableau 2D
  int colonnes; //nombre de colonnes du tableau 2D
  int *ptr; // repr�sente un tableau de int, celui-ci est interpr�t� comme
             // un tableau 2D de taille lignes x colonnes
};



/**
* affiche une varaible de type struct tab2d
*
*@param mat le tableau 2D � afficher
*/
void affiche_Tab2D(struct tab2D mat);

/**
* Affiche un message d'erreur sur le canal d'erreur selon les cas d�finis
*
*@param err l'erreur � signaler
*/
void signaler_erreur(int err);

#endif
