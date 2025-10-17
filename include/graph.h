#ifndef GRAPH_H
#define GRAPH_H

typedef int bool;
#define true 1
#define false 0

//Defines if a graph is directed or undirected.
//Use of magical numbers is not ideal, but was the easiest solution.
typedef int GraphType;
#define DIRECTED 26
#define UNDIRECTED 27

/*STRUCTURES DEFINITIONS*/

typedef struct Node {
    int id, weight; //weight = data
    struct Node* next;
} Node;

typedef struct Graph {
    int amountVertices;
    GraphType type;
    Node** adjList;
} Graph;

/*FUNCTIONS*/

//Initialization
Node* createNode(int id, int weight);
Graph* createGraph(int amountVertices, GraphType type);

//Main Functions
bool searchEdge(Graph* graph, int origin, int destiny); //returns 1 if it finds the edge, and 0 if it does not
void addEdge(Graph* graph, int origin, int destiny, int weight); //adds the edge if it does not already exist

//Others
void freeGraph(Graph *graph);
void printGraph(Graph* graph);

#endif