#include "funcoes.h"
#include "mThread.h"
#include <sys/time.h>
#include <string.h>
#include <ctype.h>


/* Defina: Número de Threads para execução. */
#define NumeroThreads 4

/* USO: ./Programa N M
    N = Lado da matriz quadrática
    M = Modo: S - Sequencial
              C - Concorrente
*/

int main(int argc, char* argv[]) {
    /* Criando as variaveis para threads, numero de threads
    e alocações diversas respetivamente... */
    struct timeval start, stop;

    if(argc != 3) {
        fprintf(stderr, "USO: ./programa <NumThreads> <LadoMatriz>\n");
        return 1;
    }

    int lado = strtol(argv[1], NULL, 10);
    char modo = toupper(argv[2][0]);

    if(modo != 'C' && modo != 'S') {
        fprintf(stderr, "Modo inválido, use 'S' ou 'C' para Sequêncial ou Concorrente\n");
        return 1;
    }

    int **matA = NULL;
    int **matB = NULL;
    int **matC = NULL;
    fflush(stdout);


    matA = alocarMatriz(lado);
    matB = alocarMatriz(lado);
    matC = alocarMatriz(lado);

    /* Caminho de diretório de arquivos */
    char caminho[] = "Matrizes/";
    /* Processamento de strings */
    char arquivoA[32] = "";
    char arquivoB[32] = "";
    char arquivoC[32] = "";
    strcat(arquivoA, caminho);
    strcat(arquivoA, "A");
    strcat(arquivoB, caminho);
    strcat(arquivoB, "B");
    strcat(arquivoC, "Resultados/");
    strcat(arquivoC, "C");

    char buff[10];
    sprintf(buff, "%dx%d", lado, lado);
    strcat(arquivoA, buff);
    strcat(arquivoA, ".txt");
    strcat(arquivoB, buff);
    strcat(arquivoB, ".txt");
    strcat(arquivoC, buff);
    if(modo == 'S') {
        strcat(arquivoC, "_S_.txt");
    } else if(modo == 'C') {
        strcat(arquivoC, "_C_.txt");
    }

    preencherMatriz(matA, lado, arquivoA);
    preencherMatriz(matB, lado, arquivoB);

    /* Zerando matC para garantir resultado */
    int i, j;
    for(i = 0; i < lado; i++) {
        for(j = 0; j < lado; j++) {
            matC[i][j] = 0;
        }
    }
    
    gettimeofday(&start, 0);
    /* Multiplicação de A x B */
    if(modo == 'S') {
        
        matMult(matA, matB, matC, lado);
    } else if(modo == 'C') {
        Dados dados[NumeroThreads];
        pthread_t* threads;
        threads = malloc(NumeroThreads * sizeof(pthread_t));
        
        int  th;
        for(th = 0; th < NumeroThreads; th++) {
            dados[th].lado = lado;
            dados[th].matA = matA;
            dados[th].matB = matB;
            dados[th].matC = matC;
            dados[th].my_rank = th;
            dados[th].numThread = NumeroThreads;
            pthread_create( &threads[th], NULL,
                        Pth_matMult, (void*) &dados[th]);
        }

        for(th = 0; th < NumeroThreads; th++) {
            pthread_join(threads[th], NULL);
        }

        free(threads);
    }
    gettimeofday(&stop, 0);

    /* Impressão de resultados */
    imprResultados(matC, lado, arquivoC);


    /* Impressão de tempo */
    FILE *fout;
	char outputFilename[] = "Pth_Registro_Mat.txt";
	fout = fopen(outputFilename, "a");
	if(fout == NULL) {
		fprintf(stderr, "Can't open output file %s!\n", outputFilename);
		exit(1);
	}

	fprintf(fout, "\t%1.4e ", (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec));
	
	fclose(fout);

    free(matA[0]);
    free(matB[0]);
    free(matC[0]);
    free(matA);
    free(matB);
    free(matC);
    return 0;
}