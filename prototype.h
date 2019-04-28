typedef struct Suggestion Suggestion;

struct Suggestion{
	char chaine[26];
	Suggestion *suiv;
	Suggestion *prec;
};

typedef struct Car Mot;

struct Car{
	char c;
	Mot *suiv;
};

typedef struct Cellule Dico;

struct Cellule{
	char c;
	Dico *succ;
	Dico *alt;
};

Dico *initDico2(Dico *dico, Mot *mot);

Mot *init_mot();

Dico *prefixeMot (Dico *dico, Mot *mot);

void afficherMot(Dico *dico, char val[50]);

void afficherMotLong(Dico *dico, char val[50], int longueur);

Suggestion *suggestionMots2 (Dico *dico, Mot *souschaine);

Suggestion *insererSuggestion (Dico *dico, Suggestion *mot, Suggestion *motprec, char val[50]);

int affichage_menu();

int affichage_print();

void viderBuffer();

Mot *creerMot(char val);

void clean();

Dico *creerDico();

int rechercheMot2(Mot *mot, Dico *dico);

Dico *ajoutMot2(Mot *mot, Dico *dico);

Dico *supprimeMot2(Mot *mot, Dico *dico);

Dico *ajusterDico(Dico *dico, char *chaine);

Dico *verimot(Dico *dico);

int affichage_verimo();

Suggestion *creerSuggestion();

Suggestion *descendre(Dico *dico, Suggestion *mot, Suggestion *motprec, char val[50], Mot *souschaine);

int affichage_veridico();

Dico *veridico(Dico *dico);

Dico *chargerDicoAl(Dico *dico);

void dechargerDicoAl(Dico *dico, char val[50], FILE *fichier3);
