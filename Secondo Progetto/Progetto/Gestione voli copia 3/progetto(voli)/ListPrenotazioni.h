#ifndef ListPrenotazioni_H
#define ListPrenotazioni_H
#include <stdio.h>
#define LEN 100
#define MAX 20
//struttura prenotazioni

struct prenotazione{
    char email_intestatario[50]; // serve per capire chi ha effettuato una prenotazione
    char citta_src[32];
    char citta_dest[32];
    double bill;
    struct prenotazione* next;
};

typedef struct prenotazione* ListPrenotazioni;


ListPrenotazioni initListPrenotazioni(char email_intestatario[50], char citta_src[32], char citta_dest[32], double bill);


void printListPrenotazioni(ListPrenotazioni L);


void filterPrintListPrenotazioni(ListPrenotazioni L, char email_intestatario[50]);

ListPrenotazioni insertTailPrenotazioni(ListPrenotazioni L, char email_intestatario[50], char citta_src[32], char citta_dest[32], double bill);

ListPrenotazioni freeListPrenotazioni(ListPrenotazioni L);

#endif /* ListPrenotazioni_h*/


