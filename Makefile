all: programa

run: programa
		@./programa

programa: main.o grafo_listaAdj.o
		gcc -g main.o grafo_listaAdj.o -o programa


main.o: main.c
		gcc -c main.c -g

grafo_listaAdj.o: grafo_listaAdj.c grafo_listaAdj.h
		gcc -c grafo_listaAdj.c -g

clean:
		rm *.o programa*
