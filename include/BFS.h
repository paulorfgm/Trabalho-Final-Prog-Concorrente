#ifndef BFS_H
#define BFS_H

#include "graph.h"

//Define as três cores que um grafo pode ter durante o BFS. 
typedef int COLOR;
#define WHITE 50
#define GREY 51
#define BLACK 52

/*GLOBAL VARIABLES DEFINITIONS*/
//Variáveis para o BFS adicionadas como globais, para não ter que passar como argumetno
//Toda vez. 
extern COLOR *color;
extern int *parent;
extern int *distance;

/*FUNCTIONS*/

//Initialization
void freeIntVectors();
void initializeIntVectors(int size);
void initializeGraphBFS(Graph *graph); //Inicializa o grafo para o BFS

//Main Functions
void BFS(Graph *graph, int start);

//Others
void printBFS(Graph* graph);
void printPath(Graph *g, int start, int end);
const char* colorToString(COLOR color);


#endif 