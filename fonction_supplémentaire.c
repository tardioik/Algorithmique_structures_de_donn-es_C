#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototype.h"

void clean()
{
	system("clear");
	system("cls");

}

int affichage_menu() //Menu principal qui revient tant que l'utilisateur n'a pas renvoyé la valeur 8

{
	int a;
        
	do{
	
	printf("\nVous pouvez choisir entre les differentes options\n\n");
        printf("1. Initialiser le dictionnaire.\n");
        printf("2. Chercher le plus long préfixe d'un mot.\n");
	printf("3. Print.\n");        
	printf("4. Rechercher un mot.\n");
        printf("5. Ajouter un mot.\n");
        printf("6. Supprimer un mot.\n");
        printf("7. Sugestion d'un mot.\n");
        printf("8. Verimot.\n");
        printf("9. Veridico.\n");
	printf("10. Quitter.\n");
        

	scanf("%d", &a);
	viderBuffer(); //Pour éviter les désagréments des rentrées \n

	}while (a<1 || a>10);

	return a;


}

int affichage_print()
{
	int a;
        
	do{

	clean();
	printf("\t FONCTIONS PRINT\n\n\n");
	
	printf("\nVous pouvez choisir entre les differentes options\n\n");
        printf("1. Afficher tous les mots du dictionnaire.\n");
        printf("2. Afficher tous les mots commençant par un prefixe.\n");
	printf("3. Afficher les mots avec un nombre de caracteres defini.\n");        
	printf("4. Retour.\n");
        
	scanf("%d", &a);
	viderBuffer(); //Pour éviter les désagréments des rentrées \n

	}while (a<1 || a>4);

	return a;


}

int affichage_verimo()
{
	int a;
        
	do{
	
	printf("\nVous pouvez choisir entre les differentes options\n\n");
        printf("1. Remplacer le mot du fichier par un autre.\n");
        printf("2. Ajouter le mot au dictionnaire.\n");
	printf("3. Retour.\n");
        
	scanf("%d", &a);
	viderBuffer(); //Pour éviter les désagréments des rentrées \n

	}while (a<1 || a>3);

	return a;


}

int affichage_veridico()
{
	int a;
        
	do{
	
	printf("\nVous pouvez choisir entre les differentes options\n\n");
        printf("1. Corriger ce mot dans le dictionnaire.\n");
        printf("2. Suppression de ce mot dans le dictionnaire.\n");
	printf("3. Validation.\n");
	printf("4. Retour.\n");
        
	scanf("%d", &a);
	viderBuffer(); //Pour éviter les désagréments des rentrées \n

	}while (a<1 || a>4);

	return a;


}


void viderBuffer() //Permet d'empêcher les entrées des caracères '\n' dans le buffer
{
	int c = 0;
	while (c != '\n' && c != EOF)
	{
	c = getchar();
	}
}

Mot *creerMot (char val)
{
	Mot *mot=malloc(sizeof(Mot));
	
	mot->c = val;
	mot->suiv = NULL;
	
	return (mot);
}

Mot *init_mot()
{
	char chaine[20];

	printf("Veuillez saisir un mot\n");	

	fgets(chaine, sizeof(chaine), stdin);
	
	int i=0;
	Mot *mot=NULL, *tete=NULL;

	printf("La chaine de caractere est %s\n", chaine);

	while (chaine[i]!='\0' && chaine[i]!='\n')
	{
		
		if(chaine[i]>=65 && chaine[i]<=90)
			chaine[i]=chaine[i]+32;

		if(chaine[i]<97 || chaine[i]>122)
		{
			i++;
		}
		else
		{
			if (i!=0)
			{
				mot->suiv = creerMot(chaine[i]);
				mot = mot->suiv;
			}
			else
			{
				tete = creerMot(chaine[i]);
				mot =tete;
			}
			mot->suiv=NULL;
			i++;
		}
	}

	return(tete);
}

Dico *creerDico()
{
	Dico *dico=malloc(sizeof(Dico));
	dico->succ=NULL;
	dico->alt=NULL;
	
	//printf("Le dictionnaire lexicographique vient d'etre active\n");
	return (dico);
}

void afficherMot(Dico *dico, char val[50])
{

	if (dico == NULL)
	{
		printf("Le dictionnaire est vide. \n");
	}
	else
	{
		int i=0;
		char valeur[50]="";

		if (val!=NULL)
		{
			while(val[i]!='\n' && val[i]!='\0')
			{
				valeur[i]=val[i];
				i++;
			}			
			
		}
		else
		{
			i=0;
		}

		
		while (dico->c != '$' )
		{
			if (dico->alt!=NULL)
				afficherMot(dico->alt, valeur);
			valeur[i]=dico->c;
			i++;

			dico=dico->succ;
		}

		if (dico->c == '$' && dico->alt !=NULL)
			afficherMot(dico->alt, valeur);	
	
		int j=0;


		while (*(valeur+j))
		{
			printf("%c", valeur[j]);
			j++;
		}
		printf("\n");
	}


}

Dico *ajusterDico(Dico *dico, char *chaine)
{
	int i=0;

	if (dico == NULL)
	{
		printf("Le dictionnaire est vide.\n");
		return dico;
	}	


	while(chaine[i]!='\n' && chaine[i]!='\0')
	{
		if (chaine[i]==dico->c)
		{
			printf("Le caractere est %c et le suivant %c\n", dico->c, dico->succ->c);
			i++;
			dico=dico->succ;
			
		}
		else if (chaine[i] < dico->c)
		{
			printf("Je suis else if avec %c\n", dico->c);
			return NULL;
		}
		else
		{
			if (dico->alt == NULL)
			{
				printf("Je suis else & if avec %c\n", dico->c);
				return NULL;
			}
			else
			{
				printf("Je suis dans else & else avec %c\n", dico->c);
				dico=dico->alt;
			}

		}
		

	}
	return dico;
}

void afficherMotLong(Dico *dico, char val[50], int longueur)
{

	if (dico == NULL)
	{
		printf("Le dictionnaire est vide. \n");
	}
	else
	{
		int i=0;
		char valeur[50]="";

		if (val!=NULL)
		{
			while(val[i]!='\n' && val[i]!='\0')
			{
				valeur[i]=val[i];
				i++;
			}			
			
		}
		else
		{
			i=0;
		}

		
		while (dico->c != '$' )
		{
			if (dico->alt!=NULL)
				afficherMotLong(dico->alt, valeur, longueur);
			valeur[i]=dico->c;
			i++;

			dico=dico->succ;
		}

		if (dico->c == '$' && dico->alt !=NULL)
			afficherMotLong(dico->alt, valeur, longueur);	
	
		if (strlen(valeur)==longueur)
		{
			int j=0;
		

			while (*(valeur+j))
			{
				printf("%c", valeur[j]);
				j++;
			} 
			printf("\n");
		}
	}


}

Suggestion *insererSuggestion (Dico *dico, Suggestion *mot, Suggestion *motprec, char val[50])
{
		int i=0, alt=0, j=0;
		char valeur[50]="";
		Dico *dicoAlt=NULL;

		if (val!=NULL)
		{
			while(val[i]!='\n' && val[i]!='\0')
			{
				valeur[i]=val[i];
				i++;
			}			
			
		}

		//printf("La valeu est %c et la suivante %c\n", dico->c, dico->succ->c);
		valeur[i]=dico->c;
		dico=dico->succ;
		i++;

		while (dico->c!= '$')
		{
			if (dico->alt != NULL)
			{					
				dicoAlt=dico->alt;
				mot = insererSuggestion(dicoAlt, mot, motprec, valeur);
			}
			valeur[i]=dico->c;
			i++;

			dico=dico->succ;
		}

		while (dico->alt !=NULL)
		{
			//printf("depart avec %c\n", dico->c);
			mot=insererSuggestion(dico->alt, mot, motprec, valeur);
			
			dico=dico->alt;
		}
	
		strcpy(mot->chaine, valeur);
		//printf("Insertion 2 de %s\n", mot->chaine);	
		mot->suiv = creerSuggestion();
		motprec=mot;
		mot = mot->suiv;
		mot->prec=motprec;				

		return (mot);

		
}

Suggestion *creerSuggestion()
{
	Suggestion *sgt=malloc(sizeof(Suggestion));
	
	sgt->prec=NULL;
	sgt->suiv=NULL;
	
}

Suggestion *descendre(Dico *dico, Suggestion *mot, Suggestion *motprec, char val[50], Mot *souschaine)
{
	if (dico->alt !=NULL)
	{
		mot = descendre (dico->alt, mot, motprec, val, souschaine);
	}
	if (souschaine->c!=dico->c)
	{
		//printf("On va inserer pour %c car souschaine vaut %c\n", dico->c, souschaine->c);
		mot = insererSuggestion(dico, mot, motprec, val);
	}
	return(mot);
}

Dico *chargerDicoAl(Dico *dico)
{

	FILE* fichier = fopen("dictionnaire.txt", "r");
	
	
	if (fichier!=NULL)
	{
		char chaine[100];
		Mot *mot=malloc(sizeof(Mot)), *tete=NULL;

		int j=0;

		while (fgets(chaine, 100, fichier)!=NULL)
		{	
			Mot *souschaine = NULL, *tete=NULL;
					
			//printf("La chaine est %s\n", chaine);

			int i=0; 
					
			while (chaine[i]!='\0' && chaine[i]!='\n')
			{
				//printf("Caractere %c\n", chaine[i]);

				if(chaine[i]>=65 && chaine[i]<=90)
					chaine[i]=chaine[i]+32;

				if(chaine[i]<97 || chaine[i]>122)
				{
					i++;
				}
				else
				{
					if (i!=0)
					{
						souschaine->suiv = creerMot(chaine[i]);
						souschaine = souschaine->suiv;
					}
					else
					{
						tete = creerMot(chaine[i]);
						souschaine =tete;
					}
					//mot->suiv=NULL;
					i++;
				}
			}
			

			//printf("On va ajouter %s", chaine);
			//printf("le mot a ete cree\n");
			if (j==0)
				dico=initDico2(dico, tete);
			else				
				dico=ajoutMot2(tete, dico);
			//printf("Premier caractere bis %c\n", dico->c);
			souschaine=NULL; tete=NULL;		
			j++;
			
		}
	
		fclose(fichier);
	}
	return(dico);	

}




void dechargerDicoAl(Dico *dico, char val[50], FILE *fichier3)
{

	if (fichier3!=NULL)
	{



		if (dico == NULL)
		{
			printf("Le dictionnaire est vide. \n");
		}
		else
		{
			int i=0;
			char valeur[50]="";

			if (val!=NULL)
			{
				while(val[i]!='\n' && val[i]!='\0')
				{
					valeur[i]=val[i];
					i++;
				}			
			
			}
			else
			{
				i=0;
			}

		
			while (dico->c != '$' )
			{
				if (dico->alt!=NULL)
					dechargerDicoAl(dico->alt, valeur, fichier3);
				valeur[i]=dico->c;
				i++;

				dico=dico->succ;
			}

			if (dico->c == '$' && dico->alt !=NULL)
				dechargerDicoAl(dico->alt, valeur, fichier3);	
	
			int j=0;


			fputs(valeur, fichier3);
			fputc('\n', fichier3);	
		}


	}

}

