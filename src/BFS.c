#include <stdlib.h>
#include <stdio.h>

#include "../include/BFS.h"
#include "../include/queue.h"

/*
Compile:
gcc source/BFS.c source/graph.c resource/queue.c main.c -o bin/BFS.exe -Wall

Run:
bin/.\BFS.exe

*/

COLOR *color;
int *parent;
int *distance;

//========= Initialization ====================

void freeIntVectors() {
    free(color);
    free(parent);
    free(distance);
}

void initializeIntVectors(int size) {
    freeIntVectors();
    color = (int *) malloc (sizeof(int) * size);
    parent = (int *) malloc (sizeof(int) * size);
    distance = (int *) malloc (sizeof(int) * size);
}


//Initializes the graph for BFS
void initializeGraphBFS(Graph *graph) {
    initializeIntVectors(graph->amountVertices);
    for (int i = 0; i < graph->amountVertices; i++) {
        color[i] = WHITE;
        parent[i] = -1;
        distance[i] = -1;
    }
}

//=============================================

//========= Main Functions ====================

void BFS(Graph *graph, int start) {
    //Initialize the graph
    initializeGraphBFS(graph);

    //Initialization of the starting vertex
    color[start] = GREY;
    distance[start] = 0;

    //Initialization of the queue
    Queue* queue = createQueue();
    enqueue(queue, start);

    //Main Loop
    while(!isEmpty(queue)) {
        int vertex = dequeue(queue);

        //Loop of the specific vertex
        Node *temp = graph->adjList[vertex];
        while (temp) {
            if (color[temp->id] == WHITE) {
                color[temp->id] = GREY;
                distance[temp->id] = distance[vertex] + 1;
                parent[temp->id] = vertex;

                enqueue(queue, temp->id);
            } 
            temp = temp->next;
        }
    
        color[vertex] = BLACK;
    }    
}

//=============================================

//========= Others ============================

void printBFS(Graph* graph) {
    printf("\n");
    for(int i = 0; i < graph->amountVertices; i++) {
        printf("Vertex: %d - Color: %s - Father: %d - Distance: %d\n", i, colorToString(color[i]), parent[i], distance[i]);
    }
}

//returns a path from start to end if it finds one. 
//G must be a graph that has already passed through BFS
void printPath(Graph *graph, int start, int end) {
    if (start == end) printf("\n\nPrinting Path:\n[%d] ", start);
    else if (parent[end] == -1) printf("There is no path between [%d] and [%d]", start, end);
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
