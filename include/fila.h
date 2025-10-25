/*HEADER PARA DEFINIÇÕES DE FILA*/
#ifndef FILA_H
#define FILA_H

/*INCLUINDO HEADERS AUXILIARES*/
#include "pthread.h"

/*DEFINIÇÕES DE ESTRUTURA DA FILA*/
typedef struct QueueNode {
    int data;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode *start, *end;
    pthread_mutex_t lock; // cada fila tem seu próprio lock, para garantir exclusão mútua
} Queue;

/*DEFINIÇÕES DAS FUNÇÕES DE FILA*/

//*1. Funções de Inicialização

//cria um "nó de fila"
QueueNode* createQueueNode(int data);

//inicializa uma fila vazia
Queue* createQueue(); 

//libera o espaço de memória da fila
void freeQueue(Queue *queue); 

//*2. Funções Principais

//adiciona um dado "data" ao fim da fila
void enqueue(Queue *queue, int data);

//retorna o valor no início da fila
int dequeue(Queue *queue); 

//*3. Funções Auxiliares

//indica se a fila está (1) ou não (0) vazia
int isEmpty(Queue *queue); 

#endif