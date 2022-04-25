#include "ListPrenotazioni.h"
#include <stdlib.h>
#include <string.h>

ListPrenotazioni initListPrenotazioni(char email_intestatario[50], char citta_src[32], char citta_dest[32], double bill) {
    ListPrenotazioni l = (ListPrenotazioni)malloc(sizeof(struct prenotazione));
    strcpy(l->citta_src, citta_src);
    strcpy(l->citta_dest, citta_dest);
    strcpy(l->email_intestatario, email_intestatario);
    l->bill = bill;
    l->next = NULL;
    return l;
}


void printListPrenotazioni(ListPrenotazioni l) {
    if (l != NULL) {
        printf("\n Booking holder:%s -->  Start:%s - Coming:%s\t", l->email_intestatario, l->citta_src, l->citta_dest);
        printListPrenotazioni(l->next);
    }
}

void filterPrintListPrenotazioni(ListPrenotazioni L, char email_intestatario[50]){
    ListPrenotazioni iter = L;
    int num_prenotazioni = 1;
    while(iter){
        if(strcmp(email_intestatario, L->email_intestatario) == 0){
            printf("Reservations %d:: ", num_prenotazioni);
            num_prenotazioni++;
            printf("Start:%s - Coming:%s, Bill:%lf\n", iter->citta_src, iter->citta_dest, iter->bill);
        }
        iter = iter->next;
    }
    return;
}

ListPrenotazioni insertTailPrenotazioni(ListPrenotazioni l, char email_intestatario[50], char citta_src[32], char citta_dest[32], double bill) {
    if (l != NULL) {
        l->next = insertTailPrenotazioni(l->next, email_intestatario, citta_src, citta_dest, bill);
    }
    else{
        l = initListPrenotazioni(email_intestatario, citta_src, citta_dest, bill);
    }
    return l;
}

ListPrenotazioni freeListPrenotazioni(ListPrenotazioni L){
    if(L){
        L->next = freeListPrenotazioni(L->next);
        free(L);
    }
    return NULL;
}


