#ifndef Graph_Graph_h
#define Graph_Graph_h
#include "List.h"

//struttura per il grafo
struct TGraph {
    List *adj;
    int nodes_count;
    char** cityNames;
};

typedef struct TGraph* Graph;

// Dealloca l'intero grafo
void freeGraph(Graph G);

// Inizializza un nuovo grafo vuoto specificando in ingresso quanti nodi saranno nel grafo
Graph initGraph(int nodes_count, char** cityNames);

// Stampa il grafo
void PrintGraph(Graph G);

// Stampa le citta contenute nel grafo
void PrintCityGraph(Graph G);

// Aggiunge un arco, specificando sorgente, target e peso
void addEdge(Graph G, int source, int target, double prezzo, double distanza);

// Rimuovi un arco specificando sorgente e target,restituisce la lista degli archi modifcata
List removeEdge(Graph G, int source, int target);

// Aggiungi un nodo
void addNode(Graph G, char* newCity);

// Rimuovi un nodo dal grafo, sistemando gli indici e riallocando la memoria
void removeNodeByIndex(Graph G, int node_to_remove);

//Rimuovo una città
void removeNodeByString(Graph G, char* name);

List checkListRemoval(List L, int node_to_remove);

//enumerazionw colori per la bfs
typedef enum{WHITE, GREY, BLACK} GraphColor;

// ricerca del percorso minimo dal vertice source a quello target
List bfs(Graph G, int source, int target);

// minimizza il percorso considerando il peso degli archi del grafo (funziona solo se tutti gli archi hanno peso positivo)
List dijkstra(Graph G, int source, int target, weightSelector selector);
int findMinIndexInVect(double* vect, GraphColor* visited, int dim);

// estrapola da visit_info il percorso da source a target
List generatePath(int* visit_info, double* price_info, double* distance_info, int source, int target);

// cerca il numero del vertice associato al nome di una particolare citta'
int getCityIndexByName(Graph G, char* key);

//permette di ottieni l'indice della città
int getCityIndex(Graph G, char* message);

//funzione per popolare il grafo
Graph populateGraph(void);

//permette di ottenere da tastiere il nome di una città non per forza presente nel grafo
char* getCityName(char* message);

//stampa path
void printPath(Graph G, List path);

#endif /*Graph_Graph_h*/





