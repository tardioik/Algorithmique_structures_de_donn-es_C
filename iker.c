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


DicoABR creernoeudvide() {
  DicoABR new = malloc (sizeof(Noeud));
  new->mot[0] = '\0';
  new-> sad = NULL;
  new-> sag = NULL;
  return new;
}


DicoABR initDico () {
  DicoABR new = creernoeudvide();
  return new;
}


DicoABR creernoeud(char* newmot) {
  DicoABR new = malloc (sizeof(Noeud));
  strcpy( new->mot, newmot);
  new-> sad = creernoeudvide();
  new-> sag = creernoeudvide();
  return new;
}

DicoABR ajoutMot (DicoABR dico,char* newmot) {
  DicoABR temp = dico;
  while (strcmp(temp->mot,"\0")!=0) {
    if (strcmp(temp->mot,newmot)<0) {
      temp = temp->sad;
    }
    else if (strcmp(temp->mot,newmot)>0) {
      temp = temp->sag;
    }
    else if (strcmp(temp->mot,newmot)==0) {
      return dico;
    }
  }
  strcpy(temp->mot,newmot);
  temp->sag = creernoeudvide();
  temp->sad = creernoeudvide();
  return dico;
}

DicoABR rechercheMot (DicoABR dico, char* newmot) {
  DicoABR temp = dico;
  while (strcmp(temp->mot,"\0")!=0) {
    if (strcmp(temp->mot,newmot)<0) {
      temp = temp->sad;
    }
    else if (strcmp(temp->mot,newmot)>0) {
      temp = temp->sag;
    }
    else {
      return temp;
    }
  }
  return NULL;
}

DicoABR predecesseur (DicoABR source) {
  DicoABR temp = source;
  temp = temp->sag;
  while (strcmp(temp->sad->mot,"\0")!=0) {
    temp = temp->sad;
  }
  return temp;
}

DicoABR supprimeMot (DicoABR dico, char* newmot) {
  DicoABR temp = rechercheMot(dico,newmot);
  DicoABR temp2 = NULL;
  if (temp!=NULL) {
    if ((strcmp(temp->sag->mot,"\0")!=0)&&(strcmp(temp->sad->mot,"\0")!=0)) {
      temp2 = predecesseur(temp);
      strcpy(temp->mot,temp2->mot);
      supprimeMot(temp2,newmot);
    }
    else if (strcmp(temp->sag->mot,"\0")!=0) {
      temp2 = temp->sag;
      strcpy(temp->mot,temp2->mot);
      temp->sad = temp2->sad;
      temp->sag = temp2->sag;
      free(temp2);
      return dico;
    }
    else if (strcmp(temp->sad->mot,"\0")!=0) {
      temp2 = temp->sad;
      strcpy(temp->mot,temp2->mot);
      temp->sag = temp2->sag;
      temp->sad = temp2->sad;
      free(temp2);
      return dico;
    }
    else {
      free(temp->sag);
      free(temp->sad);
      strcpy(temp->mot,"\0");
      return dico;
    }
  }
  return dico;
}

void navigation (DicoABR dico) {
  int choix = -1;
  DicoABR temp = dico;
  if (temp==NULL) {
    printf("Dictionnaire vide !\n\n");
  }
  else {
    printf("Racine : %s\n\n", temp->mot);
    while (choix!=0) {
      printf("Gauche (1), droite (2), retour debut (3) quitter (0) ? : \n\n");
      while ((choix>3)||(choix<0)) {
        scanf("%d",&choix);
        printf("\n\n");
      }
      switch (choix) {
        case 0 :
          break;
        case 2 :
          temp = temp->sad;
          printf("Noeud : %s\n\n", temp->mot);
          if (strcmp(temp-> mot,"\0")==0) choix = 3;
          else choix = -1;
          break;
        case 1 :
          temp = temp->sag;
          printf("Noeud : %s\n\n", temp->mot);
          if (strcmp(temp-> mot,"\0")==0) choix = 3;
          else choix = -1;
          break;
        default :
          temp= dico;
          printf("Racine : %s\n\n", temp->mot);
          choix = -1;
          break;
      }
    }
    printf("Programme quitte avec succes !\n\n");
  }
}

int comparaison (char* mot1, char* mot2, char* souschaine) {
  int nb1 = 0;
  int nb2 = 0;
  int test1 = 0;
  int test2 = 0;
  int i = 0;
  while ((test1==0)||(test2==0)) {
    if (test1==0) {
      if (mot1[i]==souschaine[i]) {
        nb1++;
      }
      else test1 = 1;
    }
    if (test2==0) {
      if (mot2[i]==souschaine[i]) {
        nb2++;
      }
      else test2 = 1;
    }
    i++;
  }
  if (nb1>nb2) {
    return 1;
  }
  if (nb2>nb1) {
    return 2;
  }
  else {
    if (mot1[nb1]<mot2[nb2]) {
      return 1;
    }
    else return 2;
  }
}

void decalage (int k, char resultats[][20], int indice) {
  int i;
  if (indice<k) {
    for (i=k-1; i>indice; i--) {
      strcpy(resultats[i],resultats[i-1]);
    }
  }
}

int TestCaseVide (int indice, char resultats[][20]) {
  if (resultats[indice]==NULL) return 1;
  else return 0;
}

void insertion (int k , DicoABR n, char* souschaine, char resultats[][20]) {
  int i;
  if (n->mot[0]==souschaine[0]) {
    for (i=0; i<k; i++) {
      if (TestCaseVide(i,resultats)==1) {
        strcpy(resultats[i],n->mot);
        break;
      }
      else if (comparaison(n->mot,resultats[i],souschaine)==1) {
        decalage (k,resultats,i);
        strcpy(resultats[i],n->mot);
        break;
      }
    }
  }
}



void suggestionMotsParcours (int k , DicoABR n, char* souschaine, char resultats[][20]) {
  insertion (k, n, souschaine, resultats);
  if (strcmp(n->sad->mot,"\0")!=0) {
    suggestionMotsParcours(k, n->sad, souschaine, resultats);
  }
  if (strcmp(n->sag->mot,"\0")!=0) {
    suggestionMotsParcours(k, n->sag, souschaine, resultats);
  }
}


void suggestionMots (int k,DicoABR dico, char* souschaine, char resultats[k][20]) {
  int i = 0;
  for (i=0; i<k; i++) resultats[i][0]='\0';
  suggestionMotsParcours(k,dico,souschaine,resultats);
}


DicoABR chargerDicoABR(DicoABR  dico, char* adresse) {
  FILE* fichier = fopen(adresse, "r");
  if (fichier!=NULL) {
    char mot[20];
    printf("Ouverture realisee avec succes ! \n\n");
    dico = initDico();
    while (fgets(mot,20,fichier)!=NULL) {
      int len = strlen(mot);
      mot[len-1]='\0';
      if ( mot[len-2] == 13){
        mot[len-2]='\0'; // CR !!!
      }
      dico = ajoutMot(dico, mot);
    }
    fclose(fichier);
  }
  else printf("Echec d'ouverture !\n\n");
  return dico;
}


void afficherABR (DicoABR dico) {
  DicoABR temp = dico;
  if (temp->sag!=NULL) afficherABR(temp->sag);
  printf("%s\n",temp->mot);
  if (temp->sad!=NULL) afficherABR(temp->sad);
}

int contient (char* mot, char* souschaine) {
  int i = 0;
  int j = 0;
  int test = 0;
  while (mot[i]!='\0') {
    if (mot[i]==souschaine[0]) {
      test = 1;;
      j = 0;
      while (test) {
        if ( souschaine[j] != '\0' && souschaine[j] != mot[i+j] ){
          test = 0;
        }
        if ( souschaine[j] == '\0' || mot[i+j] == '\0' ) break;
        j++;
      }
      if (test == 1) return 1;
    }
    i++;
  }
  return 0;
}


void afficherABRchaine (DicoABR dico, char* souschaine) {
  DicoABR temp = dico;
  if (temp->sag!=NULL) afficherABRchaine(temp->sag, souschaine);
  if (contient(temp->mot,souschaine)==1) printf("%s\n",temp->mot);
  if (temp->sad!=NULL) afficherABRchaine(temp->sad, souschaine);
}

void printABR (DicoABR dico) {
  int choix = -1;
  char souschaine[20];
  while ((choix<0)||(choix>2)) {
    printf("Que voulez vous faire ?\n\n-> Tapez (1) pour afficher le dictionnaire dans l'ordre lexicographique\n\n-> Tapez (2) pour afficher les mots contenant votre sous-chaine\n\n-> Tapez (0) pour sortir\n\n");
    scanf("%d",&choix);
    printf("\n\n");
     switch (choix) {
      case 1 :
        afficherABR(dico);
        printf("\n\n");
        choix = -1;
        break;
      case 2 :
        printf("Entrez votre sous-chaine :\n\n");
        scanf("%s",souschaine);
        printf("\n\n");
        afficherABRchaine(dico, souschaine);
        printf("\n\n");
        choix = -1;
        break;
      default :
        printf("Fin du programme print !\n\n");
        choix = 0;
        break;
    }
  }
}

void afficherABRverimot (DicoABR dico, FILE* fichier) {
  DicoABR temp = dico;
  if (temp->sag!=NULL) afficherABRverimot(temp->sag,fichier);
  if ( dico->mot[0] != '\0')
    fprintf(fichier,"%s\n",temp->mot);
  if (temp->sad!=NULL) afficherABRverimot(temp->sad,fichier);
}

void ecrirefichierABR (DicoABR dico, char* adressefichier){
  FILE* fichier = NULL;
  fichier = fopen(adressefichier, "w+");
  afficherABRverimot (dico,fichier);
  fclose(fichier);
}


void verimotABR(DicoABR dico, char* adressedico, char* adressefichier) {
  int k;
  int i = 0;
  char souschaine[20];
  int choix = -1;
  int test = 1;
  int test1 = -1;
  FILE* fichier;
  FILE* dictionnaire;
  DicoABR dicotemp = NULL;
  dicotemp = chargerDicoABR (dicotemp,adressefichier);
  fichier = fopen(adressefichier, "r");
  while ((choix<0)||(choix>2)) {
    printf("Que voulez vous faire ?\n\n-> Tapez (1) pour parcourir votre fichier\n\n-> Tapez (0) pour sortir\n\n");
    scanf("%d",&choix);
    printf("\n\n");
    switch (choix) {
      case 1 :
        if (fichier!=NULL) {
          while (test == 1) {
            if (fgets(souschaine,20,fichier)!=NULL&&souschaine[0]!='\0') {
              souschaine[strlen(souschaine)-1]='\0';
              printf("Votre mot est : %s\n\n",souschaine);
              printf("Combien de suggestions voulez-vous obtenir ?\n\n");
              scanf("%d",&k);
              char resultats[k][20];
              printf("\n\n");
              for (i=0; i<k; i++) {
                resultats[i][0] = '\0';
              }
              suggestionMots (k,dico,souschaine, resultats);
              printf("Voici les resultats du programme de suggestions : \n\n");
              for (i=0; i<k; i++) {
                printf("[%d] -> %s\n",i+1,resultats[i]);
              }
              do {
                printf("\n\n");
                printf("Que voulez-vous faire ?\n\n-> Tapez (1) pour remplacer ce mot dans le fichier\n\n-> Tapez (2) pour ajouter ce mot au dictionnaire\n\n-> Tapez (0) pour ne rien faire\n\n");
                scanf("%d",&test1);
                printf("\n\n");
              } while (test1!=1 && test1!=0 && test1!=2);
              switch (test1) {
                case 1 :
                  printf("Quel est l'indice du mot choisi ?\n\n");
                  scanf("%d",&i);
                  printf("\n\n");
                  dicotemp = supprimeMot(dicotemp,souschaine);
                  dicotemp = ajoutMot(dicotemp,resultats[i-1]);
                  printf("Mot corrige !\n\n");
                  break;
                case 2 :
                  dico = ajoutMot(dico,souschaine);
                  printf("Mot ajouté au dictionnaire !\n\n");
                  break;
                default :
                  break;
              }
              do {
                printf("Voulez-vous continuer ?\n\n-> Tapez (1) pour oui\n\n-> Tapez (0) pour non\n\n");
                scanf("%d",&test);
                printf("\n\n");
              } while ((test>1)||(test<0));
            }
            else {
              printf("Fin de fichier atteinte !\n\nRetour au debut du fichier\n\n");
              fclose(fichier);
              ecrirefichierABR (dicotemp,adressefichier);
              ecrirefichierABR (dico, adressedico);
              fichier = fopen(adressefichier, "r");
              choix = -1;
            }
          }
          fclose(fichier);
          ecrirefichierABR (dicotemp,adressefichier);
          ecrirefichierABR (dico, adressedico);
          choix = 0;
          break;
        }
        else {
          printf("Fichier vide !\n\nRetour au menu :\n\n");
          fclose(fichier);
          ecrirefichierABR (dicotemp,adressefichier);
          ecrirefichierABR (dico, adressedico);
          choix = 0;
          break;
        }
      default :
        printf("Fin du programme verimot !\n\n");
        choix = 0;
        break;
    }
  }
}


void veridicoABR(DicoABR dico, char* adressefichier) {
  int k;
  int i = 0;
  int test = 1;
  int test1 = 1;
  int test2 = 1;
  int n;
  char souschaine[20];
  FILE* fichier;
  while (test==1) {
    printf("Nouvelle recherche :\n\n");
    fichier = fopen(adressefichier, "r");
    printf("Quel est le mot à rechercher ?\n\n");
    scanf("%s",souschaine);
    printf("\n\n");
    printf("Combien de suggestions voulez-vous obtenir ?\n\n");
    scanf("%d",&k);
    char resultats[k][20];
    printf("\n\n");
    for (i=0; i<k; i++) {
      resultats[i][0] = '\0';
    }
    i=0;
    suggestionMots (k,dico,souschaine, resultats);
    printf("Voici les resultats du programme de suggestions : \n\n");
    n = -1;
    for (i=0; i<k; i++) {
      if ((resultats[i][0]=='\0')&&(n==-1)) n = i;
      printf("[%d] -> %s\n",i+1,resultats[i]);
    }
    if (n==-1) n=k;
    printf("\n\n");
    for (i=0; i<n; i++) {
      do {
        printf("Votre mot est : %s\n\n",resultats[i]);
        printf("Que voulez-vous faire ?\n\n-> Tapez (1) pour changer ce mot dans le dictionnaire\n\n-> Tapez (2) pour enlever ce mot du dictionnaire\n\n-> Tapez (0) pour valider ce mot\n\n");
        scanf("%d",&test1);
        printf("\n\n");
      } while (test1!=1 && test1!=0 && test1!=2);
      switch (test1) {
        case 1 :
          printf("Quel est le mot à mettre à la place de celui-ci ?\n\n");
          char nouveau[20];
          scanf("%s",nouveau);
          printf("\n\n");
          dico = supprimeMot(dico,resultats[i]);
          navigation(dico);
          dico = ajoutMot(dico,nouveau);
          printf("Mot corrige !\n\n");
          break;
        case 2 :
          dico = supprimeMot(dico,resultats[i]);
          printf("Mot enleve du dictionnaire !\n\n");
          break;
        default :
          printf("Mot valide !\n\n");
          break;
      }
      do {
        printf("Voulez-vous continuer ?\n\n-> Tapez (1) pour oui\n\n-> Tapez (0) pour non\n\n");
        scanf("%d",&test2);
        printf("\n\n");
      } while ((test2>1)||(test2<0));
      if (test2==0) {
        break;
      }
      if (i!=n-1) {
        do {
          printf("Voulez-vous continuer ?\n\n-> Tapez (1) pour oui\n\n-> Tapez (0) pour non\n\n");
          scanf("%d",&test2);
          printf("\n\n");
        } while ((test2>1)||(test2<0));
        if (test2==0) {
          n=i;
        }
      }
      else {
        printf("Fin des suggestions ! \n\n");
      }
    }
    printf("Fin de la revision !\n\n");
    fclose(fichier);
    ecrirefichierABR (dico,adressefichier);
    do {
      printf("Voulez-vous recommencer ?\n\n-> Tapez (1) pour oui\n\n-> Tapez (0) pour non\n\n");
      scanf("%d",&test);
      printf("\n\n");
    } while ((test>1)||(test<0));
  }
}
