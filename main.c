#include <stdio.h>
#include <stdlib.h>

#include "include/graph.h"
#include "include/BFS.h"
#include "include/queue.h"

int main() {
    Graph *graph = createGraph(10, DIRECTED);
    int weight = 0;

    addEdge(graph, 7, 8, weight);
    addEdge(graph, 8, 9, weight);
    addEdge(graph, 9, 7, weight);
    addEdge(graph, 6, 9, weight);
    addEdge(graph, 6, 1, weight);
    addEdge(graph, 1, 5, weight);
    addEdge(graph, 5, 6, weight);
    addEdge(graph, 4, 5, weight);
    addEdge(graph, 3, 4, weight);
    addEdge(graph, 2, 3, weight);
    addEdge(graph, 4, 2, weight);

    printGraph(graph);

    BFS(graph, 6);

    printBFS(graph);

    return 0;
}