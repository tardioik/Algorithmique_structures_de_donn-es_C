#include <stdlib.h>
#include <stdio.h>
#include "prototype.h"
#include "iker.h"
#include <math.h>
#include <string.h>

int main()
{

	int type = -1;
	int choix =-1;
 	DicoABR dico1;
 	printf("\n TYPE DICTIONNAIRE ? \n");
 	printf("Quel type de dictionnaire voulez-vous utiliser ?\n-> (1) pour arbre de recherche\n-> (2) pour arbre lexicographique\n");
	while ((type>2)||(type<1)) 
	{
		printf("Votre choix :\n");
		scanf("%d",&type);
		printf("\n");
	}
	if (type==1) 
	{
		dico1 = chargerDicoABR(dico1,"./dictionnaire.txt");
	
		while ((choix<0)||(choix>3)) 
		{
			printf(" MENU \n");
			printf("Choisissez les fonctions que vous voulez utiliser :\n->(1) pour print\n->(2) pour verimot\n->(3) pour veridico\n->(0) pour sortir du programme\n");
			scanf("%d",&choix);
			printf("\n\n");
	   		
			switch (choix) 
			{
	      			case 1 :
					printf(" PRINT \n");
					if (type == 1) printABR(dico1);
					choix = -1;
					break;
	      			case 2 :
					printf(" VERIMOT \n");
					if (type == 1) verimotABR(dico1,"./dictionnaire.txt","./file.txt");
					choix = -1;
					break;
	      			case 3 :
					printf(" VERIDICO \n");
					if (type == 1) veridicoABR(dico1,"./dictionnaire.txt");
					choix = -1;
					break;
	      			default :
					printf(" Fin \n");
	       				choix = 0;
					break;
	    		}
	  	}
	}
	if (type==2)
	{
		Mot *mot=NULL;
		Dico *dico=NULL;
		dico=creerDico();
		dico = chargerDicoAl(dico);

	   	do
		{
			int a=affichage_menu();

			switch (a)
			{
				case 1:
	    			{
					clean();
					printf("\t INITIALISATION D'UN DICTIONNAIRE\n\n\n");
					mot = init_mot();
					dico=creerDico();
					dico = initDico2(dico, mot);
				}break;

				case 2:
				{
					clean();
					Dico *dico2=NULL;
					printf("\t CHERCHER LE PLUS LONG PREFIXE \n\n\n");
					mot = init_mot();
					if ((dico2 = prefixeMot(dico, mot))!=NULL)
						printf("Le dernier caractere pointe du plus long prefixe est %c.\n", dico2->c);
					else
						printf("Il n'y a pas de prefixe pour ce mot.\n");
				}break;

				case 3:
				{	
					a=affichage_print();

					switch(a)
					{
						case 1:
						{
							printf("Les mots sont : \n\n");
							afficherMot(dico, NULL);
						}break;
						case 2:
						{
							Dico *dico2=NULL;
							char chaine[50];
							printf("Entre une chaine de caractere\n");
							fgets(chaine, sizeof(chaine), stdin);

							if ((dico2=ajusterDico(dico, chaine))!=NULL)
							{
								printf("Les mots sont : \n\n");
								afficherMot(dico2, chaine);
							}
							else
								printf("Ce prefixe n'existe pas dans le dictionnaire.\n");
						}break;
						case 3:
						{
							printf("Entrez un entier.\n");
							int nbCar, k=0;
							scanf("%d", &nbCar);
							viderBuffer();
							afficherMotLong(dico, NULL, nbCar);
						
						}break;
						case 4:
						{
							clean();
							continue;
						}break;
					}
				
				} break;

				case 4:
				{
					clean();
					printf("\t CHERCHER UN MOT DANS LE DICTIONNAIRE\n\n\n");
					mot = init_mot();
					if (rechercheMot2(mot, dico))
						printf("Le mot a ete trouve\n");
					else
						printf("Le mot n'a pas ete trouve\n");
				}break;

				case 5:
				{
					clean();
					printf("\t AJOUTER UN MOT DANS LE DICTIONNAIRE\n\n\n");
					mot = init_mot();
					dico = ajoutMot2(mot, dico);
				}break;

				case 6:
				{
					clean();
					printf("\t SUPPRIMER UN MOT DU DICTIONNAIRE \n\n\n");
					mot = init_mot();
					dico = supprimeMot2(mot, dico);
				}break;

				case 7:
				{
					clean();
					printf("\t SUGGESTION DE MOTS \n\n\n");
					Mot *souschaine=NULL;
					souschaine=init_mot();

					Suggestion *mot = NULL;
					int b=0, i;

					while (b<1 || b>10)
					{
						printf("Veuillez entrer un nombre positif. \n");
						printf("Il représentera le nombre de suggestions de mots qui vous seront proposes\n");
						scanf("%d", &b);
						viderBuffer();
					}
				

					mot = suggestionMots2 (dico, souschaine);
					if (mot!=NULL)
						mot=mot->prec;
			
					for (i=b; i>0; i--)
					{
						if (mot!=NULL)
						{
					
							printf("Suggestion %d | %s\n", b-i+1, mot->chaine);
							mot=mot->prec;
						}
						else 
						{
							printf("Il n'y a plus d'autres suggestions disponbiles \n");
							break;
						}
					}				
								
				}break;

				case 8:
				{
					clean();
					printf("\t VERIMOT \n\n\n");
					dico=verimot(dico);
				}break;

				case 9:
				{
					clean();
					printf("\t VERIDICO \n\n\n");
					dico=veridico(dico);				

				}break;

				case 10:
				{
					clean;	
					
					FILE* fichier2=fopen("test2.txt", "w+");
					if (fichier2!=NULL)
					{
						dechargerDicoAl(dico, NULL, fichier2);
						remove("dictionnaire.txt");
						rename("test2.txt", "dictionnaire.txt");
						fclose(fichier2);
					}
					printf("Fin du programme\n");
					return 0;
				}break;

			}

		
		} while (1);

	}
	return 0;
}
