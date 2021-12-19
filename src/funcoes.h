#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

typedef struct {
    int my_rank;
    int numThread;
    int lado;
    int **matA;
    int **matB;
    int **matC;
} Dados;

int** alocarMatriz(int LADO);

void preencherMatriz(int** matriz, int LADO, char *arquivo);

void imprResultados(int** matC, int LADO, char *arquivoC);

void matMult(int** A, int** B, int** C, int LADO);

#endif