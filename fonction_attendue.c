#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "prototype.h"
#define TAILLE_MAX 100

Dico *initDico2(Dico *dico, Mot *mot)
{

	int i=0;
	Dico *tete=NULL;

	while (mot!=NULL)
	{
		if (i!=0)
		{
			dico->succ = creerDico();
			dico = dico->succ;

		}
		else
			tete=dico;		
			
		dico->c=mot->c;
	
		mot=mot->suiv;
		i++;
	}
	dico->succ = creerDico();
	dico->succ->c = '$';

	return (tete);
}

Dico *prefixeMot (Dico *dico, Mot *mot)
{
	
	Dico *prefixe=NULL;


	int verif=0;

	if (dico==NULL)
	{
		printf("Le dictionnaire est vide\n");
		return (prefixe);
	}
	if (mot == NULL)
	{
		printf("Le mot est vide \n");
		return (prefixe);
	}

	while (verif ==0)
	{
		if (mot->c==dico->c)
		{
			if (mot->suiv == NULL)
			{
				if (dico->succ->c=='$')
				{
					dico=dico->succ;
					verif=1;
				}
				else
				{
					verif=2;
				}
			}
			else
			{
				if (dico->succ->c=='$')
				{
					prefixe = dico;
				}
			
				mot=mot->suiv;
				dico=dico->succ;
			}
		}
		else if (mot->c < dico->c)
		{
			verif = 2;

		}
		else
		{
			if (dico->alt == NULL)
			{
				verif=2;
			}
			else
			{
				dico=dico->alt;
			}

		}

	}
	
	if (verif==2)
	{
		printf("Ce mot n'existe pas dans le dictionnaire.\n");
		prefixe=NULL;
	}
	


	return (prefixe);


}



int rechercheMot2(Mot *mot, Dico *dico)
{

	int verif=0;

	if (dico==NULL)
	{
		printf("Le dictionnaire est vide\n");
		return 0;
	}
	if (mot == NULL)
	{
		printf("Le mot est vide \n");
		return 0;
	}

	while (verif==0)
	{
		if (mot->c==dico->c)
		{
			if (mot->suiv == NULL)
			{
				if (dico->succ->c=='$')
				{
					verif=1;
				}
				else
				{
					verif=2;
				}
			}
			else
			{
				mot=mot->suiv;
				dico=dico->succ;
			}
		}
		else if (mot->c < dico->c)
		{
			verif = 2;

		}
		else
		{
			if (dico->alt == NULL)
			{
				verif=2;
			}
			else
			{
				dico=dico->alt;
			}

		}

	}
	
	if (verif==1)
	{
		return 1;
	}
	if (verif==2)
	{
		return 0;
	}
	
}

Dico *ajoutMot2(Mot *mot, Dico *dico)
{

	int verif=0;

	if (dico==NULL)
	{
		printf("Le dictionnaire est vide\n");
		return dico;
	}
	if (mot == NULL)
	{
		printf("Le mot est vide \n");
		return dico;
	}

	Dico *dicoAjout=dico;
	Dico *dicoprec = NULL;
	int i=0;

	while (mot!=NULL)
	{

		if (mot->c==dico->c)
		{

			if (mot->suiv == NULL)
			{
				if (dico->succ == NULL)
				{
					dico->succ=creerDico();
					dico=dico->succ;
					dico->c='$';
					printf("Le mot a bien ete ajoute\n");
					return dicoAjout;
				}
				else
				{
					if (dico->succ->c=='$')
					{
						printf("Le mot existe deja\n");
						return dicoAjout;
					}
					else
					{
						Dico *dico2 = creerDico();
						dico2->alt = dico->succ->succ;
						dico2->succ = NULL;
						dico2->c = '$';
					
						dico->succ=dico2;
						printf("Le mot a bien ete ajoute");
						return dicoAjout;
					}
				}
			}
			else if (dico->succ==NULL)
			{
				dico->succ=creerDico();
				dico->succ->c = mot->suiv->c;

				mot=mot->suiv;
				dicoprec=dico;
				dico=dico->succ;
			} 
			else if (dico->succ->c == '$')
			{
				if (dico->succ->alt != NULL)
				{
					dicoprec=dico->succ;
					dico=dico->succ->alt;
					mot=mot->suiv;
				}
				else
				{
					dico->succ->alt=creerDico();
					dico->succ->alt->c=mot->suiv->c;
					dicoprec=dico;
					dico=dico->succ->alt;

					mot=mot->suiv;

				}
			}
			else
			{
				mot=mot->suiv;
				dicoprec=dico;
				dico=dico->succ;
			}
		}
		else if (mot->c < dico->c)
		{
			Dico *dico2=creerDico();
			if (dicoprec!=NULL)
			{
				if (dicoprec->succ!=NULL)
				{
					if (dicoprec->succ == dico)
						dicoprec->succ=dico2;
				}
				if (dicoprec->alt!=NULL)
				{
					if (dicoprec->alt == dico)
						dicoprec->alt = dico2;
				}			
			}			
			dico2->c=mot->c;
			dico2->alt = dico;
			dico=dico2;
	
			if (i==0)
				dicoAjout = dico2;

		}
		else
		{
			if (dico->alt == NULL)
			{
				dico->alt = creerDico();
				dico->alt->c = mot->c;
				dicoprec=dico;
				dico=dico->alt;
			}
			else
			{
				dicoprec=dico;
				dico=dico->alt;
			}

		}

		i++;
	}


}

Dico *supprimeMot2(Mot *mot, Dico *dico)
{
	
	Dico *prefixe=NULL;
	Mot *val=NULL;


	int verif=0;

	if (dico==NULL)
	{
		printf("Le dictionnaire est vide\n");
		return NULL;
	}

	Dico *dicoDebut = dico;

	if (mot == NULL)
	{
		printf("Le mot est vide \n");
		return (dicoDebut);
	}


	while (verif ==0)
	{
		if (mot->c==dico->c)
		{
			if (mot->suiv == NULL)
			{
				if (dico->succ->c=='$')
				{
					if (dico->succ->alt !=NULL)
						verif=3;
					else
						verif=1;
				}
				else
				{
					verif=2;
				}
			}
			else
			{
				if (dico->succ->c=='$')
				{
					val=mot->suiv;
					prefixe = dico;
				}
			
				mot=mot->suiv;
				dico=dico->succ;
			}
		}
		else if (mot->c < dico->c)
		{
			verif = 2;

		}
		else
		{
			if (dico->alt == NULL)
			{
				verif=2;
			}
			else
			{
				dico=dico->alt;
			}

		}

	}
	
	if (verif==1)
	{

		Dico *dicoprec = NULL;
		dico=prefixe->succ;

		
		while(dico->c != val->c)
		{
			dicoprec=dico;
			dico=dico->alt;
		}

		if (dico->alt != NULL)
			dicoprec->alt=dico->alt;
		else
			dicoprec->alt=NULL;

		dicoprec=dico;
		dico=dico->succ;
		dicoprec->succ = NULL;
		while(dico!=NULL)
		{
			dicoprec=dico;
			dico=dico->succ;
			free(dicoprec);
		}
		
	}
	if (verif==2)
	{
		printf("Ce mot n'existe pas dans le dictionnaire");
	}

	if (verif==3)
	{
		Dico *dicoprec = NULL;

		dicoprec=dico;
		dico=dico->succ;
		dicoprec->succ=dico->alt;
		free(dico);

	}
	


	return (dicoDebut);


}


Suggestion *suggestionMots2 (Dico *dico, Mot *souschaine)
{
	
	if (souschaine == NULL)
	{
		printf("La souschaine est vide\n");
		return NULL;
	}
	if (dico == NULL)
	{
		printf("Le tableau est vide\n");
		return NULL;
	}

	Dico *prefixe=NULL, *suivant=NULL;
	
	Suggestion *mot = creerSuggestion();
	Suggestion *motprec = NULL;
	
	char valeur[50]="";
	int verif = 0, i=0, compteur=0;

	while(verif==0)
	{
		//printf("En haut, souschaine vaut %c et dico vaut %c\n", souschaine->c, dico->c);
		if (dico->c==souschaine->c)
		{
			valeur[i]=souschaine->c;
			i++;

			if (souschaine->suiv == NULL)
			{
				verif=1;
			}
			else
			{
				if (dico->succ->c=='$')
				{
					dico=dico->succ;
					prefixe = dico;
					
					if (dico->alt!=NULL)
					{
						mot = descendre(dico->alt, mot, motprec, valeur, souschaine->suiv);
						dico=prefixe;
						while (dico!=NULL)
						{
							if(dico->c==souschaine->suiv->c)
								suivant=dico;
							dico=dico->alt;
						}

						if (suivant != NULL)	
						{
							souschaine=souschaine->suiv;
							dico=suivant;
						}
						else
							verif =1;
					}
					else
						verif=1;

					strcpy(mot->chaine, valeur);
					//printf("Insertion 1 de %s\n", mot->chaine);
					mot->suiv = creerSuggestion();
					motprec=mot;
					mot = mot->suiv;
					mot->prec=motprec;
					
				}
				else
				{				
					souschaine=souschaine->suiv;
					dico=dico->succ;
				}
			}
		}
		else if (souschaine->c < dico->c)
		{
			//le tableau est terminé !
			verif = 1;

		}
		else
		{
				//printf("Ici souschaine vaut %c et mot %c\n", souschaine->c, dico->c);

			prefixe = dico;
		
				//printf("Nous descendons dans %c\n", dico->c);
				mot = descendre(dico, mot, motprec, valeur, souschaine);
				dico=prefixe;
				while (dico!=NULL)
				{
					if(dico->c==souschaine->c)
						suivant=dico;
					dico=dico->alt;
				}
		
		
			if (suivant != NULL)	
			{
				dico=suivant;
			}
			else
				verif =1;			
	

		}
	
	}

	return (mot);
	

}

Dico *verimot (Dico *dico)
{
	FILE* fichier = fopen("file.txt", "r");
	FILE* fichier2=fopen("test2.txt", "w+");
	Dico *depart =  dico;
	
	if (fichier!=NULL && fichier2!=NULL)
	{
		char chaine[TAILLE_MAX];
		Mot *mot=malloc(sizeof(Mot)), *tete=NULL;
		int j=0;	

		while (fgets(chaine, TAILLE_MAX, fichier)!=NULL)
		{
			printf("C'est %s", chaine);
			printf("\n\n");
			int a = affichage_verimo();
			int i=0;
			switch (a)
			{
				
				case 1:
				{
					int compteur=0, select=0;
					i=0;
					Mot *souschaine = NULL, *tete=NULL;
					
					printf("La chaine est %s\n", chaine);
					
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
								souschaine->suiv = creerMot(chaine[i]);
								souschaine = souschaine->suiv;
							}
							else
							{
								tete = creerMot(chaine[i]);
								souschaine =tete;
							}
							mot->suiv=NULL;
							i++;
						}
					}
					
	
					Suggestion *mot = malloc(sizeof(Suggestion)), *debut[5];
					mot =suggestionMots2 (dico, tete);
					if (mot!=NULL)
						mot=mot->prec;
			
					for (j=5; j>0; j--)
					{
						if (mot!=NULL)
						{
					
							printf("Suggestion %d | %s\n", 5-j+1, mot->chaine);
							debut[compteur]=mot;
							mot=mot->prec;
							compteur++;
						}
						else 
						{
							printf("Il n'y a plus d'autres suggestions disponbiles \n");
							break;
						}
					}

					if (compteur==0)
						break;
					printf("Par quel mot voulez-vous le remplacer?\n");
					while (select<1 || select>compteur)
					{
						scanf("%d", &select);
						viderBuffer();
					}
					mot=debut[select-1];
					char chaine2[50];
					strcpy(chaine2, mot->chaine);
		
					fputs(chaine2, fichier2);
					fputc('\n', fichier2);
		
				}break;
	
				case 2:
				{
					fputs (chaine, fichier2);
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
					dico = ajoutMot2(tete, dico);
					i=0;
					mot = NULL; tete=NULL;
				}break;

				case 3:
				{
					fputs(chaine, fichier2);
					clean();
					continue;
				}
			}
		}
		remove("file.txt");
		rename("test2.txt", "file.txt");
	
		fclose(fichier);
		fclose(fichier2);
	}
	return(depart);	


}

Dico *veridico(Dico *dico)
{
	Dico *depart =dico;

	Mot *souschaine=NULL;
	souschaine=init_mot();
	int j, compteur=0;

	Suggestion *mot = malloc(sizeof(Suggestion)), *debut[5];
	mot =suggestionMots2 (dico, souschaine);
	if (mot!=NULL)
		mot=mot->prec;

	for (j=5; j>0; j--)
	{
		if (mot!=NULL)
		{
	
			printf("Suggestion %d | %s\n", 5-j+1, mot->chaine);
			debut[compteur]=mot;
			mot=mot->prec;
			compteur++;
		}
		else 
		{
			printf("Il n'y a plus d'autres suggestions disponbiles \n");
			break;
		}
	}	

	int i;
	for (i=0; i<compteur; i++)
	{
		char chaine[50];
		mot=debut[i];
		strcpy(chaine, mot->chaine);
		Mot *souschaine=NULL, *tete=NULL;
		int k=0;
		
		printf("Le mot est %s\n", chaine);

		while (chaine[k]!='\0' && chaine[k]!='\n')
		{

			if(chaine[k]>=65 && chaine[k]<=90)
				chaine[k]=chaine[k]+32;

			if(chaine[k]<97 || chaine[k]>122)
			{
				k++;
			}
			else
			{
				if (k!=0)
				{
					souschaine->suiv = creerMot(chaine[k]);
					souschaine = souschaine->suiv;
				}
				else
				{
					tete = creerMot(chaine[k]);
					souschaine =tete;
				}
				mot->suiv=NULL;
				k++;
			}
		}
		
		
		int a=affichage_veridico();

		switch (a)
		{
			case 1:
			{
				Mot *mot2=NULL;
				mot2 = init_mot();
				dico = supprimeMot2(tete, dico);
				dico = ajoutMot2(mot2, dico);
				printf("La correction a bien ete effectuee\n");
			}break;			
			case 2:
			{
				dico = supprimeMot2(tete, dico);
			}break;
			case 3:
			{
				printf("Le mot est conserve\n");
			}break;
		}
		printf("\n\n");
	}
		

	return(depart);
}

