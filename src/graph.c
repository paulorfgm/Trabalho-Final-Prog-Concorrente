#include <stdlib.h>
#include <stdio.h>

#include "../include/graph.h"

//========= Initialization ====================

Node* createNode(int id, int weight) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->id = id;
    newNode->weight = weight;
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

//=============================================


//========= Main Functions ====================

bool searchEdge(Graph* graph, int origin, int destiny) {
    Node* temp = graph->adjList[origin];
    while(temp) {
        if(temp->id == destiny) return true;
        temp = temp->next;
    }
    return false;
}

//adds the edge if it does not already exist
void addEdge(Graph* graph, int origin, int destiny, int weight) {
    if(searchEdge(graph, origin, destiny) == true) return;
    
    //adds from origin -> destiny
    Node* newNode = createNode(destiny, weight);
    newNode->next = graph->adjList[origin];
    graph->adjList[origin] = newNode;

    if(origin == destiny) return;
    
    else if(graph->type == UNDIRECTED) {
        //adds from destiny -> origin only if the graph is undirected    
        newNode = createNode(origin, weight);
        newNode->next = graph->adjList[destiny];
        graph->adjList[destiny] = newNode;
    }
}

//=============================================



//========= Others ============================

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

void printGraph(Graph* graph) {
    for(int i = 0; i < graph->amountVertices; i++) {
        Node* temp = graph->adjList[i];
        printf("\nVertex %d: ", i);
        while(temp) {
            printf("[%d] -> ", temp->id);
            temp = temp->next;
        }
    }
    printf("\n\n");
} 

//=============================================
