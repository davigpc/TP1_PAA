#include <stdio.h>
#include <stdlib.h>
#include "grafo_listaAdj.h"


/*                    inicializaGrafo (TipoGrafo* grafo, int numvertices): Cria um grafo com n vertices.                                                      
                                                                                                                                    
    Aloca espaco para o vetor de apontadores de listas de adjacencias e,
    para cada vertice, inicializa o apontador de sua lista de adjacencia.
    Retorna true se inicializou com sucesso e false caso contrario.


    vertices vao de 1 a numvertices.                                                                                                                                                        
*/                                                                                                                         
                                                                                                                                                     
bool inicializaGrafo(Grafo *grafo, int numVertices){
    int i;

    if (numVertices <= 0) {
        fprintf(stderr, "ERRO na chamada de inicializaGrafo: Numero de vertices deve ser positivo.\n");
        return false;
    }

    grafo->numVertices = numVertices;
    if (!(grafo->listaAdj = (Apontador*) calloc(numVertices+1, sizeof(Apontador)))) {
        fprintf(stderr, "ERRO: Falha na alocacao de memoria na funcao inicializaGrafo\n");
        return false;
    }

    grafo->numArestas = 0;

    //calloc ja inicializa com zeros.... nao precisa inicializar grafo->listaAdj[i]

    return true;
}

bool verificaValidadeVertice(int v, Grafo* grafo){
    
    
}

bool listaAdjVazia(int v, Grafo* grafo){

    if (!verificaValidadeVertice(v, grafo))
        return false;

    return (grafo->listaAdj[v] == NULL);
}

Aresta* proxListaAdj(int v, Grafo* grafo, Aresta* atual){
    
    if(atual == NULL){
        fprintf(stderr, "atual == NULL\n");
        return VERTICE_INVALIDO;
    }
    return(atual->prox);
}

void insereAresta(int v1, int v2, Peso peso, Grafo *grafo){
    
    Apontador p;

    if(!(verificaValidadeVertice(v1, grafo) && verificaValidadeVertice(v2, grafo))){
        return;
    }
    if(!(p = (Apontador) calloc(1, sizeof(Aresta)))){
        fprintf(stderr, "ERRO: Falha na alocacao de memoria na funcao insereAresta\n");
        return;
    }
    p->vdestino = v2;
    p->peso = peso;
    p->prox = grafo->listaAdj[v1]; // insere no inicio
    grafo->numArestas++;

}

bool removeArestaObtendoPeso(int v1, int v2, Peso* peso, Grafo* grafo){
    Apontador q, anterior;

    if(!(verificaValidadeVertice(v1, grafo) && verificaValidadeVertice(v2, grafo))){
        return ARESTA_NULA;
    }

    q = grafo->listaAdj[v1];

    while(( q != NULL) && (q->vdestino != v2)){
        anterior = q;
        q = q->prox;
    }

    if(q != NULL){
        if(grafo->listaAdj[v1] == q){
            grafo->listaAdj[v1] = q->prox;
        }
        else {
            anterior->prox = q->prox;
            *peso = q->peso;
            free(q);
            q = NULL;
            return true;
        }
    }

    return false;
}

void liberaGrafo(Grafo* grafo){

    int v;
    Apontador p;

    for(v = 0; v <= grafo->numVertices; v++){

        while((p = grafo->listaAdj[v]) != NULL){

            grafo->listaAdj[v] = p->prox;
            p->prox = NULL;
            free(p);
        }
    }

    grafo->numVertices = 0;
    free(grafo->listaAdj);
    grafo->listaAdj = NULL;
}

