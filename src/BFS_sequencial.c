/*ARQUIVO .C COM IMPLEMENTAÇÃO DO ALGORITMO BFS SEQUENCIAL*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/fila.h"
#include "../include/grafo.h"
#include "../include/BFS.h"

//========= FUNÇÕES PRINCIPAIS ================

void BFS_Sequencial(Graph *graph, int start) {
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

    freeIntVectors();
}

//=============================================

//========= MAIN ==============================

#ifndef DESATIVA_MAIN_BFS_SEQ
int main(int argc, char* argv[]) {
    //Dados
    char arquivo_entrada[STRING_MAX] = "tests/";

    int verticeInicial;

    //Coletando variáveis
    if (argc < 2) {
        printf("Erro! A chamada do programa deve seguir o padrão: <%s> <nome-do-arquivo-entrada>\n", argv[0]);
        exit(1);
    }
    else { //Montamos o caminho para arquivo
        strcat(arquivo_entrada, argv[1]);
    }

    verticeInicial = lerEntrada(arquivo_entrada);

    printGraph(graph);

    BFS_Sequencial(graph, verticeInicial);

    printBFS(graph);

    return 0;
}
#endif

//=============================================
