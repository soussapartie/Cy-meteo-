#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

typedef struct arbre{
	int elmt;
	int equilibre;
	struct arbre* fg;
	struct arbre* fd;
}Arbre;


int max (int, int);
int min (int, int);
int hauteur (Arbre*);
Arbre* creerArbre (int);
Arbre* insertABR(Arbre*, int);
void traiter (Arbre*, FILE*);
void parcoursPrefixe (Arbre*, FILE*);
void traitter (Arbre*);    
void parcours(Arbre*);
Arbre* suppMinAVL(Arbre*,int*, int*);
Arbre* rotG(Arbre*);
Arbre* rotD(Arbre*);
Arbre* DRG (Arbre*);
Arbre* DRD (Arbre*);
Arbre* equilibrageAVL (Arbre*);
Arbre* insertAVL (Arbre*, int, int*);
Arbre* suppMax(Arbre*, int*);
Arbre* suppABR(Arbre*, int);
void triAVL(FILE*);
void triABR(FILE*);
Arbre* getMin(Arbre*);
Arbre* suppAVL(Arbre*, int, int*);
void triTAB(FILE*);
void  avl_print(Arbre* );
void node_print(Arbre*, int, int);

// listes chainées !!!


int max (int a, int b) {
	return (a<b ? b : a);
}

int min (int a, int b) {
	return (a>b ? b : a);
}

int hauteur (Arbre* a) {
	if (a == NULL) {
		return 0;
	}
	return 1 + max(hauteur(a->fg), hauteur(a->fd));
}

Arbre* creerArbre(int e){

	Arbre* a = malloc(sizeof(Arbre));

	a->elmt = e;
	a->fg = NULL;
	a->fd = NULL;
	a->equilibre = 0;
	return a;
}

Arbre* insertABR(Arbre* a, int e) {
	if(a==NULL)
		return creerArbre(e);
	else if(e< a->elmt)
		a->fg=insertABR(a->fg,e);
	else if(e> a->elmt)
		a->fd=insertABR(a->fd,e);
	return a;
}

void traiter (Arbre* a, FILE* file) {
    int x;
	x = a->elmt;
	printf("%d\n", x);
	fprintf(file, "%d\n", x);
}

void parcoursPrefixe(Arbre* a, FILE* f) {
	if (a != NULL) {
		parcoursPrefixe(a->fg, f);
		traiter(a, f);
		parcoursPrefixe(a->fd, f);
	}
}

void traitter (Arbre* a) {
    int x;
	x = a->elmt;
	printf("%d\n", x);
}

void parcours(Arbre* a) {
	if (a != NULL) {
		parcours(a->fg);
		traitter(a);
		parcours(a->fd);
	}
}

Arbre* suppMinAVL(Arbre* a, int* h, int* pe) {
	Arbre* tmp = NULL;
	if (a->fg == NULL)  {
		*pe= a->elmt;
		*h = -1;
		tmp = a;
		a = a->fd;
		free(tmp);
		return(a);
	}
	else {
		a->fg = suppMinAVL(a->fg, h, pe);
		*h = -*h;
	}
	if (*h != 0) {
		a->equilibre = a->equilibre + *h;
		if (a->equilibre == 0) {
			*h = -1;
		}
		else {
			*h = 0;
		}
	}
	return a;
}

Arbre* rotG(Arbre* a) {

	Arbre* pivot ;
	int eq_a,eq_p;

	pivot = a->fd;
	a->fd = pivot->fg;
	pivot->fg = a;
	eq_a= a->equilibre;
	eq_p= pivot->equilibre;
	a->equilibre = eq_a - max(eq_p, 0) -1;
	pivot->equilibre = min( min (eq_a - 2, eq_a + eq_p - 2) , eq_p - 1);  
	a = pivot;
return a;
}

Arbre* rotD(Arbre* a) {

	Arbre* pivot ;
	int eq_a,eq_p;

	pivot = a->fg;
	a->fg = pivot->fd;
	pivot->fd = a;
	eq_a= a->equilibre;
	eq_p= pivot->equilibre;
	a->equilibre = eq_a - min(eq_p, 0) + 1;
	pivot->equilibre = max(max (eq_a + 2, eq_a + eq_p + 2) , eq_p + 1);
	a = pivot;
return a;
}

Arbre* DRG (Arbre* a) {
	a->fd = rotD(a->fd);
	return rotG(a);
}

Arbre* DRD (Arbre* a) {
	a->fg = rotG(a->fg);
	return rotD(a);
}

Arbre* equilibrageAVL (Arbre* a) {
	if (a->equilibre >= 2) {
		if (a->equilibre >= 0){
			return a = rotG(a);
		}
		else {
			return a= DRG(a);
		}
	}
	else if (a->equilibre <= -2) {
		if (a->equilibre <= 0) {
			return a = rotD(a);
		}
		else {
			return a = DRD(a);
		}
	}
	else {
		return a;
	}
}

/*Arbre* equilibrageAVLBRRR (Arbre* a) {
	if (a->equilibre >= 2) {
		if (a->fd->equilibre >= 0){
			return rotG(a);
		}
		return DRG(a);
	}
	else if (a->equilibre <= -2) {
		if (a->fg->equilibre <= 0) {
			return rotD(a);
		}
		return DRD(a);
	}
	return a;
}
*/ 

Arbre* insertAVL (Arbre* a, int e, int* h) {
	
	if (a == NULL) {
		*h=1;
		return creerArbre(e);
	}
	else if(e < a->elmt) {
		a->fg = insertAVL(a->fg,e,h);
		*h = -*h; 
	}
	else if(e > a->elmt) {
		a->fd = insertAVL(a->fd,e,h); 
	}
    else {
		*h= 0;
		return a;
	}
	if (*h != 0) {
		a->equilibre = a->equilibre + *h;
		// a = equilibrageAVL(a);
		if (a->equilibre == 0) {
			*h = 0;
		}else {
			*h = 1;
		}
	}
	return a;
}

 Arbre* suppMax(Arbre* a, int* pe) {
	Arbre* tmp;
	if (a->fd != NULL) {
		a->fd = suppMax(a->fd, pe);
	}
	else {
		*pe= a->elmt;
		tmp = a;
		a = a->fg;
		free(tmp);
	}
  	return a;
}

Arbre* suppABR(Arbre* a, int e) {
	Arbre* tmp;
	if (a == NULL) {
		return a;
	}
	else if (e > a->elmt) {
		a->fd = suppABR(a->fd, e);
	}
	else if (e < a->elmt) {
		a->fg = suppABR(a->fg, e);
	}
	else if (a->fg == NULL) {
		tmp= a;
		a = a->fd;
		free(tmp);
	}
	else  {
		a->fg= suppMax(a->fg, &a->elmt  ); 
	}
 	return a;
}

void triAVL(FILE* file) {
	Arbre* avla;
	int e;
	int h = hauteur(avla);
	FILE *fichier = NULL;
	fichier = fopen("test.csv", "r"); 
	if (fichier == NULL)
	{
		printf("impossible d'ouvrir test.csv");
		assert(0);
	}
	char *str;
	e = fscanf(fichier, "%s", str);
	while (e != EOF)
	{
		e = fscanf(fichier, "%s", str);
		insertAVL(avla, atoi(str), &h);
	}
	FILE *fichier2 = fopen("resultat.csv", "w+");

	parcoursPrefixe(avla, fichier2);
	// faire fonction qui supp l'avl pour libérer l'espace
}

void triABR(FILE* file) {
	Arbre* abra;
	int e;
	FILE *fichier = NULL;
	fichier = fopen("test.csv", "r"); 
	if (fichier == NULL)
	{
		printf("impossible d'ouvrir test.txt");
		assert(0);
	}
	char *str;
	e = fscanf(fichier, "%s", str);
	while (e != EOF)
	{
		e = fscanf(fichier, "%s", str);
		insertABR(abra, atoi(str));
	}
	FILE *fichier2 = fopen("resultat2.csv", "w+");

	parcoursPrefixe(abra, fichier2);
	// faire fonction qui supp l'abr pour libérer l'espace
}

Arbre* getMin(Arbre* a) {
	while (a->fg != NULL) {
		a = a->fg;
	}
	return a;
}

Arbre* suppAVL(Arbre* a, int e, int* h){
	Arbre* tmp;

	if (a == NULL) {
		*h = 1;
		return a;
	}
	else if (e > a->elmt) {
		a->fd = suppAVL(a->fd, e, h);
	}
	else if (e < a->elmt) {
		a->fg = suppAVL(a->fg, e, h);
		*h = -*h ;
	}
	else if (a->fd != NULL) {
		a->fd = suppMinAVL(a->fd, h, &(a->elmt));
	}
	else {
		tmp = a;
		a = a->fg;
		free(tmp);
		*h = -1;
	}
	if (a == NULL) {
		*h = 0;
	}
	if (*h != 0) {
		a->equilibre = a->equilibre + *h;
		a = equilibrageAVL(a);
		if (a->equilibre == 0) {
			*h = 0;
		}
		else {
			*h = 1;
		}
	}
	return a;
}

void triTAB(FILE* file) {
	int e;
	FILE *fichier = NULL;
	fichier = fopen("test.csv", "r"); 
	if (fichier == NULL)
	{
		printf("impossible d'ouvrir test.txt");
		assert(0);
	}
	char *str;
	e = fscanf(fichier, "%s", str);
	while (e != EOF)
	{
		e = fscanf(fichier, "%s", str);
		// créer une fonction insertTAB
	}
	FILE *fichier2 = fopen("resultat3.csv", "w+");

	// créer une fonction qui parcours le tableau
	// faire fonction qui supp l'abr pour libérer l'espace
}

void  avl_print(Arbre* a){
	printf("Display tree :\n");
	node_print(a, 0, hauteur(a));
	printf("\n\n");
}

void node_print(Arbre *a, int current_level, int max_level) {
	int i;

	if (a) {
		node_print(a->fd, current_level + 1, max_level);
		for (i = 0; i < current_level; i++) {
				printf("    ");
		}
		printf("%d\n", a->elmt);
		node_print(a->fg, current_level + 1, max_level);
	}
	else {
		if (current_level < max_level) {
				node_print(NULL, current_level + 1, max_level);
				for (i = 0; i < current_level; i++) {
					printf("    ");
				}
				printf("..\n");
				node_print(NULL, current_level + 1, max_level);
		}
	}
}



int main () {
	Arbre* avla;
	Arbre* abra;
	FILE* f;
	int h;
	
	avla = creerArbre(0);
	h = hauteur(avla);
	avla = insertAVL(avla,1, &h);
	avla = equilibrageAVL(avla);

	avla = insertAVL(avla,2, &h);
	avla = equilibrageAVL(avla);

	avla = insertAVL(avla,3, &h);
	avla = equilibrageAVL(avla);

	avla = insertAVL(avla,4, &h);
	avla = equilibrageAVL(avla);

	avla = insertAVL(avla,8, &h);
	avla = equilibrageAVL(avla);

	avla = insertAVL(avla,5, &h);
	avla = equilibrageAVL(avla);

	avla = insertAVL(avla,6, &h);
	avla = equilibrageAVL(avla);

	avla = insertAVL(avla,7, &h);
	avla = equilibrageAVL(avla);

	avla = insertAVL(avla,9, &h);
	avla = equilibrageAVL(avla);

	printf("AVL :\n");
	avl_print(avla);
	printf("\n");
	printf("AVL apres equilibrage :\n");
	avl_print(avla);
	printf("\n");

	return 0;
} 

	/* avla = suppAVL(avla, avla->elmt, &h);
		printf("AVL apres suppression :\n");
	node_print(avla, 0, 4);
	avla = suppAVL(avla, avla->elmt, &h);
		printf("AVL apres suppression :\n");
	node_print(avla, 0, 4);
	avla = suppAVL(avla, avla->elmt, &h);
	printf("AVL apres suppression :\n");
	node_print(avla, 0, 4);
	avla = equilibrageAVL(avla);
	printf("apres equilibrage");
	node_print(avla, 0, 4);
	printf("\n\n"); */

	/* printf("\n ABR :\n");
	node_print(abra, 0, 4);
	printf("\n\n"); 
	abra = suppABR(abra,8);
	printf("\n ABR :\n");
	node_print(abra, 0, 4);
	printf("\n\n");  */






	/* 
													ABR ET AVL

	insertABR insertAVL  suppABR suppAVL fonctionnent
	il faut créer une fonction qui supprime tt l'arbre grace à suppABR et suppAVL (pour libérer l'espace) : 
	- crée fonction qui free un avl 
	-crée une fonction qui free un abr

													LISTE CHAINEES
													
	faut créer une fonction qui tri avec les listes chainées (pile ou file et tri rapide) :
	-créer une structure pour liste chainées
	- créer une fonction qui créer une liste chainée
	-fonction qui récupere le fichier et le met dnas la liste chainée (se tri tt seul)
	- fonction qui renvoie tt la liste triée dans un fichier
	- fonction qui supp tt la liste chainée récursivement
	*/






