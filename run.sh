# gcc src/BFS.c src/graph.c src/queue.c main.c -o bin/bfs.exe -Wall
# bin/./bfs.exe teste_entrada.txt

gcc src/BFS_Conc.c src/BFS.c src/graph.c src/queue.c -o bin/bfs_conc.exe -Wall
bin/./bfs_conc.exe teste_entrada.txt 16