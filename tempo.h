#ifndef TEMPO_H
#define TEMPO_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

typedef struct {

    struct rusage rtime;
    struct timeval tv;

} tempo;

tempo tempoAtual();

double tempoDecorrido(struct timeval inicio, struct timeval fim);

void imprimeTempos(tempo inicio, tempo fim);


#endif