//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<malloc.h>
//#include<string.h>
//
//typedef struct Televizor Televizor;
//typedef struct Nod Nod;
//
//
//struct Televizor {
//    int cod;
//    char* marca;
//    float diagonala;
//    int rezolutie[2]; // rezolutie[0] - latime, rezolutie[1] - inaltime
//    float pret;
//};
//
//struct Nod {
//    Televizor televizor;
//    Nod* next;
//};
//
//Televizor intializareTV(int cod, const char* marca, float diagonala, int rezolutie[2], float pret) {
//    Televizor tv;
//    tv.cod = cod;
//    if (tv.marca != NULL) {
//        tv.marca = malloc(strlen(marca) + 1);
//        strcpy(tv.marca, marca);
//    }
//    tv.diagonala = diagonala;
//    tv.rezolutie[0] = rezolutie[0];
//    tv.rezolutie[1] = rezolutie[1];
//    tv.pret = pret;
//
//    return tv;
//}
//
//void afiseaza(struct Televizor televizor) {
//    printf("Cod: %d\n", televizor.cod);
//    if (televizor.marca != NULL)
//        printf("Marca: %s\n", televizor.marca);
//    else
//        printf("Marca: -");
//    printf("Diagonala: %.2f inch\n", televizor.diagonala);
//    printf("Rezolutie: %d x %d\n", televizor.rezolutie[0], televizor.rezolutie[1]);
//    printf("Pret: %.2f lei\n", televizor.pret);
//    printf("\n");
//}
//
//void afisareLista(Nod* lista) {
//    while (lista!=NULL)
//    {
//        afiseaza(lista->televizor);
//        lista = lista->next;
//    }
//}
//
//Nod* insearareInceput(Televizor televizor, Nod* lista) {
//    Nod* nod = (Nod*)malloc(sizeof(Nod));
//    nod->televizor = televizor;
//    nod->next = lista;
//}
//
//float calculDistantaPotrivita(Televizor tv) {
//    return 1.2 * tv.diagonala;
//}
//
//char* distantaPotrivitaMaxima(Nod* lista) {
//    float max = 0;
//    char* aux = NULL;
//    while (lista != NULL) {
//        if (calculDistantaPotrivita(lista->televizor) > max) {
//            aux = lista->televizor.marca;
//            max = calculDistantaPotrivita(lista->televizor);
//        }
//        lista = lista->next;
//    }
//
//    if (aux != NULL) {
//        char* marcaTV = (char*)malloc(sizeof(marcaTV));
//        strcpy(marcaTV, aux);
//        return marcaTV;
//    }
//    else return NULL;
//}
//
//int contorNoduriLista(Nod* lista) {
//    int sNoduri = 0;
//    while (lista != NULL) {
//        sNoduri++;
//        lista = lista->next;
//    }
//    return sNoduri;
//}
//
////void stergereNodPozitieData(Nod** lista, int pozitie) {
////    int cont = 0;
////    if (contorNoduriLista(*lista) <= pozitie && pozitie > 0) {
////        while ((*lista) != NULL) {
////            cont++;
////            if (cont == pozitie) {
////                Nod* aux = (*lista)->next;
////                
////            }
////        }
////    }
////   
////}
//
//void stergereNod(Nod* nod) {
//    free(nod->televizor.marca);
//    free(nod);
//}
//
//int main() {
//
//    int r1[] = {12, 14};
//    int r2[] = {13, 24};
//    int r3[] = {14, 17};
//    Nod* lista = NULL;
//    Televizor t1 = intializareTV(1232, "Samsung", 12, r1 , 2334);
//    Televizor t2 = intializareTV(14352, "Apple", 13, r2 , 2303.4);
//    Televizor t3 = intializareTV(12332, "Samsung Ultimate TV", 15, r3 , 2322.34);
//    lista = insearareInceput(t1, lista);
//    lista = insearareInceput(t2, lista);
//    lista = insearareInceput(t3, lista);
//    lista = insearareInceput(intializareTV(124, "Sharp", 12, r2, 2300), lista);
//    afisareLista(lista);
//    printf("\n\n%s\n", distantaPotrivitaMaxima(lista));
//    printf("\n\n%d\n", contorNoduriLista(lista));
//	return 0;
//}