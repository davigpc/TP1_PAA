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

    // Heap *heap = criaHeap(grafo->numVertices);
    // imprimeHeap(heap);
    imprimeGrafo(argv[2], grafo);
    caminhoTotal = dijkstra(grafo);
    printf("%d \n", caminhoTotal);

    liberaGrafo(grafo);

    return 0;
}