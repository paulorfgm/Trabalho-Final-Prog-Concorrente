# Compila e executa o teste de corretude do BFS concorrente vs BFS sequencial
gcc -Wall -Wextra -std=c11 -pthread -O2 -lrt \
	src/BFS.c src/grafo.c src/fila.c src/BFS_sequencial.c src/BFS_concorrente.c \
	src/teste_performance.c -Iinclude \
	-o bin/teste_performance \
	-DDESATIVA_MAIN_BFS_SEQ -DDESATIVA_MAIN_BFS_CONC
for i in {1..3}; do
    bin/teste_performance > tests/teste_performance_$i.txt
done