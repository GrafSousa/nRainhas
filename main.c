#include "Tabuleiro.h"

int main()
{
    int tamanho = 0;
    int modoAnalise = 0;
    Tabuleiro tabuleiro;

    printf("Entre com o tamanho do tabuleiro: ");
    scanf("%d", &tamanho);
    printf("Voce deseja o modo analise ativado ?\n1 - SIM\n2 - NAO\nSua resposta: ");
    scanf("%d", &modoAnalise);

    if( modoAnalise != 1 )
        modoAnalise = 0;

    setTabuleiro(&tabuleiro, tamanho, modoAnalise);
    colocaRainha(&tabuleiro);
    imprimeResultado(&tabuleiro);
    //imprimeTabuleiro(&tabuleiro);
    return 0;
}
