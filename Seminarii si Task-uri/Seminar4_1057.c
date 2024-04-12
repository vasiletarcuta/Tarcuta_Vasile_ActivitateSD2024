//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<malloc.h>
//#include<string.h>
//#include<stdlib.h>
//
//
//struct Masina {
//    int id;
//    char* producator;
//    int nrUsi;
//    float pret;
//};
//
//
//struct Masina* adaugareInVector(struct Masina* masini, struct Masina m, int* nrMasini) {
//    struct Masina* aux = (struct Masina*)malloc(sizeof(struct Masina) * ((*nrMasini) + 1));
//    for (int i = 0; i < *nrMasini; i++) {
//        aux[i] = masini[i];
//    }
//    aux[*nrMasini] = m;
//    (*nrMasini)++;
//    if (masini != NULL) {
//        free(masini);
//    }
//    return aux;
//}
//
//struct Masina* citireFisier(const char* numeFisier, int* nrMasini) {
//
//    FILE* file = fopen(numeFisier, "r");
//    char buffer[100];
//    char delimitare[] = ",\n";
//    struct Masina* masini = NULL;
//    (*nrMasini) = 0;
//    while (fgets(buffer, 100, file) != NULL) {
//        char* element = strtok(buffer, delimitare);
//        struct Masina m;
//        m.id = atoi(element);
//        element = strtok(NULL, delimitare);
//        m.producator = (char*)malloc(strlen(element) + 1);
//        strcpy(m.producator, element);
//        element = strtok(NULL, delimitare);
//        m.nrUsi = atoi(element);
//        element = strtok(NULL, delimitare);
//        m.pret = atoi(element);
//        masini = adaugareInVector(masini, m, nrMasini);
//
//    }
//    fclose(file);
//    return masini;
//}
//
//void citireMatrice(const char* numeFisier, struct Masina** matrice, int nrLinii, int* nrColoane) {
//
//    FILE* file = fopen(numeFisier, "r");
//    char buffer[100];
//    char delimitare[] = ",\n";
//    while (fgets(buffer, 100, file) != NULL) {
//        char* element = strtok(buffer, delimitare);
//        struct Masina m;
//        m.id = atoi(element);
//        element = strtok(NULL, delimitare);
//        m.producator = (char*)malloc(strlen(element) + 1);
//        strcpy(m.producator, element);
//        element = strtok(NULL, delimitare);
//        m.nrUsi = atoi(element);
//        element = strtok(NULL, delimitare);
//        m.pret = atoi(element);
//        matrice[m.nrUsi - 2] = adaugareInVector(matrice[m.nrUsi - 2], m, &(nrColoane[m.nrUsi - 2]));
//
//    }
//    fclose(file);
//}
//
////pretul mediu al masinilor cu nr de usi dat ca param
//float pretMediu(struct Masina** matrice, int nrLinii, int* nrColoane, int nrUsi) {
//    if (nrUsi < 1 && nrUsi>4) {
//        return 0;
//    }
//
//    float pretTotal = 0;
//    int index = nrUsi - 2;
//    if (nrColoane[index] == 0)
//        return 0;
//    for (int i = 0; i < nrColoane[index]; i++) {
//        pretTotal += matrice[index][i].pret;
//    }
//    return pretTotal / nrColoane[index];
//}
//
//struct Masina* masiniSport(struct Masina* masini, int nrMasini, int* nrMasiniSport) {
//    *nrMasiniSport = 0;
//    for (int i = 0; i < nrMasini; i++) {
//        if (masini[i].nrUsi < 4) {
//            (*nrMasiniSport)++;
//        }
//    }
//    struct Masina* vector = (struct Masina*)malloc(sizeof(struct Masina) * (*nrMasiniSport));
//    int k = 0;
//    for (int i = 0; i < nrMasini; i++) {
//        if (masini[i].nrUsi < 4) {
//            vector[k++] = masini[i];
//        }
//    }
//    return vector;
//}
//
//void afisareMatrice(struct Masina** matrice, int nrLinii, int* nrColoane) {
//    for (int i = 0; i < nrLinii; i++) {
//        for (int j = 0; j < nrColoane[i]; j++) {
//            printf("%d,  %s,  %d, %5.2f  \t", matrice[i][j].id, matrice[i][j].producator, matrice[i][j].nrUsi, matrice[i][j].pret);
//
//        }
//        printf("\n");
//    }
//}
//
//struct Masina cautareMasinaID(struct Masina** matrice, int nrLinii, int* nrCol, int id) {
//    for (int i = 0; i < nrLinii; i++)
//        for (int j = 0; j < nrCol[i]; j++)
//            if (matrice[i][j].id == id)
//                return matrice[i][j];
//
//    struct Masina mNull;
//    mNull.id = 0;
//    mNull.producator = NULL;
//    mNull.nrUsi = 0;
//    mNull.pret = 0;
//    return mNull;
//}
//
//void dezalocareMatrice(struct Masina*** matrice, int nrLinii, int** nrColoane) {
//    for (int i = 0; i < nrLinii; i++) {
//        for (int j = 0; j < (*nrColoane)[i]; j++) {
//            free((*matrice)[i][j].producator);
//        }
//        free((*matrice[i]));
//    }
//    free((*nrColoane));
//    nrColoane = NULL;
//    free((*matrice));
//    matrice = NULL;
//}
//
//int main() {
//
//    /* struct Masina* masini = NULL;
//     int nrMasini = 0;
//
//     masini = citireFisier("masini.txt", &nrMasini);
//     for (int i = 0; i < nrMasini; i++) {
//         printf("Masina are id-ul %d, producatorul %s, nrUsi %d si pretul %5.2f\n", masini[i].id, masini[i].producator, masini[i].nrUsi, masini[i].pret);
//     }
//     int* nrMasiniSport = 0;
//     struct Masina* masiniSport_ = NULL;
//     masiniSport_ = masiniSport(masini, 3, &nrMasiniSport);
//     for (int i = 0; i < nrMasiniSport; i++) {
//         printf("Masina are id-ul %d, producatorul %s, nrUsi %d si pretul %5.2f\n", masiniSport_[i].id, masiniSport_[i].producator, masiniSport_[i].nrUsi, masiniSport_[i].pret);
//     }*/
//
//    struct Masina** matrice;
//    int nrLinii = 3;
//    int* nrColoane;
//    nrColoane = (int*)malloc(sizeof(int) * nrLinii);
//    matrice = (struct Masina**)malloc(sizeof(struct Masina*) * nrLinii);
//    for (int i = 0; i < nrLinii; i++)
//    {
//        nrColoane[i] = 0;
//        matrice[i] = NULL;
//    }
//
//    citireMatrice("masini.txt", matrice, nrLinii, nrColoane);
//    afisareMatrice(matrice, nrLinii, nrColoane);
//
//    printf("%5.2f", pretMediu(matrice, nrLinii, nrColoane, 4));
//
//    struct Masina masinaCautata;
//    masinaCautata = cautareMasinaID(matrice, nrLinii, nrColoane, 2);
//    printf("\n\n\nMasina are id-ul %d, producatorul %s, nrUsi %d si pretul %5.2f\n", masinaCautata.id, masinaCautata.producator, masinaCautata.nrUsi, masinaCautata.pret);
//
//    dezalocareMatrice(&matrice, nrLinii, &nrColoane);
//}