#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>
#include <bits/getopt_core.h>

#include "grafo_listaAdj.h"
#include "heap.h"
#include "tempo.h"



int main(int argc, char *argv[3])
{

    FILE* input_file = NULL;
    FILE* output_file = stderr;
    char c;
    while((c = getopt(argc, argv, "i:o:")) != -1) {
        switch (c) {
            case 'i':
                input_file = fopen(optarg, "r");
                if(!input_file) printf("Falha ao abrir arquivo %s\n", optarg);
                break;
            case 'o':
                output_file = fopen(optarg, "w");
                if(!output_file) printf("Falha ao abrir arquivo %s\n", optarg);
                break;
            default:
                ;;
        }
    }
    Grafo *grafo = leGrafo(argv[1]);
    imprimeMenoresCaminhos(argv[2], grafo);


    return 0;
}