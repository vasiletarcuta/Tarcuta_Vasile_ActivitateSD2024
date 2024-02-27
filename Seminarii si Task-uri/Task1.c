#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>

struct Televizor {
    int cod;
    char* marca;
    float diagonala;
    int rezolutie[2]; // rezolutie[0] - latime, rezolutie[1] - inaltime
    float pret;
};

struct Televizor citesteTV() {
    struct Televizor tv;
    tv.marca = NULL;

    printf("\nIntroduceti codul televizorului: ");
    scanf("%d", &tv.cod);

    char buffer[100];
    printf("\nIntroduceti marca televizorului: ");
    scanf("%s", buffer);

    tv.marca = malloc(strlen(buffer) + 1);
    if (tv.marca != NULL) {
        strcpy(tv.marca, buffer);
    }

    //printf("\nIntroduceti diagonala televizorului: ");
    //scanf("%f", &tv.diagonala);

    printf("\nIntroduceti rezolutia:");
    printf("\n Latime: ");
    scanf("%d", &tv.rezolutie[0]);
    printf("\n Inaltime: ");
    scanf("%d", &tv.rezolutie[1]);

    printf("\nIntroduceti pretul:");
    scanf("%f", &tv.pret);

    return tv;
}


float calculDiagonalaTVInch(int lungime, int latime) {
    return sqrt(lungime * lungime + latime * latime) * 0.393700787;
}


struct Televizor intializareTV(int cod, const char* marca, float diagonala, int rezolutie[2], float pret) {
    struct Televizor tv;

    tv.cod = cod;
    tv.marca = malloc(strlen(marca) + 1);
    if (tv.marca != NULL) {
        strcpy(tv.marca, marca);
    }
    tv.diagonala = calculDiagonalaTVInch(rezolutie[0], rezolutie[1]);
    tv.rezolutie[0] = rezolutie[0];
    tv.rezolutie[1] = rezolutie[1];
    tv.pret = pret;

    return tv;
}

void afiseaza(struct Televizor televizor) {
    printf("Cod: %d\n", televizor.cod);
    if (televizor.marca != NULL)
        printf("Marca: %s\n", televizor.marca);
    else
        printf("Marca: -");
    printf("Diagonala: %.2f inch\n", televizor.diagonala);
    printf("Rezolutie: %d x %d\n", televizor.rezolutie[0], televizor.rezolutie[1]);
    printf("Pret: %.2f lei\n", televizor.pret);
    printf("\n");
}

void eliberareMem(struct Televizor televizor) {
    free(televizor.marca);
    televizor.marca = NULL;
}

float distantaNecesaraTV(int diagonalaTV) {
    //pt fiecare inch din diagonala, este necesar sa se stea la 4.2cm distanta
    return diagonalaTV * 4.2;
}

struct Televizor modificaPret(struct Televizor tv, float nouPret) {
    tv.pret = nouPret;
    return tv;
}

int main() {
    int rezolutie[] = { 45, 75 };
    int rezolutie1[] = { 97, 56 };
    struct Televizor televizorV = intializareTV(23, "Samsung", calculDiagonalaTVInch(rezolutie[0], rezolutie[1]), rezolutie, 2500);
    struct Televizor televizorV1 = intializareTV(13, "Apple TV", calculDiagonalaTVInch(rezolutie1[0], rezolutie1[1]), rezolutie1, 3300);
   // struct Televizor televizorV2 = citesteTV();
    afiseaza(televizorV);
    afiseaza(televizorV1);
   // afiseaza(televizorV2);
    printf("\n\n");
    printf("\nPt televizorul cu id %d, este necesara o distanta de %5.2f cm.", televizorV.cod, distantaNecesaraTV(televizorV.diagonala));
    printf("\nPt televizorul cu id %d, este necesara o distanta de %5.2f cm.", televizorV1.cod, distantaNecesaraTV(televizorV1.diagonala));
    printf("\n\n");
    televizorV = modificaPret(televizorV, 1234);
    afiseaza(televizorV);
    eliberareMem(televizorV);
    eliberareMem(televizorV1);
   // eliberareMem(televizorV2);
   

    return 0;
}