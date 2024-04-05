#ifndef TEMPO_H
#define TEMPO_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>
#include <time.h>

float tempoUsuario(struct rusage *, struct rusage *);
float tempoSistema(struct rusage *, struct rusage *);
float tempoRelogio(struct timeval *, struct timeval *);

void imprimeTempos(char *, struct rusage *, struct rusage *, struct timeval *, struct timeval *);

#endif