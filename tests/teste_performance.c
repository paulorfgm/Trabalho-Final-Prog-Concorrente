#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/grafo.h"
#include "../include/BFS.h"
#include "timer.h"

extern Graph *graph;
extern COLOR *color;
extern int *parent;
extern int *distance;

void BFS_Sequencial(Graph *graph, int start);
void BFS_Concorrente(int inicio, int num_threads);

typedef struct {
    int vertices;
    int arestas;
    int threads_testar[10];
    int qtd_threads;
} CasoPerformance;

int main(void) {
    CasoPerformance casos[] = {
        {100, 250, {1, 2, 4}, 3},                    // Caso 1: Pequeno Esparso
        {100, 4000, {1, 2, 4}, 3},                   // Caso 2: Pequeno Denso
        {1000, 5000, {1, 2, 4, 8}, 4},               // Caso 3: Médio Esparso
        {1000, 400000, {1, 2, 4, 8, 12}, 5},         // Caso 4: Médio Denso
        {100000, 500000, {1, 2, 4, 8, 12, 16}, 6},   // Caso 5: Médio Esparso
        {100000, 5000000, {1, 2, 4, 8, 12, 16}, 6},  // Caso 6: Médio Denso
        {1000000, 5000000, {1, 2, 4, 8, 12, 16}, 6}, // Caso 7: Grande Esparso
        {1000000, 10000000, {1, 2, 4, 8, 12, 16}, 6} // Caso 8: Grande Denso
    };

    const int quantidade_casos = sizeof(casos) / sizeof(casos[0]);
    const int repeticoes = 5;

    printf("=================================================================\n");
    printf("TESTES DE PERFORMANCE - BFS SEQUENCIAL vs CONCORRENTE\n");
    printf("Grafos Aleatórios (média de %d execuções)\n", repeticoes);
    printf("=================================================================\n\n");

    for (int i = 0; i < quantidade_casos; i++) {
        CasoPerformance *caso = &casos[i];

        printf("-----------------------------------------------------------------\n");
        printf("Caso %d/%d: Grafo com %d vértices e %d arestas\n",
               i + 1, quantidade_casos, caso->vertices, caso->arestas);
        printf("-----------------------------------------------------------------\n");

        Graph *grafo = gerar_grafo_aleatorio(caso->vertices, caso->arestas);
        if (!grafo) {
            fprintf(stderr, "ERRO: Falha ao gerar grafo para o caso %d\n", i + 1);
            continue;
        }

        double tempo_seq_total = 0.0;

        // --- BFS SEQUENCIAL (média de N execuções)
        for (int r = 0; r < repeticoes; r++) {
            double inicio, fim;
            graph = grafo;
            GET_TIME(inicio);
            BFS_Sequencial(grafo, 0);
            GET_TIME(fim);
            double tempo_exec = fim - inicio;
            tempo_seq_total += tempo_exec;
        }
        double tempo_seq_medio = tempo_seq_total / repeticoes;
        printf("Sequencial:  %.6f segundos (média de %d execuções)\n",
               tempo_seq_medio, repeticoes);

        // --- BFS CONCORRENTE (para cada número de threads)
        for (int t = 0; t < caso->qtd_threads; t++) {
            int num_threads = caso->threads_testar[t];
            double tempo_conc_total = 0.0;

            for (int r = 0; r < repeticoes; r++) {
                double inicio, fim;
                graph = grafo;
                GET_TIME(inicio);
                BFS_Concorrente(0, num_threads);
                GET_TIME(fim);
                double tempo_exec = fim - inicio;
                tempo_conc_total += tempo_exec;
            }

            double tempo_conc_medio = tempo_conc_total / repeticoes;
            double aceleracao = tempo_seq_medio / tempo_conc_medio;
            double eficiencia = aceleracao / num_threads;
            printf("  %2d threads: %.6f segundos (aceleracao: %.2f) (eficiencia: %.2f)\n",
                   num_threads, tempo_conc_medio, aceleracao, eficiencia);
        }

        freeGraph(grafo);
        printf("\n");
    }

    printf("=================================================================\n");
    printf("Testes de performance concluídos\n");
    printf("=================================================================\n");

    return 0;
}
