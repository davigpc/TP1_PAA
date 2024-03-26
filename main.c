#include <stdio.h>
#include <stdlib.h>
#include "grafo_listaAdj.h"
#include "heap.h"
#include "dijkstra.h"

int main(int argc, char *argv[2])
{
    int *numMenoresCaminhos;
    numMenoresCaminhos = (int *)malloc(1 * sizeof(int));

    int caminhoTotal;

    Grafo *grafo = leGrafo(argv[1], numMenoresCaminhos);
    imprimeGrafo(argv[2], grafo);
    liberaGrafo(grafo);
    caminhoTotal = dijkstra(grafo);

    return 0;
}