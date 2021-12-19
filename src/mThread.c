#include "mThread.h"
#include "funcoes.h"

void *Pth_matMult(void* dados_th) {
    Dados *dados = (Dados*)dados_th;
    
    int lado_local = dados->lado/dados->numThread;
    int primeira_linha = dados->my_rank * lado_local;
    int ultima_linha = (dados->my_rank + 1) * lado_local;

    int i, j, k;
    for(i = primeira_linha; i < ultima_linha; i++) {
        for(j = 0; j < dados->lado; j++) {
            for(k = 0; k < dados->lado; k++) {
                dados->matC[i][j] += dados->matA[i][k] * dados->matB[k][j];
            }
        }
    }

    return NULL;
}