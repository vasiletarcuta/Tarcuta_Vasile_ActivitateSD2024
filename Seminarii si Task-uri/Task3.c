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

float distantaMinNecesaraTV(int diagonalaTV) {
    //pt fiecare inch din diagonala, este necesar sa se stea la 4.2cm distanta
    return diagonalaTV * 4.2;
}

struct Televizor modificaPret(struct Televizor tv, float nouPret) {
    tv.pret = nouPret;
    return tv;
}

void afisareVector(struct Televizor* tv, int nrTV) {
    for (int i = 0; i < nrTV; i++) {
        afiseaza(tv[i]);
    }
}

void dezalocareVectorTV(struct Televizor** tv, int* nrTV) {
    for (int i = 0; i < *nrTV; i++)
        free((*tv)[i].marca);

    free(*tv);
    *nrTV = 0;
    *tv = NULL;
}

struct Televizor* copiazaTVMare(struct Televizor* tv, int nrTV, float diagonalaMin, int* nrTVMari) {
    *nrTVMari = 0;
    for (int i = 0; i < nrTV; i++) {
        if (tv[i].diagonala > diagonalaMin) {
            (*nrTVMari)++;
        }
    }

    int k = 0;
    struct Televizor* vector = (struct Televizor*)malloc(sizeof(struct Televizor) * (*nrTVMari));
    for (int i = 0; i < nrTV; i++) {
        if (tv[i].diagonala > diagonalaMin) {
            vector[k++] = intializareTV(tv[i].cod, tv[i].marca, tv[i].diagonala, tv[i].rezolutie, tv[i].pret);
        }
    }

    return vector;
}

struct Televizor* copiazaTVMic(struct Televizor* tv, int nrTV, float diagonalaMax, int* nrTVMic) {
    *nrTVMic = 0;
    for (int i = 0; i < nrTV; i++) {
        if (tv[i].diagonala < diagonalaMax) {
            (*nrTVMic)++;
        }
    }

    int k = 0;
    struct Televizor* vector = (struct Televizor*)malloc(sizeof(struct Televizor) * (*nrTVMic));
    for (int i = 0; i < nrTV; i++) {
        if (tv[i].diagonala < diagonalaMax) {
            vector[k++] = intializareTV(tv[i].cod, tv[i].marca, tv[i].diagonala, tv[i].rezolutie, tv[i].pret);
        }
    }

    return vector;
}

struct Televizor* concateneazaVectori(struct Televizor* vt1, struct Televizor* vt2, int nrTV1, int nrTV2) {
    struct Televizor* VectorConcatenat = (struct Televizor*)malloc(sizeof(struct Televizor) * (nrTV1 + nrTV2));
    if (VectorConcatenat == NULL) {
        return NULL;
    }
    for (int i = 0; i < nrTV1; i++) {
        VectorConcatenat[i] = vt1[i];
    }

    for (int i = 0; i < nrTV2; i++) {
        VectorConcatenat[nrTV1 + i] = vt2[i];
    }

    return VectorConcatenat;
}

void TVInFisierTxt(struct Televizor tv) {
    FILE* g = fopen("televizorInTxt.txt", "w");
    if (g == NULL)
    {
        printf("Fisierul text nu s-a putut crea!");
        return;
    }
    fprintf(g, "%d %s %f %d %d %f", tv.cod, tv.marca, tv.diagonala, tv.rezolutie[0], tv.rezolutie[1], tv.pret);
    fclose(g);
}

void vectorTVInFisierTxt(struct Televizor* tv, int nrElemente) {
    FILE* g = fopen("vectorTVInTxt.txt", "w");
    if (g == NULL) {
        printf("Fisierul text nu s-a putut crea!");
        return;
    }

    fprintf(g, "%d\n", nrElemente); 
    for (int i = 0; i < nrElemente; i++) {
        fprintf(g, "%d %s %.2f %d %d %.2f\n", tv[i].cod, tv[i].marca, tv[i].diagonala,
            tv[i].rezolutie[0], tv[i].rezolutie[1], tv[i].pret);
    }

    fclose(g);
}

//struct Televizor* citesteVectorTVDinFisierText(const char* numeFisier, int* numarElemente) {
//    FILE* fisier = fopen(numeFisier, "r");
//    if (fisier == NULL) {
//        printf("Eroare la deschiderea fisierului pentru citire.\n");
//        return NULL;
//    }
//    fscanf(fisier, "%d", numarElemente);
//    struct Televizor* vector = (struct Televizor*)malloc(*numarElemente * sizeof(struct Televizor));
//    if (vector == NULL) {
//        printf("Eroare la alocarea memoriei pentru vector.\n");
//        fclose(fisier);
//        return NULL;
//    }
//    for (int i = 0; i < *numarElemente; i++) {
//        fscanf(fisier, "%d %ms %f %d %d %f",
//            &vector[i].cod, &vector[i].marca, &vector[i].diagonala,
//            &vector[i].rezolutie[0], &vector[i].rezolutie[1], &vector[i].pret);
//    }
//    fclose(fisier);
//    return vector;
//}

int main() {
    int nrTelevizoare = 5;
    int rezolutie[] = { 45, 75 };
    int rezolutie1[] = { 97, 56 };
    struct Televizor televizorV = intializareTV(23, "Samsung", calculDiagonalaTVInch(rezolutie[0], rezolutie[1]), rezolutie, 2500);
    //struct Televizor televizorV1 = intializareTV(13, "Apple TV", calculDiagonalaTVInch(rezolutie1[0], rezolutie1[1]), rezolutie1, 5300);
    struct Televizor* VectorTV = (struct Televizor*)malloc(sizeof(struct Televizor) * nrTelevizoare);
    for (int i = 0;i < nrTelevizoare;i++) {
        if (i % 2 == 0) {
            VectorTV[i] = intializareTV(i + 1, "AppleTV", calculDiagonalaTVInch(rezolutie[0], rezolutie[1]), rezolutie, i * 100 + 1000 * (i + 1));
        }
        else
            VectorTV[i] = intializareTV(i + 10, "Samsung", calculDiagonalaTVInch(rezolutie1[0], rezolutie1[1]), rezolutie1, (i + 2) * 100 + 1000 * (i + 1));

    }
    afisareVector(VectorTV, nrTelevizoare);
    vectorTVInFisierTxt(VectorTV, nrTelevizoare);
    printf("\n\n");
    int nrTelevizoareMari = 0;
    int nrTelevizoareMici = 0;

    struct Televizor* vectorTVMare = copiazaTVMare(VectorTV, nrTelevizoare, 40, &nrTelevizoareMari);
    struct Televizor* vectorTVMic = copiazaTVMic(VectorTV, nrTelevizoare, 40, &nrTelevizoareMici);

    //afisare in txt a unui obiect
    TVInFisierTxt(televizorV);

    printf("\n\n");
    afisareVector(vectorTVMare, nrTelevizoareMari);
    printf("\n\n");
    afisareVector(vectorTVMic, nrTelevizoareMici);

    struct Televizor* vectorConcatenatTVMicMare = concateneazaVectori(vectorTVMare, vectorTVMic, nrTelevizoareMari, nrTelevizoareMici);
    printf("\n\n");
    afisareVector(vectorConcatenatTVMicMare, nrTelevizoareMari + nrTelevizoareMici);

    //struct Televizor* vectorTelevizoare = citesteVectorTVDinFisierText("vectorTVInTxt.txt", &nrTelevizoare);
    //afisareVector(vectorTelevizoare, nrTelevizoare);

    eliberareMem(televizorV);
    dezalocareVectorTV(&vectorTVMare, &nrTelevizoareMari);
    dezalocareVectorTV(&vectorTVMic, &nrTelevizoareMici);
    dezalocareVectorTV(&VectorTV, &nrTelevizoare);
    //dezalocareVectorTV(&vectorTelevizoare, &nrTelevizoare);
    return 0;
}