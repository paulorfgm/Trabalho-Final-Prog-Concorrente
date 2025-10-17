#ifndef BFS_H
#define BFS_H

#include "graph.h"

//Defines the 3 colors a graph can have during BFS and DFS.
//Use of magical numbers is not ideal, but was the easiest solution.
typedef int COLOR;
#define WHITE 50
#define GREY 51
#define BLACK 52

/*GLOBAL VARIABLES DEFINITIONS*/
//I added the vectors relevant to the BFS algorithm as global variables
//So that I don`t need to pass them as arguments every time.

// Alternatively, we could use these vectors as "static" in .c, to simulate an object`s private attributes. 

extern COLOR *color;
extern int *parent;
extern int *distance;

/*FUNCTIONS*/

//Initialization
void freeIntVectors();
void initializeIntVectors(int size);
void initializeGraphBFS(Graph *graph); //Initializes the graph for BFS

//Main Functions
void BFS(Graph *graph, int start);

//Others
void printBFS(Graph* graph);
void printPath(Graph *g, int start, int end);
const char* colorToString(COLOR color);


#endif 