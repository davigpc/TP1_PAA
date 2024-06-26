all: programa

run: programa
		@./programa

programa: main.o grafo_listaAdj.o heap.o tempo.o
		gcc -g main.o grafo_listaAdj.o heap.o tempo.o -o programa

main.o: main.c
		gcc -c main.c -g

grafo_listaAdj.o: grafo_listaAdj.c grafo_listaAdj.h heap.c heap.h
		gcc -c grafo_listaAdj.c -g

heap.o: heap.c heap.h grafo_listaAdj.h
		gcc -c heap.c -g

tempo.o: tempo.c tempo.h
		gcc -c tempo.c -g

clean:
		rm *.o programa*
