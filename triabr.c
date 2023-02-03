#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

typedef struct arbre{
	int id;
	int elmt;
	float alt;
	struct arbre* fg;
	struct arbre* fd;
}Arbre;

typedef struct excel {
    int id;
    int date; //pas comme ca
    int Mpress;
    int Dwind;
    int Vwind;
    int humidité;
    int Spress;
    int Vpress;
    int prec;
    int coord; // pas comme ca
    int T;
    int Tmin;
    int Tmax;
    int alt;
    int cp;
} Excel;

int max (int, int);
int min (int, int);
int hauteur (Arbre*);
Arbre* creerArbre (int, float);
Arbre* insertABR(Arbre*, int);
void traiter (Arbre*, FILE*);
void parcoursPrefixe (Arbre*, FILE*);
Arbre* suppMax(Arbre*, int*);
Arbre* suppELMT(Arbre*, int);
void suppArbre(Arbre*);
void deleteArbre (Arbre**);
void triABR(FILE*);
void  avl_print(Arbre* );
void node_print(Arbre*, int, int);


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

Arbre* creerArbre(int id, float alt){

	Arbre* a = malloc(sizeof(Arbre));

	a->id = id;
	a->fg = NULL;
	a->fd = NULL;
	a->alt = alt;
	return a;
}

Arbre* insertABRh1(Arbre* a, int id, float alt) {

	if(a == NULL)
		return creerArbre(id, alt);
	else if(alt < a->alt)
		a->fg=insertABRh1(a->fg,id, alt);
	else if(alt > a->alt)
		a->fd=insertABRh1(a->fd,id, alt);
	return a;
}

Arbre* creationarbreh1(Arbre* a) {
    FILE *fp = fopen("tempo3.txt", "r");
    if (fp == NULL) {
        printf("erreur     fopen ");
        exit(2);
    }
    char buffer[2048];
    int ID;
    float alt;
    while (fgets(buffer, 2048, fp) != NULL) {                            
        int ret = sscanf(buffer, "%d %f", &ID, &alt);
        if (ret != 2) {
            printf("erreur lors de la lecture des champs");
            exit(4);
        }
        a = insertABRh1(a, ID, alt);
    }
    fclose(fp);
    return a;
}



 Arbre* insertABR(Arbre* a, int e) {
	float i; // a supp ca apres
	if(a == NULL)
		return creerArbre(e, i);
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

Arbre* suppELMT(Arbre* a, int e) {
	Arbre* tmp;
	if (a == NULL) {
		return a;
	}
	else if (e > a->elmt) {
		a->fd = suppELMT(a->fd, e);
	}
	else if (e < a->elmt) {
		a->fg = suppELMT(a->fg, e);
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

void suppArbre(Arbre* a) {
	if (a != NULL) {
		suppArbre(a->fg);
		suppArbre(a->fd);
		free(a);
	}
}

void deleteArbre (Arbre** a) {
	suppArbre(*a);
	*a = NULL;
}

void triABR(FILE* file) {
	Arbre* a;
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
		insertABR(a, atoi(str));
	}
	FILE *fichier2 = fopen("resultat2.csv", "w+");

	parcoursPrefixe(a, fichier2);
	deleteArbre(&a);
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
		printf("%d %f\n", a->elmt, a->alt);
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
    Arbre* a;
	// a = creationarbreh1(a);
    printf("ABR :\n");
	avl_print(a);
	printf("\n");
	// deleteArbre(&a);

    return 0;
    } 















	/* 
	void traitter (Arbre*);    
	void parcours(Arbre*);
	
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
} */
