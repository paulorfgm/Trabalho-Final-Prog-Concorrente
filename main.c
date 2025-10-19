#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/graph.h"
#include "include/BFS.h"
#include "include/queue.h"

//Define para o grafo ser direcionado (DIRECTED) ou não direcionado (UNDIRECTED)
#define DIRECTION UNDIRECTED

#define STRING_MAX 100

//Função para leitura dos casos de teste
//Entrada: nome do arquivo .txt, e ponteiro para o grafo
//Saída: vertice inicial, com grafo alterado (referência)
int lerEntrada(char* arquivo_entrada, Graph **graph) {
    FILE *arquivo = fopen(arquivo_entrada, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    
    printf("====== LEITURA DO ARQUIVO ======\n");

    int V, E;
    fscanf(arquivo, "%d %d", &V, &E);
    printf("Vértices: %d, Arestas: %d\n", V, E);

    *graph = createGraph(V, DIRECTION);
    
    int origem, destino;
    for (int i = 0; i < E; i++) {
        fscanf(arquivo, "%d %d", &origem, &destino);
        addEdge(*graph, origem, destino);
        printf("(%d, %d)\n", origem, destino);
    }

    int verticeInicial;
    fscanf(arquivo, "%d", &verticeInicial);
    printf("Vertice inicial: %d\n", verticeInicial);

    printf("====== FIM DA LEITURA ==========\n\n");

    fclose(arquivo);

    return verticeInicial;
}

int main(int argc, char* argv[]) {
    //Dados
    char arquivo_entrada[STRING_MAX] = "tests/";

    Graph *graph;
    int verticeInicial;

    //Coletando variáveis
    if (argc < 2) {
        printf("Erro! A chamada do programa deve seguir o padrão: <%s> <nome-do-arquivo-entrada>\n", argv[0]);
        exit(1);
    }
    else { //Montamos o caminho para arquivo
        strcat(arquivo_entrada, argv[1]);
    }

    verticeInicial = lerEntrada(arquivo_entrada, &graph);

    printGraph(graph);

    BFS(graph, verticeInicial);

    printBFS(graph);

    return 0;
}