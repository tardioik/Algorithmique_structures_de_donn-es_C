#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct noeud {
  char mot[20];
  struct noeud* sag;
  struct noeud* sad;
} Noeud;

typedef Noeud* DicoABR;

DicoABR initDico ();

DicoABR creernoeud(char* mot);

DicoABR creernoeudvide();

DicoABR ajoutMot (DicoABR dico,char* newmot);

DicoABR rechercheMot (DicoABR dico, char* newmot);

DicoABR predecesseur (DicoABR source);

DicoABR supprimeMot (DicoABR dico, char* newmot);

void comparaison (char* mot1, char* mot2, char* souschaine);

void insertion (int k , DicoABR n, char* souschaine, char resultats[][20]);

void suggestionMotsParcours (int k , DicoABR n, char* souschaine, char** resultats);

void suggestionMots (int k,DicoABR dico, char* souschaine);

DicoABR chargerDicoABR(DicoABR dico, char* adresse);

void afficherABR (DicoABR dico);

int contient (char* mot, char* souschaine);

void afficherABRchaine (DicoABR dico, char* souschaine);

void printABR (DicoABR dico);

void afficherABRverimot (DicoABR dico);

void ecrirefichierABR (DicoABR dico, char* adressefichier);

void verimotABR(DicoABR dico, char* adressedico, char* adressefichier);

void veridicoABR(DicoABR dico, char* adressefichier);

