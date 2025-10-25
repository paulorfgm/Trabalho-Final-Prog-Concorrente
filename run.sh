gcc src/fila.c src/grafo.c src/BFS.c src/BFS_sequencial.c -o bin/bfs_sequencial.out -Wall
bin/./bfs_sequencial.out teste_entrada.txt

gcc src/fila.c src/grafo.c src/BFS.c src/BFS_concorrente.c -o bin/bfs_concorrente.out -Wall
bin/./bfs_concorrente.out teste_entrada.txt 2