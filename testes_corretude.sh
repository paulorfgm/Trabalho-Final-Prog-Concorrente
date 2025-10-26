# Compila e executa o teste de corretude do BFS concorrente
gcc -Wall -Wextra -std=c11 -pthread -O2 -lrt \
	src/BFS.c src/grafo.c src/fila.c src/BFS_sequencial.c src/BFS_concorrente.c \
	src/teste_corretude.c -Iinclude \
	-o bin/teste_corretude \
	-DDESATIVA_MAIN_BFS_SEQ -DDESATIVA_MAIN_BFS_CONC
bin/teste_corretude > tests/teste_corretude.txt