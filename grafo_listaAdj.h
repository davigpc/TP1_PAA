#ifndef GRAFO_LISTAADJ_H
#define GRAFO_LISTAADJ_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define VERTICE_INVALIDO NULL
#define ARESTA_NULA -1
#define PESO_MAXIMO 9999

typedef int Peso;

typedef struct str_aresta
{

    int vdestino;
    Peso peso;
    struct str_aresta *prox;

} Aresta;

typedef Aresta *Apontador;

typedef struct
{

    Apontador *listaAdj;
    int numVertices;
    int numArestas;
    int numMenoresCaminhos;

} Grafo;

Grafo *inicializaGrafo(int, int, int);

bool verificaValidadeVertice(int, Grafo *);

bool listaAdjVazia(int, Grafo *);

Apontador proxListaAdj(int, Grafo *, Apontador);

void insereAresta(int, int, Peso, Grafo *);

bool removeAresta(int, int, Grafo *);

Apontador primeiroListaAdj(int, Grafo *);

bool existeAresta(int, int, Grafo *);

Apontador encontraAresta(int, int, Grafo *);

void liberaGrafo(Grafo *);

void imprimeGrafo(char *, Grafo *);

Grafo *leGrafo(char *);

Peso obtemPesoAresta(int, int, Grafo *);

#endif
