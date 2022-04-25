#ifndef Graph_List_h
#define Graph_List_h

//struttura lista
 struct TList {
    int target;
    char city[10];
    double peso[2];
    struct TList* next;
};

typedef struct TList* List;

//enumerazione che ci permette di capire se usiamo il prezzo oppure il peso
typedef enum{PRICE, DISTANCE} weightSelector;

#define  BY_PRICE PRICE
#define  BY_DISTANCE DISTANCE

// Inizializza un nuovo nodo
List initNodeList(int target, double prezzo, double distanza);

// Aggiunge un nodo alla fine della lista
// controllandone l'esistenza
// La funzione ritorna sempre la testa della lista
List appendNodeList(List L, int target, double prezzo, double distanza);

// Aggiunge un nodo in testa alla lista
// senza controllare l'esistenza
// La funzione ritorna sempre la testa della lista
List addNodeHead(List L, int target, double prezzo, double distanza);

// Rimuove solo un occorrenza di un nodo con il target specificato
// dalla lista
// La funzione ritorna sempre la testa della lista
List removeNodeList(List L, int target);

// Dealloca la lista interamente
List freeList(List L);

// Stampa la lista
void printList(List L);

// funzioni di servizio
double getPriceFromPath(List path);

#endif /* Graph_List_h */




