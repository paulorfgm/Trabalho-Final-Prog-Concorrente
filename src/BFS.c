#include <stdlib.h>
#include <stdio.h>

#include "../include/BFS.h"
#include "../include/queue.h"

// COLOR *color;
// int *parent;
// int *distance;

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


//Inicializa o Grafo para o BFS
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
    //Inicializa o Grafo
    initializeGraphBFS(graph);

    //Insere os valores iniciais para os vetores
    color[start] = GREY;
    distance[start] = 0;

    //Inicializa a fila
    Queue* queue = createQueue();
    enqueue(queue, start);

    //Loop principal do BFS
    while(!isEmpty(queue)) {
        int vertex = dequeue(queue);

        //Loop do vértice em específico
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
    printf("--> BFS: \n");
    printf("\n");
    for(int i = 0; i < graph->amountVertices; i++) {
        printf("Vertex: %d - Color: %s - Father: %d - Distance: %d\n", i, colorToString(color[i]), parent[i], distance[i]);
    }
}

//retorna um caminho de start ate end, se encontrar um. 
//G deve ser um grafo que já passou pelo BFS
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
