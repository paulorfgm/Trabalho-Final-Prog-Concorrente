/*ARQUIVO .C COM IMPLEMENTAÇÃO DO ALGORITMO BFS CONCORRENTE*/
#define _GNU_SOURCE //Para usar a barreira

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#include "../include/fila.h"
#include "../include/grafo.h"
#include "../include/BFS.h"

/*VARIÁVEIS GLOBAIS*/
pthread_barrier_t barreira; // Barreira definida em pthread.h, usada durante o BFS
pthread_mutex_t *lock_vertices; // Vetor de locks, com um para cada vértice

Queue *fila_nivel_atual; // Fila com os vértices a serem explorados no nível atual
Queue *fila_proximo_nivel; // Fila com os vértices a serem explorados no próximo nível

Graph *graph;
COLOR *color;
int *parent;
int *distance;

int nivel_atual;
int continuar = 1;

//========= FUNÇÃO DAS THREADS ===============

void* processaNivel(void* arg) {
    long int thread_id = (long int) arg;

    while(continuar) {
        int vertice_atual;
        while((vertice_atual = dequeue(fila_nivel_atual)) != -1) {
            color[vertice_atual] = BLACK;

            Node *vizinho = graph->adjList[vertice_atual];
            while(vizinho != NULL) {
                int v = vizinho->id;

                pthread_mutex_lock(&lock_vertices[v]);

                if (color[v] == WHITE) {
                    color[v] = GREY;
                    parent[v] = vertice_atual;
                    distance[v] = nivel_atual + 1;
                    enqueue(fila_proximo_nivel, v);
                }

                pthread_mutex_unlock(&lock_vertices[v]);

                vizinho = vizinho->next;
            }
        }

        pthread_barrier_wait(&barreira);
    
        if (thread_id == 0) {
            Queue *temp = fila_nivel_atual;
            fila_nivel_atual = fila_proximo_nivel;
            fila_proximo_nivel = temp;
            nivel_atual++;
            
            if (isEmpty(fila_nivel_atual)) {
                continuar = 0;
            }
        } 
    
        pthread_barrier_wait(&barreira);
    }

    pthread_exit(NULL);
}

//=============================================

//========= FUNÇÃO PRINCIPAL ==================

void BFS_Concorrente(int inicio, int num_threads) {
    initializeIntVectors(graph->amountVertices);
    lock_vertices = (pthread_mutex_t *) malloc (graph->amountVertices * sizeof(pthread_mutex_t));

    for (int i = 0; i < graph->amountVertices; i++) {
        color[i] = WHITE;
        parent[i] = -1;
        distance[i] = -1;
        pthread_mutex_init(&lock_vertices[i], NULL);
    }

    color[inicio] = GREY;
    distance[inicio] = 0;
    nivel_atual = 0;
    continuar = 1;

    fila_nivel_atual = createQueue();
    fila_proximo_nivel = createQueue();

    enqueue(fila_nivel_atual, inicio);

    pthread_barrier_init(&barreira, NULL, num_threads);

    pthread_t threads[num_threads];
    
    for(long int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, processaNivel, (void*) i);
    }

    for(long int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_barrier_destroy(&barreira);
    for(int i = 0; i < graph->amountVertices; i++) {
        pthread_mutex_destroy(&lock_vertices[i]);
    }

    free(lock_vertices);
    freeQueue(fila_nivel_atual);
    freeQueue(fila_proximo_nivel);
}

//=============================================

//========= MAIN ==============================

int main(int argc, char* argv[]) {
    //Dados
    char arquivo_entrada[STRING_MAX] = "tests/";

    int verticeInicial;
    int num_threads;

    //Coletando variáveis
    if (argc < 3) {
        printf("Erro! A chamada do programa deve seguir o padrão: <%s> <nome-do-arquivo-entrada> <quantidade-de-threads>\n", argv[0]);
        exit(1);
    }
    else { //Montamos o caminho para arquivo
        strcat(arquivo_entrada, argv[1]);
        num_threads = atoi(argv[2]);
    }

    verticeInicial = lerEntrada(arquivo_entrada);

    printGraph(graph);

    BFS_Concorrente(verticeInicial, num_threads);

    printBFS(graph);

    return 0;
}

//=============================================
