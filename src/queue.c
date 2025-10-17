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
    return queue;
}

//=============================================

//========= Main Functions ====================

//enqueues an int with data at the end of the queue
void enqueue(Queue *queue, int data) {
    QueueNode* newNode = createQueueNode(data);

    if(queue->start == NULL) {
        queue->start = queue->end = newNode;
    }

    else {
        queue->end->next = newNode;
        queue->end = newNode;
    }
}

//returns the data at the start of the queue
int dequeue(Queue *queue) {
    if(isEmpty(queue)) return -1;

    QueueNode *selectedNode = queue->start;
    int data = selectedNode->data;
    queue->start = queue->start->next;

    if(queue->start == NULL) queue->end = NULL;

    free(selectedNode);
    return data;
}

//=============================================

//========= Others ============================

//returns 1 if empty, 0 if not.
int isEmpty(Queue *queue) {
    return (queue->start == NULL);
}

//=============================================