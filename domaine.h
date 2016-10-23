#ifndef DOMAINE_H
#define DOMAINE_H
/*
int verifierDomaine(int argc,char *agrv[]);

int leDomaineEstValide(int agrc,char *agrv[]);
*/
int verifierDomaine(int argc,char *agrv[]);

int verifierCommande(char *chaine);

int leDomaineEstValide(int agrc,char *agrv[]);

int domainePermise(char carac);

int valeurPermise(char *chaine);

int valeurNonPermise(char *chaine);

int chaineEstUnDomaine(char *chaine);
#endif