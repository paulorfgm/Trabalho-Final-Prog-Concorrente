# Compila e executa BFS sequencial
gcc src/fila.c src/grafo.c src/BFS.c src/BFS_sequencial.c -o bin/bfs_sequencial.out -Wall
bin/bfs_sequencial.out teste_entrada.txt

# Compila e executa BFS concorrente
gcc src/fila.c src/grafo.c src/BFS.c src/BFS_concorrente.c -o bin/bfs_concorrente.out -Wall
bin/bfs_concorrente.out teste_entrada.txt 2

# Compila e executa o teste de corretude do BFS concorrente
gcc -Wall -Wextra -std=c11 -pthread -O2 \
	src/BFS.c src/grafo.c src/fila.c src/BFS_sequencial.c src/BFS_concorrente.c \
	tests/test_corretude.c -Iinclude \
	-o bin/test_corretude \
	-DDESATIVA_MAIN_BFS_SEQ -DDESATIVA_MAIN_BFS_CONC
bin/test_corretude

# Compila e executa o teste de corretude do BFS concorrente vs BFS sequencial
echo "==============================="
gcc -Wall -Wextra -std=c11 -pthread -O2 \
	src/BFS.c src/grafo.c src/fila.c src/BFS_sequencial.c src/BFS_concorrente.c \
	tests/test_performance.c -Iinclude \
	-o bin/test_performance \
	-DDESATIVA_MAIN_BFS_SEQ -DDESATIVA_MAIN_BFS_CONC
bin/test_performance