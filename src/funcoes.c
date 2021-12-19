#include "funcoes.h"


int** alocarMatriz(int LADO) {
    /* Alocação de matrizes pelo método de ponteiros
    em linhas contíguas. Mantendo toda a matriz
    alocada contínuamente na memória 
    (Ps: para matrizes quadráticas usamos apenas um lado,
    caso queira lados diferentes o mesmo pode ser definido
    com a adição do mesmo nos parâmetros da função)*/
    int** matriz;

    //Primeiramente alocamos uma primeira linha.
    matriz = malloc(LADO * sizeof(int*));
    /* E assim, podemos só definir o primeiro ponteiro com o tamanho
    de toda a matriz, que pode depois serem ajustados de acordo com
    os elementos as outras "colunas" ao lado da primeira linha */

    /* E aqui ajustamos, definindo cada elemento da primeira linha
    como uma coluna da matriz. Como podemos ver, cada "coluna"
    é definida como um intervalo de (i * Lado), que é justamente
    a quantidade de elementos em cada coluna. */
    int i;
    matriz[0] = malloc( (LADO * LADO) * sizeof(int));

    for(i = 1; i < LADO; i++)
        matriz[i] = matriz[0] + i * LADO;



    return matriz;
}

    /* 
        Função para o preenchimento das matrizes
        lendo para o nome de arquivo dado.
    */
void preencherMatriz(int** matriz, int lado, char *arquivo) {
    int i, j;
    FILE *fin;
    fin = fopen(arquivo, "r");
    if(fin == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", arquivo);
        exit(1);
    }
    int lin, col;
    fscanf(fin, "%d %d%*c", &lin, &col);
    for(i = 0; i < lado; i++) {
        for(j = 0; j < lado; j++) {
            fscanf(fin, "%d", &matriz[i][j]);
        }
    }
    fclose(fin);
}

    /* Recebe matrizes A, B e C. 
    Realizando a multiplicação
    A x B = C */
void matMult(int** A, int** B, int** C, int LADO) {
    int i, j, k;
    for(i = 0; i < LADO; i++) {
        for(j = 0; j < LADO; j++) {
            for(k = 0; k < LADO; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

    /* Imprime os resultados da matrizC */
void imprResultados(int** matC, int LADO, char *arquivo) {
    int i, j;
    FILE *fout;
    fout = fopen(arquivo, "w");
    if(fout == NULL) {
        fprintf(stderr, "Erro ao criar o arquivo %s\n", arquivo);
        exit(1);
    }
    fprintf(fout, "%d %d\n", LADO, LADO);

    for(i = 0; i < LADO; i++) {
        for(j = 0; j < LADO; j++) {
            fprintf(fout, "%d ", matC[i][j]);
        }
        fprintf(fout, "\n");
    }
    fclose(fout);
}
