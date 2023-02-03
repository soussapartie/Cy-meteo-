#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

typedef struct chainon {
    int elmt;
    struct chainon* next;
}Chainon;

void insert(Chainon** liste, int e) {
    Chainon* new_chainon = (Chainon*) malloc(sizeof(struct chainon));
    new_chainon->elmt  = e;
    new_chainon->next = (*liste);
    (*liste) = new_chainon;
}

Chainon* split(Chainon* liste) {
    Chainon* fast = liste;
    Chainon* slow = liste;
    while (fast->next && fast->next->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    Chainon* tmp = slow->next;
    slow->next = NULL;
    return tmp;
}

Chainon* fusion(Chainon* liste1, Chainon* liste2) {
    if (!liste1) {
        return liste2;
    }
    if (!liste2) {
        return liste1;
    }
    if (liste1->elmt < liste2->elmt) {
        liste1->next = fusion (liste1->next, liste2);
        return liste1;
    }
    else {
        liste2->next = fusion(liste1, liste2->next);
        return liste2;
    }
}

void triFusion(Chainon** tete) {
    Chainon* current = *tete;
    if ((current == NULL) || (current->next == NULL)) {
        return; 
    }
    Chainon* liste2 = split(current);
    triFusion(&current);
    triFusion(&liste2);
    *tete = fusion(current, liste2);
}

void printListe(Chainon* chainon, FILE* file) {
    int x;
    while (chainon != NULL) {
        x = chainon->elmt;
        printf("%d ", chainon->elmt);
        fprintf(file, "%d\n", x);
        chainon = chainon->next;
    }
}

void print(Chainon* chainon) {
    if (chainon == NULL) {
        printf("liste nulle");
    }
    while (chainon != NULL) {
        printf("%d ", chainon->elmt);
        chainon = chainon->next;
    }
}


void suppListe(Chainon** tete) {
   Chainon* current = *tete;
   Chainon* next;
 
   while (current != NULL) {
       next = current->next;
       free(current);
       current = next;
   }
   *tete = NULL;
}

void triTAB(FILE* file) {
    Chainon* liste;
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
		insert(&liste, atoi(str));
        triFusion(&liste);
	}
	FILE *fichier2 = fopen("resultat3.csv", "w+");
    printListe(liste, file);
    suppListe(&liste);
}

int main(){
    Chainon* a = NULL;
    insert(&a, 15);
    insert(&a, 10);
    insert(&a, 5);
    insert(&a, 20);
    insert(&a, 3);
    insert(&a, 2);
    triFusion(&a);
    print(a);
    suppListe(&a);
    print(a);
return 0;
}

    