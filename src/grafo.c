/*ARQUIVO .C COM IMPLEMENTAÇÃO DE GRAFO*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "../include/grafo.h"

//========= INICIALIZAÇÃO ====================

Node* createNode(int id) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->id = id;
    return newNode;
}

Graph* createGraph(int amountVertices, GraphType type) {
    Graph *graph = (Graph*) malloc(sizeof(Graph));

    graph->amountVertices = amountVertices;
    graph->type = type;
    graph->adjList = (Node**) malloc(sizeof(Node*) * amountVertices);

    for (int i = 0; i < amountVertices; i++) {
        graph->adjList[i] = NULL;
    }

    return graph;
}

void freeGraph(Graph *graph) {
    if (graph == NULL) return;

    for (int i = 0; i < graph->amountVertices; i++) {
        Node* current = graph->adjList[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }

    free(graph->adjList);
    free(graph);
}

//=============================================


//========= FUNÇÕES PRINCIPAIS ================

void addEdge(Graph* graph, int origin, int destiny) {
    if(searchEdge(graph, origin, destiny) == true) return;
    
    //adiciona a aresta de origin -> destiny
    Node* newNode = createNode(destiny);
    newNode->next = graph->adjList[origin];
    graph->adjList[origin] = newNode;

    if(origin == destiny) return;
    
    //adiciona a aresta de destiny -> origin, mas apenas se o grafo for não direcionado  
    else if(graph->type == UNDIRECTED) {
        newNode = createNode(origin);
        newNode->next = graph->adjList[destiny];
        graph->adjList[destiny] = newNode;
    }
}

//=============================================

//========= OUTROS ============================

BOOL searchEdge(Graph* graph, int origin, int destiny) {
    Node* temp = graph->adjList[origin];
    while(temp) {
        if(temp->id == destiny) return true;
        temp = temp->next;
    }
    return false;
}

void printGraph(Graph* graph) {
    printf("====== GRAFO LIDO ==============");
    for(int i = 0; i < graph->amountVertices; i++) {
        Node* temp = graph->adjList[i];
        printf("\nVértice: %d: ", i);
        while(temp) {
            printf("[%d] -> ", temp->id);
            temp = temp->next;
        }
    }
    printf("\n====== FIM DO GRAFO ============\n\n");
} 

Graph* gerar_grafo_aleatorio(int vertices, int arestas) {
    Graph *grafo = createGraph(vertices, UNDIRECTED);
    int adicionadas = 0;

    // Garante conectividade mínima (cria um caminho entre todos os vértices)
    for (int i = 0; i < vertices - 1 && adicionadas < arestas; i++) {
        addEdge(grafo, i, i + 1);
        adicionadas++;
    }

    // Adiciona arestas aleatórias até atingir o total desejado
    srand((unsigned) time(NULL));
    int tentativas = 0, max_tentativas = arestas * 5;

    while (adicionadas < arestas && tentativas < max_tentativas) {
        int origem = rand() % vertices;
        int destino = rand() % vertices;

        if (origem != destino && !searchEdge(grafo, origem, destino)) {
            addEdge(grafo, origem, destino);
            adicionadas++;
        }

        tentativas++;
    }

    return grafo;
}

//=============================================
