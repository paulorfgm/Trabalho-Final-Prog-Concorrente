# Compila e executa BFS sequencial
gcc src/fila.c src/grafo.c src/BFS.c src/BFS_sequencial.c -o bin/bfs_sequencial.out -Wall
bin/bfs_sequencial.out teste_entrada.txt