#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct Galerie Galerie;
struct Galerie {
	int cod; 
	const char* nume;
	float pretIntrare;
};

typedef struct nod nod;
struct nod {
	Galerie info;
	nod* next;
};

typedef struct hashtable HashTable;
struct hashtable{
	nod** vector;
	int dim;
};

HashTable initializareHashTable(int dimensiune) {
	HashTable hash;
	hash.dim = dimensiune;
	hash.vector = (nod**)malloc(sizeof(nod*)*dimensiune);
	for (int i = 0;i < dimensiune;i++) {
		hash.vector[i] = NULL;
	}
	return hash;
}

Galerie initGalerie(int cod, const char* nume, float pret) {
	Galerie g;
	g.cod = cod;
	g.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(g.nume, nume);
	g.pretIntrare = pret;
	return g;
}

int calculHash(int cod, const char* nume, int dimensiune) {
	//de obicei se calculeaza dupa cum vrem noi, atat timp cat se asigura unicitatea
	if (dimensiune > 0)
	{
		int rez = cod * strlen(nume);
		return rez % dimensiune;
	}
	return -1;
}

void inserareLaFinal(nod** cap, Galerie galerie) {
	nod* temp = (nod*)malloc(sizeof(nod));
	temp->info = galerie;
	temp->next = NULL;
	if (*cap) {
		nod* aux = *cap;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = temp;
	}
	else {
		*cap = temp;
	}
	
}

void inserareGalerieInTabela(HashTable hash, Galerie galerie) {
	if (hash.dim > 0) {
		int pozitie = calculHash(galerie.cod, galerie.nume, hash.dim);
		if (hash.vector[pozitie] != NULL) {
			inserareLaFinal(&(hash.vector[pozitie]), galerie);
		}
		else {
			//acelasi lucru ca mai sus
			inserareLaFinal(&(hash.vector[pozitie]), galerie);
		}
	}
}

void afisareGalerie(Galerie g) {
	printf("%d. Intrarea la galeria %s costa %.2f\n", g.cod, g.nume, g.pretIntrare);
}
		

void afisareListaGalerii (nod* cap) {
	while (cap) {
		afisareGalerie(cap->info);
		cap = cap->next;
	}
}

void afisareTabela(HashTable tabela) {
	for (int i = 0;i < tabela.dim;i++) {
		if (tabela.vector[i] != NULL) {
			printf("Clusterul %d:\n\n",i+1);
			afisareListaGalerii(tabela.vector[i]);
		}
	}
}

Galerie cautaGalerieDupaCheie(int cod, const char* nume, HashTable tabela) {
	int pozitie = calculHash(cod, nume, tabela.dim);//am determinat pozitia
	if (pozitie >= 0 && pozitie < tabela.dim) {
		nod* p = tabela.vector[pozitie];
		while (p && p->info.cod != cod && strcmp(p->info.nume, nume) != 0) {
			p = p->next;
		}
		if (p) {
			return p->info;//shallow copy
		}
		else {
			return initGalerie(-1, "", 0);
		}
	}
	else {
		return initGalerie(-1, "", 0);
	}
}

int main() {

	Galerie g1 = initGalerie(1, "Orizont", 10);
	Galerie g2 = initGalerie(2, "Carcul Armatei", 6);
	Galerie g3 = initGalerie(3, "Louvre", 30);
	Galerie g4 = initGalerie(4, "Antipa", 30);
	Galerie g5 = initGalerie(5, "Istorie", 30);
	
	HashTable tabela = initializareHashTable(5);
	
	inserareGalerieInTabela(tabela, g1);
	inserareGalerieInTabela(tabela, g2);
	inserareGalerieInTabela(tabela, g3);
	inserareGalerieInTabela(tabela, g4);
	inserareGalerieInTabela(tabela, g5);

	afisareTabela(tabela);

	Galerie g = cautaGalerieDupaCheie(4, "Antipa", tabela);
	printf("\n=====================\nCautare:\n\n");
	afisareGalerie(g);
	return 0;
}