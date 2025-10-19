#ifndef QUEUE_H
#define QUEUE_H

/*STRUCTURES DEFINITIONS*/

typedef struct QueueNode {
    int data;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode *start, *end;
} Queue;

/*FUNCTIONS*/

//Initialization
QueueNode* createQueueNode(int data);
Queue* createQueue(); 

//Main Functions
void enqueue(Queue *queue, int data); //adiciona um valor "dado" no final da fila
int dequeue(Queue *queue); //retorna o dado na frente da fila

//Others
int isEmpty(Queue *queue); //retorna 1 se a fila estiver vazia, 0 caso contrário

#endif