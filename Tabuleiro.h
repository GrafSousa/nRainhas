#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define COM_RAINHA 0
#define SEM_RAINHA 1

#define FALSE 0
#define TRUE 1

#define MODO_ANALISE 1
typedef struct Tabuleiro{
    int tamanho;
    int **tabuleiro;
    int linha;
    int coluna;
    int solucoes;
    int usados;
    int descartados;
    int tentativas;
    int modo_analise;

}Tabuleiro;

void setTabuleiro(Tabuleiro *tabuleiro, int tamanho, int modo_analise);
void colocaRainha(Tabuleiro *tabuleiro);
void imprimeTabuleiro( Tabuleiro *tabuleiro );
void imprimeTabuleiro2(Tabuleiro *tabuleiro);
void imprimeResultado(Tabuleiro *tabuleiro);
int seguro( Tabuleiro *tabuleiro);


