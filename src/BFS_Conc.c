// ARQUIVO COM A IMPLEMENTAÇÃO CONCORRENTE DO BFS

#define _GNU_SOURCE //Para usar a barreira

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#include "../include/queue.h"
#include "../include/graph.h"
#include "../include/BFS.h" //? Trocar para um BFS_Conc.h

//Define para o grafo ser direcionado (DIRECTED) ou não direcionado (UNDIRECTED)
#define DIRECTION UNDIRECTED

#define STRING_MAX 100


//========= VARIÁVEIS GLOBAIS ====================
pthread_barrier_t barreira; 
pthread_mutex_t *lock_vertices; // Vetor de locks, com um para cada vértice

Queue *fila_nivel_atual;
Queue *fila_proximo_nivel;

Graph *graph;
COLOR *color;
int *parent;
int *distance;

int nivel_atual;
int continuar = 1;

//========= FUNÇÃO DAS THREADS ====================

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

//========= FUNÇÃO PRINCIPAL BFS CONCORRENTE ====================

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


//Função para leitura dos casos de teste
//Entrada: nome do arquivo .txt, e ponteiro para o grafo
//Saída: vertice inicial, com grafo alterado (referência)
int lerEntrada(char* arquivo_entrada) {
    FILE *arquivo = fopen(arquivo_entrada, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    
    printf("====== LEITURA DO ARQUIVO ======\n");

    int V, E;
    fscanf(arquivo, "%d %d", &V, &E);
    printf("Vértices: %d, Arestas: %d\n", V, E);

    graph = createGraph(V, DIRECTION);
    
    int origem, destino;
    for (int i = 0; i < E; i++) {
        fscanf(arquivo, "%d %d", &origem, &destino);
        addEdge(graph, origem, destino);
        printf("(%d, %d)\n", origem, destino);
    }

    int verticeInicial;
    fscanf(arquivo, "%d", &verticeInicial);
    printf("Vertice inicial: %d\n", verticeInicial);

    printf("====== FIM DA LEITURA ==========\n\n");

    fclose(arquivo);

    return verticeInicial;
}

int main(int argc, char* argv[]) {
    //Dados
    char arquivo_entrada[STRING_MAX] = "tests/";

    int verticeInicial;

    //Coletando variáveis
    if (argc < 2) {
        printf("Erro! A chamada do programa deve seguir o padrão: <%s> <nome-do-arquivo-entrada>\n", argv[0]);
        exit(1);
    }
    else { //Montamos o caminho para arquivo
        strcat(arquivo_entrada, argv[1]);
    }

    verticeInicial = lerEntrada(arquivo_entrada);

    printGraph(graph);

    int num_threads = 2; // Número fixo de threads
    BFS_Concorrente(verticeInicial, num_threads);

    printBFS(graph);

    return 0;
}