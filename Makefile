all: programa

run: programa
		@./programa

programa: main.o grafo_listaAdj.o heap.o eppstein.o
		gcc -g main.o grafo_listaAdj.o heap.o eppstein.o -o programa


main.o: main.c
		gcc -c main.c -g

grafo_listaAdj.o: grafo_listaAdj.c grafo_listaAdj.h
		gcc -c grafo_listaAdj.c -g

heap.o: heap.c heap.h grafo_listaAdj.h
		gcc -c heap.c -g

eppstein.o: eppstein.c eppstein.h heap.h grafo_listaAdj.h
		gcc -c eppstein.c -g

clean:
		rm *.o programa*
