#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <time.h>
#include "grafo_listaAdj.h"
#include "heap.h"
#include "eppstein.h"
#include "tempo.h"

int main(int argc, char *argv[3])
{

    struct rusage inicio, fim;
    struct timeval inicioRelogio, fimRelogio;

    Grafo *grafo = leGrafo(argv[1]);

    getrusage(RUSAGE_SELF, &inicio);
    gettimeofday(&inicioRelogio, NULL);

    imprimeMenoresCaminhos(argv[2], grafo);

    gettimeofday(&fimRelogio, NULL);
    getrusage(RUSAGE_SELF, &fim);

    imprimeTempos(argv[3], &inicio, &fim, &inicioRelogio, &fimRelogio);

    liberaGrafo(grafo);

    return 0;
}