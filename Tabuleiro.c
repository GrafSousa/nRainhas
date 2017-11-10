#include "Tabuleiro.h"

void setTabuleiro( Tabuleiro *tabuleiro, int tamanho, int modo_analise ){
    int i = 0 , j = 0;
    int count = 0;

    tabuleiro ->tamanho = tamanho;
    tabuleiro ->linha = 0;
    tabuleiro ->coluna = 0;
    tabuleiro ->solucoes = 0;
    tabuleiro ->usados = 0;
    tabuleiro ->descartados = 0;
    tabuleiro ->tentativas = 0;
    tabuleiro ->modo_analise = modo_analise;
    tabuleiro ->tabuleiro = (int **)malloc(tabuleiro ->tamanho * sizeof(int *));
    if( tabuleiro ->tabuleiro == NULL ){
        printf("** Erro: Memoria insuficiente **\n");
        return(NULL);
    }
    //Aloca número de colunas
    for( i = 0; i < tabuleiro ->tamanho; i++ ){
        tabuleiro ->tabuleiro[i] = (int *)malloc( tabuleiro ->tamanho * sizeof(int));
        if(tabuleiro ->tabuleiro[i] == NULL ){
            printf("** Erro: Memoria Insuficiente **");
            return(NULL);
        }
    }


    for( i = 0; i < tabuleiro ->tamanho; i++ ){
        for( j = 0; j < tabuleiro ->tamanho; j++ ){
            tabuleiro ->tabuleiro[i][j] = SEM_RAINHA;
        }
    }

}

int seguro( Tabuleiro *tabuleiro){
    int i = 0, j = 0;
    for( i = 0; i < tabuleiro ->tamanho; i++ ){
        if( tabuleiro ->tabuleiro[tabuleiro ->linha][i] == COM_RAINHA){
            tabuleiro ->tentativas = tabuleiro ->tentativas + 1;
            return FALSE;
        }

    }
    //verifica a coluna
    for( i = 0; i < tabuleiro ->tamanho; i++ ){
        if( tabuleiro ->tabuleiro[i][tabuleiro ->coluna] == COM_RAINHA){
            tabuleiro ->tentativas = tabuleiro ->tentativas + 1;
            return FALSE;
        }

    }

    for( i = tabuleiro ->linha, j = tabuleiro ->coluna; i >= 0 && j >= 0; i--, j--){
        if( tabuleiro ->tabuleiro[i][j] == COM_RAINHA ){
            tabuleiro ->tentativas = tabuleiro ->tentativas + 1;
            return FALSE;
        }

    }
    for( i = tabuleiro ->linha; i < tabuleiro ->tamanho; i++ ){
        for( j = tabuleiro ->coluna; j < tabuleiro ->tamanho; j++ ){
            if( tabuleiro ->tabuleiro[i][j] == COM_RAINHA ){
                tabuleiro ->tentativas = tabuleiro ->tentativas + 1;
                return FALSE;
            }
        }
    }

    for( i = tabuleiro ->linha, j = tabuleiro ->coluna; i >= 0 && j < tabuleiro ->tamanho; i--, j++){
        if( tabuleiro ->tabuleiro[i][j] == COM_RAINHA ){
            tabuleiro ->tentativas = tabuleiro ->tentativas + 1;
            return FALSE;
        }

    }
    for( i = tabuleiro ->linha, j = tabuleiro ->coluna; i < tabuleiro ->tamanho && j >= 0; i++, j--){
        if( tabuleiro ->tabuleiro[i][j] == COM_RAINHA ){
            tabuleiro ->tentativas = tabuleiro ->tentativas + 1;
            return FALSE;
        }

    }
    return TRUE;
}

void colocaRainha(Tabuleiro *tabuleiro ){
    int linha = 0, coluna = 0;
    if( tabuleiro ->coluna == tabuleiro ->tamanho ){
        tabuleiro ->solucoes++;
        tabuleiro ->descartados = tabuleiro ->descartados - 1;
        imprimeTabuleiro(tabuleiro);
        return;
    }

    for( tabuleiro ->linha = 0; tabuleiro ->linha < tabuleiro ->tamanho; tabuleiro ->linha++ ){
        if( seguro(tabuleiro) ){
            //insere a rainha
            tabuleiro ->tabuleiro[tabuleiro ->linha][tabuleiro ->coluna] = COM_RAINHA;
            tabuleiro ->usados = tabuleiro ->usados + 1;
            linha = tabuleiro ->linha;
            coluna = tabuleiro ->coluna;
            //move uma coluna
            tabuleiro ->coluna = tabuleiro ->coluna + 1;
            colocaRainha(tabuleiro);
            tabuleiro ->linha = linha;
            tabuleiro ->coluna = coluna;
            tabuleiro ->tabuleiro[ tabuleiro ->linha][tabuleiro ->coluna] = SEM_RAINHA;
            tabuleiro ->descartados = tabuleiro ->descartados + 1;
            tabuleiro ->usados = tabuleiro ->usados -1;

        }

    }
}

void imprimeTabuleiro2(Tabuleiro *tabuleiro){
    int i = 0, j = 0;

    for( i = 0; i < tabuleiro ->tamanho; i++ ){
        for( j = 0; j <tabuleiro ->tamanho; j++ ){
            printf("%d ", tabuleiro ->tabuleiro[i][j]);
        }
        printf("\n");
    }
}

void imprimeTabuleiro( Tabuleiro *tabuleiro ){
    FILE *file;
    char inicioArquivo[20] = "solucao-";
    char fimArquivo[20] = "-Rainhas.txt";
    char tamTab[100];
    char *nomeFinal;
    int i = 0, j = 0;


    snprintf(tamTab, 20, "%d", tabuleiro ->tamanho);
    strcat(inicioArquivo, tamTab);
    nomeFinal = strcat(inicioArquivo, fimArquivo);
    file = fopen(nomeFinal, "a+");

    fprintf(file, "%s %d", "Solucao:", tabuleiro ->solucoes);
    fprintf(file, "%s", "\n");

    for( i = 0; i < tabuleiro ->tamanho; i++ ){
        for( j = 0; j < tabuleiro ->tamanho; j++){
            if( tabuleiro ->tabuleiro[i][j] == COM_RAINHA ){
                fprintf(file, "%s", "|R");
            }
            else{
                fprintf(file, "%s", "|_");
            }
        }
        fprintf(file, "%s", "|");
        fprintf(file, "%s", "\n");
    }
    if( tabuleiro ->descartados < 0)
        tabuleiro ->descartados = 0;

    fprintf(file, "%s %d", "Total de usadas:", tabuleiro ->usados);
    fprintf(file, "%s", "\n");
    fprintf(file, "%s %d", "Total de descartadas:", tabuleiro ->descartados);
    fprintf(file, "%s", "\n");
    if( tabuleiro ->modo_analise == MODO_ANALISE ){
        fprintf(file, "%s %d", "Total de tentativas:", tabuleiro ->tentativas);
        fprintf(file, "%s %s", "\n", "\n");
    }


    //tabuleiro ->usados = 0;
    tabuleiro ->descartados = 0;
    tabuleiro ->descartados = (tabuleiro ->descartados - tabuleiro ->tamanho) + 1;
    tabuleiro ->tentativas = 0;
}

void imprimeResultado(Tabuleiro *tabuleiro){

    FILE *file;
    char inicioArquivo[20] = "solucao-";
    char fimArquivo[20] = "-Rainhas.txt";
    char tamTab[100];
    char *nomeFinal;
    int i = 0, j = 0;


    snprintf(tamTab, 20, "%d", tabuleiro ->tamanho);
    strcat(inicioArquivo, tamTab);
    nomeFinal = strcat(inicioArquivo, fimArquivo);
    file = fopen(nomeFinal, "a+");

    printf("\nFoi criado um arquivo com as solucoes chamado: %s\n", nomeFinal );

}
