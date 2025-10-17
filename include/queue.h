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
void enqueue(Queue *queue, int data); //enqueues an int with data at the end of the queue
int dequeue(Queue *queue); //returns the data at the start of the queue

//Others
int isEmpty(Queue *queue); //returns 1 if empty, 0 if not.

#endif