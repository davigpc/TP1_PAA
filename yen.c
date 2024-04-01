#include "yen.h"
#include <stdio.h>
#include <stdlib.h>

Caminhos *criaCaminhos(int qtdCaminhos)
{
    Caminhos *caminhos = (Caminhos *)calloc(1, sizeof(Caminhos));
    caminhos->caminhos = (Caminho **)calloc(qtdCaminhos, sizeof(Caminho *));
    caminhos->qtdCaminhos = 0;
}

Caminhos *yen(char *nomearqLeitura, Grafo *grafo)
{
    Caminhos *menoresCaminhos = criaCaminhos(grafo->numMenoresCaminhos);
    Caminhos *candidatos = criaCaminhos(grafo->numMenoresCaminhos);
    Vertice spurVertice;
    Vertice proxSpurVertice;
    Caminho *caminhoRaiz;
    Caminho *caminhoSpur;
    Caminho *caminhoTotal;

    for (int i = 0; i < grafo->numMenoresCaminhos; i++)
    {
        menoresCaminhos->caminhos[i] = criaVetorCaminho(grafo->numVertices);
    }

    for (int i = 0; i < grafo->numMenoresCaminhos; i++)
    {
        candidatos->caminhos[i] = criaVetorCaminho(grafo->numVertices);
    }

    menoresCaminhos->caminhos[0] = dijkstra(grafo, 1);
    menoresCaminhos->qtdCaminhos = 1;

    for (int i = 1; i < grafo->numMenoresCaminhos; i++)
    {
        for (int j = 0; j < menoresCaminhos->caminhos[i - 1]->tamCaminho - 1; j++)
        {
            spurVertice = menoresCaminhos->caminhos[i - 1]->vertices[j];
            proxSpurVertice = menoresCaminhos->caminhos[i - 1]->vertices[j + 1];

            // caminhoRaiz = função que coloca o caminho até o spur node
            caminhoRaiz = copiaCaminho(grafo, menoresCaminhos->caminhos[i - 1], spurVertice.id);

            for (int k = 0; k < menoresCaminhos->qtdCaminhos; k++)
            {
                if (verificaCaminhosIguais(grafo, caminhoRaiz, menoresCaminhos->caminhos[k]))
                {
                    removeAresta(spurVertice.id, proxSpurVertice.id, grafo);
                }
            }

            removeVerticesCaminho(grafo, caminhoRaiz);

            caminhoSpur = dijkstra(grafo, spurVertice.id);

            if (spurPathVazio(caminhoSpur))
            {
                continue;
            }

            caminhoTotal = juntaCaminhos(grafo, caminhoRaiz, caminhoSpur, spurVertice.id);

            if (!existeCaminhoCandidato(candidatos, caminhoTotal, grafo))
            {
                ordenaCandidatos(candidatos);
                if (candidatos->qtdCaminhos == grafo->numMenoresCaminhos)
                {
                    if (caminhoTotal->pesoCaminho < candidatos->caminhos[grafo->numMenoresCaminhos - 1]->pesoCaminho)
                    {
                        candidatos->caminhos[grafo->numMenoresCaminhos - 1]->pesoCaminho = caminhoTotal->pesoCaminho;
                    }
                }
                else
                {
                    candidatos->caminhos[candidatos->qtdCaminhos]->pesoCaminho = caminhoTotal->pesoCaminho;
                }
            }

            liberaGrafo(grafo);
            grafo = leGrafo(nomearqLeitura);
        }

        if (candidatos->caminhos[0]->vertices == NULL)
        {
            break;
        }

        ordenaCandidatos(candidatos);

        menoresCaminhos->caminhos[i] = candidatos->caminhos[0];
        menoresCaminhos->qtdCaminhos++;
    }

    return menoresCaminhos;
}

Caminho *copiaCaminho(Grafo *grafo, Caminho *caminhoOriginal, int destino)
{

    Caminho *novoCaminho = criaVetorCaminho(caminhoOriginal->tamCaminho);

    Peso pesoCaminho = 0;

    for (int i = 0; i < caminhoOriginal->tamCaminho; i++)
    {
        novoCaminho->vertices[i] = caminhoOriginal->vertices[i];

        if (i > 0) // o primeiro nao tem vertice pai
        {
            pesoCaminho += obtemPesoAresta(caminhoOriginal->vertices[i].idVerticePai, caminhoOriginal->vertices[i].id, grafo);
        }

        if (caminhoOriginal->vertices[i].id == destino)
        {
            novoCaminho->pesoCaminho = pesoCaminho;
            novoCaminho->tamCaminho = i + 1;
            break;
        }
    }
    return novoCaminho;
}

bool verificaCaminhosIguais(Grafo *grafo, Caminho *caminhoRaiz, Caminho *caminhoOriginal)
{
    int contador = 0;

    for (int i = 0; i < caminhoRaiz->tamCaminho; i++)
    {
        if (caminhoRaiz->vertices[i].id == caminhoOriginal->vertices[i].id)
        {
            contador++;
        }
    }

    if (contador == caminhoRaiz->tamCaminho)
    {
        return true;
    }

    return false;
}

void removeVerticesCaminho(Grafo *grafo, Caminho *caminhoRaiz)
{
    Apontador p;
    int indice;

    for (int i = 0; i < caminhoRaiz->tamCaminho - 1; i++)
    {
        indice = caminhoRaiz->vertices[i].id;
        while ((p = grafo->listaAdj[indice]) != NULL)
        {

            grafo->listaAdj[indice] = p->prox;
            p->prox = NULL;
            free(p);
        }
    }
}

bool spurPathVazio(Caminho *caminhoSpur)
{

    if (caminhoSpur->tamCaminho == 0)
    {
        return true;
    }

    return false;
}

Caminho *juntaCaminhos(Grafo *grafo, Caminho *caminhoRaiz, Caminho *caminhoSpur, int destino)
{

    Caminho *novoCaminho = criaVetorCaminho(caminhoRaiz->tamCaminho + caminhoSpur->tamCaminho - 1); //-1 pois o spurVertice aparece nos dois caminhos

    Peso pesoCaminho = 0;

    for (int i = 0; i < caminhoRaiz->tamCaminho; i++)
    {
        novoCaminho->vertices[i] = caminhoRaiz->vertices[i];

        if (i > 0)
        {
            pesoCaminho += obtemPesoAresta(caminhoRaiz->vertices[i].idVerticePai, caminhoRaiz->vertices[i].id, grafo);
        }

        if (caminhoRaiz->vertices[i].id == destino)
        {
            novoCaminho->pesoCaminho = pesoCaminho;
            novoCaminho->tamCaminho = i + 1;
            break;
        }
    }

    for (int i = caminhoRaiz->tamCaminho; i < caminhoRaiz->tamCaminho + caminhoSpur->tamCaminho - 1; i++)
    {
        novoCaminho->vertices[i] = caminhoSpur->vertices[i];
        pesoCaminho += obtemPesoAresta(caminhoSpur->vertices[i].idVerticePai, caminhoSpur->vertices[i].id, grafo);
        novoCaminho->tamCaminho = i + 1;
    }

    return novoCaminho;
}

void ordenaCandidatos(Caminhos *candidatos)
{
    int i, j;
    Caminho *chave;

    for (i = 1; i < candidatos->qtdCaminhos; i++)
    {

        chave = candidatos->caminhos[i];
        j = i - 1;

        while (j >= 0 && candidatos->caminhos[j]->pesoCaminho > chave->pesoCaminho)
        {
            candidatos->caminhos[j + 1] = candidatos->caminhos[j];
            j = j - 1;
        }
        candidatos->caminhos[j + 1] = chave;
    }
}

bool existeCaminhoCandidato(Caminhos *candidatos, Caminho *caminhoTotal, Grafo *grafo)
{
    bool comparador = false;

    for (int i = 0; i < candidatos->qtdCaminhos; i++)
    {
        if (verificaCaminhosIguais(grafo, caminhoTotal, candidatos->caminhos[i]))
        {
            comparador = true;
        }
    }
    return comparador;
}

void imprimeMenoresCaminhos(char *nomearqLeitura, char *nomearqEscrita, Grafo *grafo)
{
    Caminhos *menoresCaminhos = yen(nomearqLeitura, grafo);
    FILE *fp;

    fp = fopen(nomearqEscrita, "w");

    if (fp == NULL)
    {
        fprintf(stderr, "ERRO: falha ao abrir arquivo.\n");
        return;
    }

    for (int i = 0; i < menoresCaminhos->qtdCaminhos; i++)
    {
        fprintf(fp, "%d ", menoresCaminhos->caminhos[i]->pesoCaminho);
    }
    fprintf(fp, "\n");
}