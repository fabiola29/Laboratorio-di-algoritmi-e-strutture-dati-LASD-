#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "List.h"

List initNodeList(int target, double prezzo, double distanza) {
    List L = (List)malloc(sizeof(struct TList));
    assert(L != NULL);// controllo che vi sia ancora memoria disponibile
    L->target = target;
    L->peso[PRICE] = prezzo;
    L->peso[DISTANCE] = distanza;
    L->next = NULL;
    return L;
}

List appendNodeList(List L, int target, double prezzo, double distanza) {
    if (L != NULL) {
        if (L->target != target) {
            L->next = appendNodeList(L->next, target, prezzo, distanza);
        }
        //else target gia' presente in lista e non sono ammessi duplicati, quindi non si fa nulla
    } else {
        L = initNodeList(target, prezzo, distanza);
    }
    return L;
}

List addNodeHead(List L, int target, double prezzo, double distanza) {
    List G = initNodeList(target, prezzo, distanza);
    if (L != NULL) {
        G->next = L;
    }
    return G;
}


List removeNodeList(List L, int target) {
    if (L != NULL) {
        if (L->target == target) {
            List tmp = L->next;
            free(L);
            return tmp;
        }
        L->next = removeNodeList(L->next, target);
    }
    return L;
}


List freeList(List L) {
    if (L != NULL) {
        L->next = freeList(L->next);
        free(L);
    }
    return NULL;
}


void printList(List L) {
    if (L != NULL) {
        printf("(Id:%d, Distance:%6g)", L->target, L->peso[DISTANCE]);
        printList(L->next);
    }
}



double getPriceFromPath(List path){
  if(path == NULL) return 0.0;
  List iter = NULL;
  for(iter = path; iter->next != NULL; iter = iter->next);
  return iter->peso[PRICE];
}
