#ifndef funzioni_h
#define funzioni_h
#define funzioni_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXTITOLO 20
#define MAXAUTORE 50
#define MAXNOME 255
#define MAXCOGNOME 255
#define MAXMATRICOLA 9
#define LEN 1000

struct libri{
    char titolo [MAXTITOLO];
    char autore [MAXAUTORE];
    int cod_id;
    struct libri *next;
};
typedef struct libri* list;


int menu(void);
void printList(list L);
void gestioneErrore(void);
void SearchBook(struct libri *l, char titolo[]);
void freeNodo(struct libri *nodo);
list DeleteBook(list lis, char titolo[]);
struct libri *leggiFile(FILE *fp, struct libri *lista);
struct libri *nuovoNodo(char *titolo, char *autore, int cod_id);
struct libri *inserisciLista(struct libri *nodo, struct libri *lista);
list initList(char titolo[],char autore[],int cod_id);
list insertTail(list L, char titolo[], char autore[], int cod_id);

#endif


