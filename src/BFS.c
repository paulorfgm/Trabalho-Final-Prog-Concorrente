/*ARQUIVO .C COM IMPLEMENTAÇÃO DAS FUNÇÕES AUXILIARES AO ALGORITMO BFS*/
#include <stdlib.h>
#include <stdio.h>

#include "../include/BFS.h"
#include "../include/fila.h"
#include "../include/grafo.h"

/*DEFINIÇÕES DE VARIÁVEIS GLOBAIS*/
Graph *graph = NULL;
COLOR *color = NULL;
int *parent = NULL;
int *distance = NULL;

//========= INICIALIZAÇÃO ====================

void initializeIntVectors(int size) {
    freeIntVectors();
    color = (int *) malloc (sizeof(int) * size);
    parent = (int *) malloc (sizeof(int) * size);
    distance = (int *) malloc (sizeof(int) * size);
}

void freeIntVectors() {
    free(color);
    free(parent);
    free(distance);
}

void initializeGraphBFS(Graph *graph) {
    initializeIntVectors(graph->amountVertices);
    for (int i = 0; i < graph->amountVertices; i++) {
        color[i] = WHITE;
        parent[i] = -1;
        distance[i] = -1;
    }
}

//=============================================

//========= LEITURA DE ARQUIVOS ===============

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

//=============================================

//========= OUTROS ============================

void printBFS(Graph* graph) {
    printf("====== INICIO DO BFS ===========");
    printf("\n");
    for(int i = 0; i < graph->amountVertices; i++) {
        printf("Vértice: %d - Cor: %s - Pai: %d - Distância: %d\n", i, colorToString(color[i]), parent[i], distance[i]);
    }
    printf("====== FIM DO BFS ==============\n\n");
}

void printPath(Graph *graph, int start, int end) {
    if (start == end) printf("\n\nImprimindo Caminho:\n[%d] ", start);
    else if (parent[end] == -1) printf("Não há caminho entre [%d] e [%d]", start, end);
    else {
        printPath(graph, start, parent[end]);
        printf(" [%d] ", end);

    }
}

const char* colorToString(COLOR color) {
    switch (color) {
        case WHITE: return "WHITE";
        case GREY:  return "GREY";
        case BLACK: return "BLACK";
        default:    return "UNKNOWN";
    }
}

//=============================================
