# Globais

- Grafo G
    - V
    - Tipo (direcionado ou não)
    - Lista de Adjacência 
- Nível Atual L
- Vetor de Cores
- Vetor de Pais
- Vetor de Distância


# Funções

BFS_conc():
    IncializaBFS -> pode ser concorrente também 
    Cria Fila_L
    Coloca vértice inicial em Fila_L
    Enquanto (Fila_L não estiver vazia):
        Cria Fila_{L+1}
        --> Manda sinal para threads processarem 
        --> Lock até receber sinal de concluído

ProcessaNível(Fila_L, Fila_{L+1}):
    - LOCK(L)
    - Se Fila_L estiver vazia, bloqueia a thread -> "dorme"
    - Caso contrário, pega o primeiro vértice x da Fila_L
    - UNLOCK(L)

    - Para cada vizinho de x
      - LOCK(L+1)
      - Se a cor de x for branca, troca x para cor_?
      - Atualiza pai 
      - Atualiza distancia = L + 1
      - Coloca x em Fila_{L+1}
      - UNLOCK(L+1)

