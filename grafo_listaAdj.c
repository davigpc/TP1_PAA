#include <stdio.h>
#include <stdlib.h>
#include "grafo_listaAdj.h"

/*                    inicializaGrafo (TipoGrafo* grafo, int numvertices): Cria um grafo com n vertices.

    Aloca espaco para o vetor de apontadores de listas de adjacencias e,
    para cada vertice, inicializa o apontador de sua lista de adjacencia.
    Retorna true se inicializou com sucesso e false caso contrario.


    vertices vao de 1 a numvertices.
*/

Grafo *inicializaGrafo(int numVertices, int numArestas, int numMenoresCaminhos)
{

    Grafo *grafo = (Grafo *)calloc(1, sizeof(Grafo));

    grafo->numVertices = numVertices;

    grafo->listaAdj = (Apontador *)calloc(numVertices + 2, sizeof(Apontador));

    // for num vert

    grafo->numArestas = numArestas;

    grafo->numMenoresCaminhos = numMenoresCaminhos;

    // calloc ja inicializa com zeros.... nao precisa inicializar grafo->listaAdj[i]

    return grafo;
}

bool verificaValidadeVertice(int v, Grafo *grafo)
{
    if (v > grafo->numVertices)
    {
        fprintf(stderr, "ERRO: Numero do vertice (%d) maior que o numero total de vertices (%d).\n", v, grafo->numVertices);
        return false;
    }

    if (v <= 0)
    {
        fprintf(stderr, "ERRO: Numero do vertice (%d) deve ser positivo.\n", v);
        return false;
    }

    return true;
}
bool listaAdjVazia(int v, Grafo *grafo)
{

    if (!verificaValidadeVertice(v, grafo))
        return false;

    return (grafo->listaAdj[v] == NULL);
}

Apontador proxListaAdj(int v, Grafo *grafo, Apontador atual)
{

    if (atual == NULL)
    {
        fprintf(stderr, "atual == NULL\n");
        return VERTICE_INVALIDO;
    }
    return (atual->prox);
}

void insereAresta(int v1, int v2, Peso peso, Grafo *grafo)
{

    Apontador p;

    if (!(verificaValidadeVertice(v1, grafo) && verificaValidadeVertice(v2, grafo)))
    {
        return;
    }
    if (!(p = (Apontador)calloc(1, sizeof(Aresta))))
    {
        fprintf(stderr, "ERRO: Falha na alocacao de memoria na funcao insereAresta\n");
        return;
    }
    p->vdestino = v2;
    p->peso = peso;
    p->prox = grafo->listaAdj[v1]; // insere no inicio
    grafo->listaAdj[v1] = p;
}

bool removeAresta(int v1, int v2, Grafo *grafo)
{

    Apontador q, anterior;

    if (!(verificaValidadeVertice(v1, grafo) && verificaValidadeVertice(v2, grafo)))
    {
        return ARESTA_NULA;
    }

    q = grafo->listaAdj[v1];

    while ((q != NULL) && (q->vdestino != v2))
    {
        anterior = q;
        q = q->prox;
    }

    if (q != NULL)
    {
        if (grafo->listaAdj[v1] == q)
        {
            grafo->listaAdj[v1] = q->prox;
        }
        else
        {
            anterior->prox = q->prox;
            //*peso = q->peso;
            free(q);
            q = NULL;
            return true;
        }
    }

    return false;
}

Apontador primeiroListaAdj(int v, Grafo *grafo)
{
    return (grafo->listaAdj[v]);
}

bool existeAresta(int v1, int v2, Grafo *grafo)
{

    Apontador q;

    if (!(verificaValidadeVertice(v1, grafo) && verificaValidadeVertice(v2, grafo)))
    {
        return false;
    }

    q = grafo->listaAdj[v1];

    while ((q != NULL) && (q->vdestino != v2))
    {
        q = q->prox;
    }

    if (q != NULL)
    {
        return true;
    }

    return false;
}

Apontador encontraAresta(int v1, int v2, Grafo *grafo)
{

    Apontador q;

    if (!(verificaValidadeVertice(v1, grafo) && verificaValidadeVertice(v2, grafo)))
    {
        return NULL;
    }

    q = grafo->listaAdj[v1];

    while ((q != NULL) && (q->vdestino != v2))
    {
        q = q->prox;
    }

    if (q != NULL)
    {
        return q;
    }

    return NULL;
}

void liberaGrafo(Grafo *grafo)
{

    int v;
    Apontador p;

    for (v = 0; v <= grafo->numVertices + 1; v++)
    {

        while ((p = grafo->listaAdj[v]) != NULL)
        {

            grafo->listaAdj[v] = p->prox;
            p->prox = NULL;
            free(p);
        }
    }

    grafo->numVertices = 0;
    free(grafo->listaAdj);
    grafo->listaAdj = NULL;
}

void imprimeGrafo(char *nomearq, Grafo *grafo)
{

    FILE *fp;
    int v;
    Apontador p;

    fp = fopen(nomearq, "w");

    if (fp == NULL)
    {
        fprintf(stderr, "ERRO: falha ao abrir arquivo.\n");
        return;
    }

    for (v = 1; v <= grafo->numVertices; v++)
    {
        p = grafo->listaAdj[v];
        while (p != NULL)
        {
            fprintf(fp, "%d ---> %d\n", v, p->vdestino);
            p = p->prox;
        }
    }
}

Grafo *leGrafo(char *nomearq)
{
    FILE *fp;
    int numVertices, numArestas, numMenoresCaminhos;
    int v1, v2;
    Peso peso;

    fp = fopen(nomearq, "r");

    if (fp == NULL)
    {
        fprintf(stderr, "ERRO: falha ao abrir arquivo.\n");
        return (NULL);
    }

    if (fscanf(fp, "%d %d %d", &numVertices, &numArestas, &numMenoresCaminhos) != 3)
    {
        fprintf(stderr, "ERRO: numero de argumentos de entrada invalido.\n");
        return (NULL);
    }

    Grafo *grafo = inicializaGrafo(numVertices, numArestas, numMenoresCaminhos);

    for (int i = 1; i <= grafo->numArestas; i++)
    {
        if (fscanf(fp, "%d %d %d", &v1, &v2, &peso) != 3)
        {
            fprintf(stderr, "ERRO 1: numero de argumentos de entrada invalido.\n");
        }
        insereAresta(v1, v2, peso, grafo);
    }

    return grafo;
}

Peso obtemPesoAresta(int v1, int v2, Grafo *grafo)
{
    Apontador p;

    p = encontraAresta(v1, v2, grafo);

    if (p == NULL)
    {
        fprintf(stderr, "ERRO: numero de argumentos de entrada invalido.\n");
        return (ARESTA_NULA);
    }

    return (p->peso);
}
