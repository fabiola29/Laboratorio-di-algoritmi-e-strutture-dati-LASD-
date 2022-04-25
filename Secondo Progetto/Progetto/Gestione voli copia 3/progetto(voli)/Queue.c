#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Queue.h"

Queue initQueue(){
    Queue q = (Queue) malloc(sizeof(struct Tqueue));
    assert(q != NULL);
    q->head = q->tail = NULL;
    return q;
}

void freeQueue(Queue Q){
    assert(Q != NULL);
    QNode iter = Q->head, tmp = NULL;
    while (iter){
        tmp = iter;
        iter = iter->next;
        free(tmp);
    }
    free(Q);
    return;
}

QNode initQueueNode(int vertex){
    QNode newnode = (QNode) malloc(sizeof(struct node_struct));
    assert(newnode != NULL);
    newnode->vertex = vertex;
    newnode->next = NULL;
    return newnode;
}

int isEmptyQueue(Queue Q){
    assert(Q != NULL);
    return Q->head == NULL;
}

void enqueue(Queue Q, int vertex){
    QNode newnode = initQueueNode(vertex);
    if(isEmptyQueue(Q)){
        Q->tail = Q->head = newnode;
    }else{
        Q->tail->next = newnode;
        Q->tail = newnode;
    }
    return;
}

int dequeue(Queue Q, int* vertex){
    if(isEmptyQueue(Q)){
        return -1;
    }
    *vertex = Q->head->vertex;
    QNode tmp = Q->head;
    if(Q->head == Q->tail){
        Q->tail = NULL;
    }
    Q->head = Q->head->next;
    free(tmp);
    return 0;
}


