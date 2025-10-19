#include <stdlib.h>
#include <stdio.h>

#include "../include/queue.h"

//========= Initialization ====================

QueueNode* createQueueNode(int data) {
    QueueNode* newNode = (QueueNode *) malloc(sizeof(QueueNode));
    newNode->next = NULL;
    newNode->data = data;
    return newNode;
}

Queue* createQueue() {
    Queue* queue = (Queue *) malloc(sizeof(Queue));
    queue->start = NULL;
    queue->end = NULL;
    pthread_mutex_init(&queue->lock, NULL);
    return queue;
}

void freeQueue(Queue *queue) {
    pthread_mutex_destroy(&queue->lock);
    free(queue);
}

//=============================================

//========= Main Functions ====================

//adiciona um dado "data" ao fim da fila
void enqueue(Queue *queue, int data) {
    QueueNode* newNode = createQueueNode(data);
    
    pthread_mutex_lock(&queue->lock);

    if(queue->start == NULL) {
        queue->start = queue->end = newNode;
    }

    else {
        queue->end->next = newNode;
        queue->end = newNode;
    }

    pthread_mutex_unlock(&queue->lock);
}

//retorna o valor no início da fila
int dequeue(Queue *queue) {
    pthread_mutex_lock(&queue->lock);

    if(isEmpty(queue)) { 
        return -1; 
        pthread_mutex_unlock(&queue->lock);
    }

    QueueNode *selectedNode = queue->start;
    int data = selectedNode->data;
    queue->start = queue->start->next;

    if(queue->start == NULL) queue->end = NULL;
    
    free(selectedNode);

    pthread_mutex_unlock(&queue->lock);
    
    return data;
}

//=============================================

//========= Others ============================

//retorna 1 se a fila estiver fazia, 0 caso contrário
int isEmpty(Queue *queue) {
    return (queue->start == NULL);
}

//=============================================