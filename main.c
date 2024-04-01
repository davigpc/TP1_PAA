#include <stdio.h>
#include <stdlib.h>
#include "grafo_listaAdj.h"
#include "heap.h"
#include "dijkstra.h"
#include "yen.h"

int main(int argc, char *argv[2])
{
    Grafo *grafo = leGrafo(argv[1]);

    imprimeMenoresCaminhos(argv[1], argv[2], grafo);

    liberaGrafo(grafo);

    return 0;
}