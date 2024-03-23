#ifndef GRAFO_LISTAADJ.H
#define GRAFO_LISTAADJ.H

#include <stdbool.h>


#define VERTICE_INVALIDO NULL
#define ARESTA_NULA -1

typedef int Peso;

typedef struct str_aresta{
    int vdestino;
    Peso peso;
    struct str_aresta* prox;
} Aresta;

typedef Aresta* Apontador;

typedef struct {
    Apontador* listaAdj;
    int numVertices;
    int numArestas;

} Grafo;

bool inicializaGrafo(Grafo*, int);

bool verificaValidadeVertice(int, Grafo*);

bool listaAdjVazia(int, Grafo*);

void insereAresta(int, int, Peso, Grafo*);

bool removeArestaObtendoPeso(int, int, Peso*, Grafo*);

void liberaGrafo(Grafo*);

#endif
