#ifndef QUEUE_H
#define QUEUE_H
          // questa coda sara' utilizzata per contenere valori interi
         // che rappresentano i vertici di un grafo
         // Nb: solo i vertici e non i pesi di eventuali archi

typedef struct node_struct{
        struct node_struct* next;
        int vertex;
}* QNode;
    
typedef struct Tqueue{
        QNode head;
        QNode tail;
}* Queue;


Queue initQueue(void);

void  freeQueue(Queue Q);

QNode initQueueNode(int vertex);

int isEmptyQueue(Queue Q);

void enqueue(Queue Q, int vertex);
     
// il valore di ritorno e' utilizzato per vedere se l'operazione va a buon fine
// se e' vuota ritorna -1 e la dequeue non e' stata eseguita
// in ogni altro caso ritorna 0 ed il puntatore *vertex conterra' il vertice
int dequeue(Queue Q, int* vertex);

#endif /* Queue_h */



