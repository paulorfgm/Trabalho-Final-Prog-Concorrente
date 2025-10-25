/*HEADER PARA DEFINIÇÕES DE FUNÇÕES AUXILIARES DO ALGORITMO BFS*/
#ifndef BFS_H
#define BFS_H

/*INCLUINDO HEADERS AUXILIARES*/
#include "grafo.h"

/*DEFINIÇÕES DE TIPOS*/
typedef int COLOR; //possíveis cores que um vértice assume ao decorrer do BFS
#define WHITE 50
#define GREY 51
#define BLACK 52

#define DIRECTION UNDIRECTED //tipo do grafo "base" para o algoritmo
#define STRING_MAX 100 //tamanho máximo do arquivo de entrada

/*DEFINIÇÕES DE VARIÁVEIS GLOBAIS*/
extern COLOR *color;
extern int *parent;
extern int *distance;
extern Graph *graph;

/*DEFINIÇÕES DAS FUNÇÕES DO BFS*/
//*1. Funções de Inicialização

//inicializa os espaços de memória dos três vetores que são variáveis globais:
//color, parent, e distance
void initializeIntVectors(int size);

//libera os espaços de memória dos três vetores globais
void freeIntVectors();

//prepara o grafo para execução do BFS
void initializeGraphBFS(Graph *graph);

//*2. Funções de Leitura de Arquivo

//faz a leitura do arquivo de entrada arquivo_entrada
//retorna o vértice pelo qual o BFS deve iniciar
int lerEntrada(char* arquivo_entrada);

//*3. Funções Auxiliares

//mostra o grafo após a execução do BFS
void printBFS(Graph* graph);

//mostra um caminho do grafo começando em "start" e indo até "end"
//só funciona com um grafo que já passou pelo BFS
void printPath(Graph *g, int start, int end);

//converte o inteiro associado a uma cor para a string correspondente
const char* colorToString(COLOR color);

#endif 