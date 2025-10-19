#ifndef GRAPH_H
#define GRAPH_H

typedef int bool;
#define true 1
#define false 0

/*
OBS: os vértices do grafo começarão no 0
*/


//Define se o grafo é direcionado ou não direcionado.
typedef int GraphType;
#define DIRECTED 26
#define UNDIRECTED 27

/*STRUCTURES DEFINITIONS*/

typedef struct Node {
    int id; 
    struct Node* next;
} Node;

typedef struct Graph {
    int amountVertices;
    GraphType type;
    Node** adjList;
} Graph;

/*FUNCTIONS*/

//Initialization
Node* createNode(int id);
Graph* createGraph(int amountVertices, GraphType type);

//Main Functions
bool searchEdge(Graph* graph, int origin, int destiny); //retorna 1 se encontrar a aresta, e 0 se não encontrar. 
void addEdge(Graph* graph, int origin, int destiny); //adiciona a aresta, se ela não existir.

//Others
void freeGraph(Graph *graph);
void printGraph(Graph* graph);

#endif