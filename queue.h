#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"


typedef struct QueueNode{
    Tree *data;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue{
    QueueNode *front;
    QueueNode *end;
    int size;
}Queue;

Queue* createQueue(){
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->end = NULL;
    q->size = 0;
    return q;
}

void enque(Queue *q, Tree *t){
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    node->data = t;
    node->next = NULL;
    if(q->front == NULL){
        q->front = q->end = node;
    }
    else{
        q->end->next = node;
        q->end = node;
    }
    q->size++;
}
void deque(Queue *q){
    if(q->front == NULL)
        return;
    QueueNode *tmp = q->front;
    q->front = q->front->next;
    if(q->front == NULL)
        q->end = NULL;
    q->size--;
    free(tmp);
}
void freeQ(Queue *q){
    while(q->front){
        deque(q);
    }
    free(q);
}