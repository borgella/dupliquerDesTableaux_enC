#--------------------------
#Declaration des variables
CC = gcc
CFLAGS = -Wall -std=c99 -g
LDFLAGS = -lm
#-------------------------

#------COMMENT ON OBTIENT LE DUP EXECUTABLE-------------------
#PROG = dup2 ou dup2 est le nom qu'on a choisi pour l executable
PROG = dup2			
SCRS = dup2.c fonction.c domaine.c util.c affichage.c traitementDuTableau.c
#--------------------------

#On obtient les .objets necessaires pour les liens par la conversion des .c des sources (SCRS)
#---------------------------
OBJS = $(SCRS:.c=.o)
#--------------------------

#----------------------------
#compilation 
$(PROG) : $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG)
#----------------------------------
	
# Pour les dependannces maintenant 
# Pour obtenir l executable dup.o on inclut (dup.c et les include 
# qui se trouvent dans le fichier dup.c a savoir affichage.h,fonction.h)
dup2:  dup2.c fonction.h domaine.h util.h affichage.h 
fonction.o: fonction.c fonction.h util.c util.h domaine.c domaine.h
domaine.o: domaine.c domaine.h util.c util.h
util.o: util.c util.h
affichage.o : affichage.c affichage.h
traitementDuTableau.o: traitementDuTableau.c traitementDuTableau.h util.c util.h
#--------------------------------

#----------------------------------------
clean:
	/bin/rm  -f core *~ $(OBJS)
