#include "yen.h"
#include <stdio.h>
#include <stdlib.h>

Caminhos *criaCaminhos(int qtdCaminhos)
{
    Caminhos *caminhos = (Caminhos *)calloc(1, sizeof(Caminhos));
    caminhos->caminhos = (Caminho **)calloc(qtdCaminhos, sizeof(Caminho *));
    caminhos->qtdCaminhos = 0;
    return caminhos;
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

    menoresCaminhos->caminhos[0] = dijkstra(grafo, 1);
    menoresCaminhos->qtdCaminhos = 1;

    for (int i = 1; i < grafo->numMenoresCaminhos; i++)
    {
        for (int j = 0; j < menoresCaminhos->caminhos[i - 1]->tamCaminho - 1; j++)
        {
            spurVertice = menoresCaminhos->caminhos[i - 1]->vertices[j];

            // caminhoRaiz = função que coloca o caminho até o spur node
            caminhoRaiz = copiaCaminho(grafo, menoresCaminhos->caminhos[i - 1], spurVertice.id);

            for (int k = 0; k < menoresCaminhos->qtdCaminhos; k++)
            {
                if (verificaCaminhosIguais(grafo, caminhoRaiz, menoresCaminhos->caminhos[k]))
                {
                    proxSpurVertice = menoresCaminhos->caminhos[k]->vertices[j + 1];
                    removeAresta(spurVertice.id, proxSpurVertice.id, grafo);
                }
            }

            caminhoSpur = dijkstra(grafo, spurVertice.id);

            liberaGrafo(grafo);
            grafo = leGrafo(nomearqLeitura);

            if (caminhoSpur == NULL)
            {
                free(caminhoRaiz->vertices);
                free(caminhoRaiz);
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
                        candidatos->caminhos[grafo->numMenoresCaminhos - 1] = caminhoTotal;
                        candidatos->qtdCaminhos++;
                        caminhoTotal = caminhoRaiz;
                    }
                }
                else
                {
                    candidatos->caminhos[candidatos->qtdCaminhos] = caminhoTotal;
                    candidatos->qtdCaminhos++;
                    caminhoTotal = caminhoRaiz;
                }
            }

            else
            {
                free(caminhoTotal->vertices);
                free(caminhoTotal);
            }

            free(caminhoRaiz->vertices);
            free(caminhoRaiz);

            free(caminhoSpur->vertices);
            free(caminhoSpur);
        }

        if (candidatos->caminhos[0]->vertices == NULL)
        {
            break;
        }

        ordenaCandidatos(candidatos);

        menoresCaminhos->caminhos[i] = candidatos->caminhos[0];
        menoresCaminhos->qtdCaminhos++;

        removePrimeiroCandidato(candidatos);
    }

    liberaCaminhos(candidatos);

    liberaGrafo(grafo);

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
            pesoCaminho += obtemPesoAresta(caminhoOriginal->vertices[i].verticePai, caminhoOriginal->vertices[i].id, grafo);
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
    int indice;

    for (int i = 0; i < caminhoRaiz->tamCaminho - 1; i++)
    {
        indice = caminhoRaiz->vertices[i].id;

        grafo->listaAdj[indice] = NULL;
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
    }

    for (int i = caminhoRaiz->tamCaminho; i < caminhoRaiz->tamCaminho + caminhoSpur->tamCaminho - 1; i++)
    {
        novoCaminho->vertices[i] = caminhoSpur->vertices[i - (caminhoRaiz->tamCaminho - 1)];
    }

    novoCaminho->tamCaminho = caminhoRaiz->tamCaminho + caminhoSpur->tamCaminho - 1;
    novoCaminho->pesoCaminho = caminhoRaiz->pesoCaminho + caminhoSpur->pesoCaminho;
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
        fprintf(fp, "%lld ", menoresCaminhos->caminhos[i]->pesoCaminho);
    }
    fprintf(fp, "\n");

    liberaCaminhos(menoresCaminhos);

    fclose(fp);
}

void removePrimeiroCandidato(Caminhos *candidatos)
{

    for (int b = 0; b < candidatos->qtdCaminhos - 1; b++)
    {
        candidatos->caminhos[b] = candidatos->caminhos[b + 1];
    }

    candidatos->qtdCaminhos--;
}

void imprimeCandidatos(FILE *fp, Caminhos *candidatos)
{
    for (int i = 0; i < candidatos->qtdCaminhos; i++)
    {
        fprintf(fp, "%lld ", candidatos->caminhos[i]->pesoCaminho);
    }
    fprintf(fp, "\n");
}

void liberaCaminhos(Caminhos *caminhos)
{
    for (int i = 0; i < caminhos->qtdCaminhos; i++)
    {
        free(caminhos->caminhos[i]->vertices);
        free(caminhos->caminhos[i]);
    }
    free(caminhos->caminhos);
    free(caminhos);
}