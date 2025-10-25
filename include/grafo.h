/*HEADER PARA DEFINIÇÕES DE GRAFO*/
#ifndef GRAPH_H
#define GRAPH_H

/*DEFINIÇÕES DE TIPOS*/
typedef int BOOL;
#define true 1
#define false 0

typedef int GraphType; //se um grafo é direcionado ou não
#define DIRECTED 26
#define UNDIRECTED 27

/*DEFINIÇÕES DE ESTRUTURA DE GRAFO*/
typedef struct Node {
    int id; 
    struct Node* next;
} Node;

typedef struct Graph {
    int amountVertices;
    GraphType type;
    Node** adjList;
} Graph;

/*DEFINIÇÕES DAS FUNÇÕES DE GRAFO*/

//*1. Funções de Inicialização

//cria o vértice de um grafo
Node* createNode(int id);

//cria um grafo vazio com amountVertices vértices, de tipo type
Graph* createGraph(int amountVertices, GraphType type);

//libera o espaço de memória do grafo
void freeGraph(Graph *graph);

//*2. Funções Principais

//adiciona uma aresta origin -> destiny para o grafo
void addEdge(Graph* graph, int origin, int destiny); 

//*3. Funções Auxiliares

//indica se uma aresta existe ou não no grafo
BOOL searchEdge(Graph* graph, int origin, int destiny); 

//mostra o grafo
void printGraph(Graph* graph);

#endif