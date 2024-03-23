#include <stdio.h>
#include <stdlib.h>
#include "grafo_listaAdj.h"

int main(int argc, char *argv[2])
{
    int *numMenoresCaminhos;
    numMenoresCaminhos = (int *)malloc(1 * sizeof(int));

    Grafo *grafo = leGrafo(argv[1], numMenoresCaminhos);
    imprimeGrafo(argv[2], grafo);
    liberaGrafo(grafo);

    return 0;
}