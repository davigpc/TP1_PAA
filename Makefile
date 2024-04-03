all: programa

run: programa
		@./programa

programa: main.o grafo_listaAdj.o heap.o dijkstra.o yen.o
		gcc -g main.o grafo_listaAdj.o heap.o dijkstra.o yen.o -o programa


main.o: main.c
		gcc -c main.c -g

grafo_listaAdj.o: grafo_listaAdj.c grafo_listaAdj.h
		gcc -c grafo_listaAdj.c -g

heap.o: heap.c heap.h grafo_listaAdj.h
		gcc -c heap.c -g

dijkstra.o: dijkstra.c dijkstra.h heap.h grafo_listaAdj.h
		gcc -c dijkstra.c -g

yen.o: yen.c yen.h dijkstra.h heap.h grafo_listaAdj.h
		gcc -c yen.c -g

clean:
		rm *.o programa*
