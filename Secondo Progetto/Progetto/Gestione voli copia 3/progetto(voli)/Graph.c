#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "Graph.h"
#include "List.h"
#include "Queue.h"
#define BUFFER_SIZE 256


Graph initGraph(int nodes_count, char** cityNames) {
    Graph G = (Graph)malloc(sizeof(struct TGraph));
    assert(G != NULL);
    G->adj = (List *)calloc(nodes_count, sizeof(List));
    assert(G->adj != NULL);
    G->nodes_count = nodes_count;
    G->cityNames = cityNames;
    return G;
}

void freeGraph(Graph G) {
    if (G != NULL) {
        if (G->nodes_count > 0) {
            int i = 0;
            for (i = 0; i < G->nodes_count; i++) {
                G->adj[i] = freeList(G->adj[i]);
                free(G->cityNames[i]);
            }
        }
        free(G->adj);
        free(G->cityNames);
        free(G);
    }
}

void addEdge(Graph G, int source, int target, double prezzo, double distanza) {//source=partenza, target=arrivo
    assert(G != NULL);
    assert(source < G->nodes_count);
    assert(target < G->nodes_count);
    if (source != target) {
        G->adj[source] = appendNodeList(G->adj[source], target, prezzo, distanza);
    }
    
}

List removeEdge(Graph G, int source, int target) {
    assert(G != NULL);
    assert(source < G->nodes_count);
    assert(target < G->nodes_count);
    if (source != target) {
        G->adj[source] = removeNodeList(G->adj[source], target);
    }
    return G->adj[source];
}


void addNode(Graph G, char* newCity) {
    if (G != NULL) {
        List * old=G->adj;
        char** old_matrix = G->cityNames;
        int i=0;
        G->adj = (List *)calloc(G->nodes_count+1, sizeof(List));
        assert(G->adj != NULL);
        G->cityNames = (char**)calloc(G->nodes_count+1, sizeof(char*));
        assert(G->cityNames != NULL);
        for(i=0;i<G->nodes_count;i++){
            G->adj[i]=old[i];
            G->cityNames[i] = old_matrix[i];
        }
        G->nodes_count += 1;
        G->adj[G->nodes_count-1] = NULL;
        G->cityNames[G->nodes_count-1] = (char*) calloc(strlen(newCity)+1, sizeof(char));
        assert(G->cityNames[G->nodes_count-1] != NULL);
        strcpy(G->cityNames[G->nodes_count-1], newCity);
    }
}


void removeNodeByIndex(Graph G, int node_to_remove) {
    if (G != NULL) {
        if(node_to_remove >= G->nodes_count || node_to_remove < 0){
            // il nodo da rimuovere non appartiene al grafo
            return;
        }
        int i = 0;
        int x = 0;
        List *tmp = G->adj;
        char** old_matrix = G->cityNames;
        G->adj = (List *)calloc(G->nodes_count-1, sizeof(List));
        assert(G->adj != NULL);
        G->cityNames = (char**)calloc(G->nodes_count-1, sizeof(char*));
        assert(G->cityNames != NULL);
        for (i = 0; i < G->nodes_count; i++) {
            if (i != node_to_remove) {
                G->adj[x] = checkListRemoval(tmp[i], node_to_remove);
                G->cityNames[x] = old_matrix[i];
                x++;
            } else {
                free(old_matrix[i]);
                G->adj[i] = freeList(tmp[i]);
            }
        }
        free(tmp);
        free(old_matrix);
        G->nodes_count -= 1;
    }
}

void removeNodeByString(Graph G, char* name){
    removeNodeByIndex(G, getCityIndexByName(G, name));
    return;
}

List checkListRemoval(List L, int node_to_remove) {
    if (L != NULL) {
        L->next = checkListRemoval(L->next, node_to_remove);
        if (L->target == node_to_remove) {
            List tmp = L->next;
            free(L);
            return tmp;
        } else if (L->target > node_to_remove) {
            L->target -= 1;
        }
    }
    return L;
}


List bfs(Graph G, int source, int target){
    assert(G != NULL);                                          // controllo che il grafo non sia nullo
    assert(source < G->nodes_count || target < G->nodes_count); // controllo che i vertici inseriti appartengano al grafo
    Queue Q = initQueue();//inizializza i nodi del grafo in particolare serve per espolora i nodi della dfs in modo corretto.
    int* visit_path = (int*)calloc(G->nodes_count, sizeof(int));//serve per capire quale nodo ha scoperto un altro nodo
    assert(visit_path != NULL);
    double* distanceInfo = (double*) calloc(G->nodes_count, sizeof(double));//dichiaro la variabile distanceInfo ed uso una calloc perchè è possibile che la dimensione allocata può variare ed con una dim fissa alcuni nodi possono non essere esplorati
    assert (distanceInfo != NULL);
    double* priceInfo = (double*) calloc(G->nodes_count, sizeof(double));//stesso discorso di distanceInfo
    assert(priceInfo != NULL);
    // calloc inizializza gli interi a zero, che nella enum corrisponde a WHITE
    GraphColor* visited = (GraphColor*) calloc(G->nodes_count, sizeof(GraphColor));
    assert(visited != NULL);
    enqueue(Q, source);
    visited[source] = BLACK;
    // il nodo di partenza e' raggiungibile da se stesso con un percoso nullo
    visit_path[source] = source;
    distanceInfo[source] = 0.0;
    priceInfo[source] = 0.0;
    int targetFound = 0;
    int v;//contiene la testa della coda
    while(!isEmptyQueue(Q)  && !targetFound){//controllo che la coda non è vuota ed la città di destinazione non è stata trovata
        // non occorre controllare  che la coda abbiamo terminato l'operazione correttamente
        // dato che in questo punto del codice sicuramente non e' vuota;
        dequeue(Q, &v);//toglie il primo nodo dalla coda che nel primo caso è il sorgente e negli altri è il vertice adiacente
        for(List iter = G->adj[v]; iter != NULL; iter = iter->next){//itero sugli adiacenti del nodo v
            if(visited[iter->target] == WHITE){//se un nodo adiacente a v è bianco
                enqueue(Q, iter->target);//viene inserito nella coda
                // segno di aver visitato il vertice in cui termina l'arco
                visited[iter->target] = BLACK;
                // segno che il vertice in questione e' raggiungibile con un arco partendo dal vertice v
                visit_path[iter->target] = v;
                // calcolo il peso del percorso
                distanceInfo[iter->target] = distanceInfo[v] + iter->peso[DISTANCE];
                priceInfo[iter->target] = priceInfo[v] + iter->peso[PRICE];
                if(iter->target == target){
                    targetFound = 1;
                    break;
                }
            }
        }
    }
    freeQueue(Q);
    List path = NULL;
    if(targetFound == 1){
        path = generatePath(visit_path, priceInfo, distanceInfo, source, target);
    }
    free(visited);
    free(visit_path);
    free(distanceInfo);
    free(priceInfo);
    return path;
}

List dijkstra(Graph G, int source, int target, weightSelector selector){
    assert(G != NULL);
    int* visit_path = (int*) calloc(G->nodes_count, sizeof(int));//serve per capire quale nodo ha scoperto un altro nodo
    assert(visit_path != NULL);
    double* primaryWeight = (double*) calloc(G->nodes_count, sizeof(double));//dichiaro la variabile primaruWeight che serve per capire se usiamo il prezzo
    assert (primaryWeight != NULL);
    double* secondaryWeight = (double*) calloc(G->nodes_count, sizeof(double));//dichiaro la variabile secondaryWeight che serve per capire se usiamo la distanza
    assert (secondaryWeight != NULL);
    weightSelector secondarySelector = (selector == PRICE)? DISTANCE : PRICE;
    List path = NULL;
    GraphColor* visited = (GraphColor*) calloc(G->nodes_count, sizeof(GraphColor));
    assert(visited != NULL);
    for(int i=0; i<G->nodes_count; i++){
        primaryWeight[i] = (source == i) ? 0.0 : INFINITY;
        secondaryWeight[i] = (source == i) ? 0.0 : INFINITY;
    }
    int targetFound = 0;
    int currentVertex = -1;
    while(1){
        // estraiamo il vertice di distanza minima
        currentVertex = findMinIndexInVect(primaryWeight, visited, G->nodes_count);
        // esploriamo gli adiacenti del vertice estratto
        if (currentVertex == -1){
            // in questo caso non ci sono piu' percorsi da esplorare, possiamo uscire dal while
            break;
        }
        visited[currentVertex] = BLACK;
        for(List iter = G->adj[currentVertex]; iter != NULL; iter = iter->next){
            // se il vertice in cui si arriva attraversando l'arco ha un peso superiore a quello attualmente calcolato si aggiornano le informazioni
            if(iter->target == target){
                // in questo caso si e' certi che esiste almeno un percorso
                targetFound = 1;
            }
            double tmp = primaryWeight[currentVertex] + iter->peso[selector];
            if(primaryWeight[iter->target] > tmp){
                primaryWeight[iter->target] = tmp;
                visit_path[iter->target] = currentVertex;
                secondaryWeight[iter->target] = secondaryWeight[currentVertex] + iter->peso[secondarySelector];
            }
        }
    }
    if(targetFound == 1){
        if(selector == BY_PRICE){
            path = generatePath(visit_path, primaryWeight, secondaryWeight, source, target);
        }else{
            path = generatePath(visit_path, secondaryWeight, primaryWeight, source, target);
        }
    }
    free(visit_path);
    free(primaryWeight);
    free(secondaryWeight);
    free(visited);
    return path;
}

int findMinIndexInVect(double* vect, GraphColor* visited, int dim){
    int index = -1;
    int firstFind = 0;
    for(int i=0; i<dim; i++){
        if(firstFind == 0 && visited[i] == WHITE){// ricerca del primo elemento valido
            index = i;
            firstFind = 1;
        }else if(firstFind == 1 && visited[i] == WHITE){// se ho trovato gia' un elemnto valido devo controllare che sia il minimo
            if(vect[index] > vect[i]){
                index = i;
            }
        }
    }
    if(vect[index] == INFINITY){
        index = -1;
    }
    return index;
}

List generatePath(int* visit_info, double* price_info, double* distance_info, int source, int target){
    if(source == target){
        return initNodeList(source, price_info[source], distance_info[source]);
    }else{
        List path = generatePath(visit_info, price_info, distance_info, source, visit_info[target]);
        path = appendNodeList(path, target, price_info[target], distance_info[target]);
        return path;
    }
}

int getCityIndexByName(Graph G, char* key){
    assert(G != NULL);
    assert(G->cityNames != NULL);
    int index = -1;
    int i;
    for(i=0; i<G->nodes_count; i++){
        if(!strcmp(G->cityNames[i], key)){
            index = i;
            break;
        }
    }
    return index;
}

int getCityIndex(Graph G, char* message){
    if(G == NULL){
        printf("Graph not initialized\n");
        return -1;
    }
    if(G->nodes_count == 0){
        printf("Empty graph\n");
        return -1;
    }
    int choice;
    do{
        printf("\nAvailable destinations:\n");
        for(int i=0; i<G->nodes_count; i++){
            printf("Name: %s, Id: %d\n", G->cityNames[i], i);
        }
        printf("\nSelect  %s:", message);
        scanf("%d", &choice);
        if(choice < 0 || choice >= G->nodes_count){
            printf("Invalid choice.\n");
        }
    }while(choice < 0 ||  choice >= G->nodes_count);
    return choice;
}

Graph populateGraph(){
    Graph g = NULL;
 
      char** nomiCitta = (char**) calloc(20, sizeof(char*));
    assert(nomiCitta != NULL);
    for(int i=0; i<20; i++){
        nomiCitta[i] = (char*) calloc(60, sizeof(char));
        assert(nomiCitta[i] != NULL);
    }
    strcpy(nomiCitta[0],  "Napoli");
    strcpy(nomiCitta[1],  "Roma");
    strcpy(nomiCitta[2],  "Milano");
    strcpy(nomiCitta[3],  "Torino");
    strcpy(nomiCitta[4],  "Salerno");
    strcpy(nomiCitta[5],  "Praga");
    strcpy(nomiCitta[6],  "Bari");
    strcpy(nomiCitta[7],  "Londra");
    strcpy(nomiCitta[8],  "Cagliari");
    strcpy(nomiCitta[9],  "Venezia");
    strcpy(nomiCitta[10], "Genova");
    strcpy(nomiCitta[11], "Firenze");
    strcpy(nomiCitta[12], "Palermo");
    strcpy(nomiCitta[13], "Catania");
    strcpy(nomiCitta[14], "Parma");
    strcpy(nomiCitta[15], "Verona");
    strcpy(nomiCitta[16], "Bergamo");
    strcpy(nomiCitta[17], "Bolzano");
    strcpy(nomiCitta[18], "Perugia");
    strcpy(nomiCitta[19], "Taranto");
    g = initGraph(20,nomiCitta); //popolo grafo
    addEdge(g, getCityIndexByName(g, "Napoli"), getCityIndexByName(g, "Milano"), 41.00, 657.00);
    addEdge(g, getCityIndexByName(g, "Napoli"), getCityIndexByName(g, "Roma"), 37.00, 198.00);
    addEdge(g, getCityIndexByName(g, "Roma"), getCityIndexByName(g, "Milano"), 84.00, 478.00);
    addEdge(g, getCityIndexByName(g, "Milano"), getCityIndexByName(g, "Londra"), 300.50, 1195.1);
    addEdge(g, getCityIndexByName(g, "Torino"), getCityIndexByName(g, "Salerno"), 112.80 ,930.60);
    addEdge(g, getCityIndexByName(g, "Salerno"), getCityIndexByName(g, "Praga"), 123.80,1544.00);
    addEdge(g, getCityIndexByName(g, "Praga"), getCityIndexByName(g, "Salerno"), 111.80,15544.0);
    addEdge(g, getCityIndexByName(g, "Praga"), getCityIndexByName(g, "Torino"), 128.44, 752.00);
    addEdge(g, getCityIndexByName(g, "Bari"), getCityIndexByName(g,  "Venezia"), 30.00, 602.45);
    addEdge(g, getCityIndexByName(g, "Londra"), getCityIndexByName(g, "Firenze"), 1542.31, 141.00);
    addEdge(g, getCityIndexByName(g, "Cagliari"), getCityIndexByName(g, "Firenze"), 537.11, 183.00);
    addEdge(g, getCityIndexByName(g, "Venezia"), getCityIndexByName(g, "Catania"), 74.00, 1294.30);
    addEdge(g, getCityIndexByName(g, "Genova"), getCityIndexByName(g, "Perugia"), 74.47, 312.76);
    addEdge(g, getCityIndexByName(g, "Firenze"), getCityIndexByName(g, "Bari"), 189.00, 547.00);
    addEdge(g, getCityIndexByName(g, "Palermo"), getCityIndexByName(g, "Londra"), 72.00, 1779.42);
    addEdge(g, getCityIndexByName(g, "Catania"), getCityIndexByName(g, "Venezia"), 1.00, 1294.30);
    addEdge(g, getCityIndexByName(g, "Parma"), getCityIndexByName(g, "Verona"), 66.80, 144.16);
    addEdge(g, getCityIndexByName(g, "Verona"), getCityIndexByName(g, "Praga"), 122.00, 813.28);
    addEdge(g, getCityIndexByName(g, "Bergamo"), getCityIndexByName(g, "Palermo"), 81.00, 878.69);
    addEdge(g, getCityIndexByName(g, "Bolzano"), getCityIndexByName(g, "Taranto"), 89.00, 820.96);
    addEdge(g, getCityIndexByName(g, "Perugia"), getCityIndexByName(g, "Bolzano"), 110.56, 385.19);
    addEdge(g, getCityIndexByName(g, "Taranto"), getCityIndexByName(g, "Catania"), 60.67, 479.69);
    return g;
}

char* getCityName(char* message){
    char buffer[BUFFER_SIZE];
    char* new_string;
    printf("Insert the %s:", message);
    scanf("%s", buffer);
    new_string = (char*) calloc( strlen(buffer)+1, sizeof(char));
    assert(new_string != NULL);
    strcpy(new_string, buffer);
    return new_string;
}

 void PrintGraph(Graph G){
    assert(G!=NULL);
    for(int i=0; i<G->nodes_count; i++){
        printf("[Id:%d, City: %s] ", i, G->cityNames[i]);
        for(List iter = G->adj[i];iter !=NULL;iter = iter->next){
            printf("--> (Id: %d, City: %s, Piece:%lf, Distance:%lf)",iter->target, G->cityNames[iter->target], iter->peso[PRICE], iter->peso[DISTANCE]);
    }
    puts("");
    }
    return;
}

void PrintCityGraph(Graph G){
    assert(G != NULL);
    for(int i=0; i < G->nodes_count; i++){
        printf("Id: %d, City name: %s\n", i, G->cityNames[i]);
    }
    puts("");
    return;
}

void printPath(Graph G, List path){
    assert(G != NULL);
    if(path == NULL){
        return;
    }
    printf("PATH: ");
    List iter = NULL;
    double prezzo = 0.0, distanza = 0.0;
    for(iter = path; iter != NULL; iter = iter->next){
        printf("id: %d, name: %s -->  ", iter->target, G->cityNames[iter->target]);
        if(iter->next == NULL){
            prezzo = iter->peso[PRICE];
            distanza = iter->peso[DISTANCE];
        }
    }
    printf("(Piece: %lf, Distance: %lf)\n", prezzo, distanza);
    return;
}


