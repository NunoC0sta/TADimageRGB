    #include "instrumentation.h"
    #include "imageRGB.h"
    #include <stdio.h>

    void TQTI(int tamanho){
        InstrName[0] = "comparisons";
        InstrCalibrate();

        Image img1 = ImageCreateChess(tamanho, tamanho, 2, 0xFF0000);
        Image img2 = ImageCreateChess(tamanho, tamanho, 2, 0xFF0000);

        InstrReset();

        int equal = ImageIsEqual(img1, img2);

        printf("Comparação de Imagens iguais\n\n");
        printf("AS imagens de tamanho %dx%d são iguais? %s\n", tamanho, tamanho, equal ? "Sim" : "Não");
        InstrPrint();

        ImageDestroy(&img1);
        ImageDestroy(&img2);
        printf("\n");
    }


    void TQTD(int tamanho1, int tamanho2){
        InstrName[0] = "comparisons";
        InstrCalibrate();

        Image img1 = ImageCreateChess(tamanho1, tamanho1, 2, 0xFF0000);
        Image img2 = ImageCreateChess(tamanho2, tamanho2, 2, 0xFF0000);

        InstrReset();

        int equal = ImageIsEqual(img1, img2);

        printf("Comparação de Imagens Com Tamanhos Diferentes\n\n");
        printf("AS imagens de tamanho %dx%d  e %dx%d são iguais? %s\n", tamanho1, tamanho1, tamanho2, tamanho2, equal ? "Sim" : "Não");
        InstrPrint();

        ImageDestroy(&img1);
        ImageDestroy(&img2);
        printf("\n");
    }

    void TQTICD(int tamanho){
        InstrName[0] = "comparisons";
        InstrCalibrate();

        Image img1 = ImageCreateChess(tamanho, tamanho, 2, 0xFF0000);
        Image img2 = ImageCreateChess(tamanho, tamanho, 2, 0xFF0001);

        InstrReset();

        int equal = ImageIsEqual(img1, img2);

        printf("Comparação de Imagens com Tamanhos Iguais e Cores Diferentes\n\n");
        printf("AS imagens de tamanho %dx%d e cores %d e %d são iguais? %s\n", tamanho, tamanho, 0xFF0000, 0xFF0001, equal ? "Sim" : "Não");
        InstrPrint();

        //ImageDestroy(&img1);
        //ImageDestroy(&img2);
        printf("\n");
    }

    void TQTDCD (int tamanho1, int tamanho2){
        InstrName[0] = "comparisons";
        InstrCalibrate();

        Image img1 = ImageCreateChess(tamanho1, tamanho1, 2, 0xFF0000);
        Image img2 = ImageCreateChess(tamanho2, tamanho2, 2, 0xFF0001);

        InstrReset();

        int equal = ImageIsEqual(img1, img2);

        printf("Comparação de Imagens Com tamanhos Diferentes e Cores Diferentes\n\n");
        printf("AS imagens de tamanho %dx%d e %dx%d e cores %d e %d são iguais? %s\n", tamanho1, tamanho1, tamanho2, tamanho2, 0xFF0000, 0xFF0001, equal ? "Sim" : "Não");
        InstrPrint();

        ImageDestroy(&img1);
        ImageDestroy(&img2);
        printf("\n");
    }

    int main() {
        int T1 = 12000; //Mudar para alterar o Tamanho
        int T2 = 5; //Mudar para alterar o Tamanho

        TQTI(T1);   //Teste Quadrados Tamanho Igual pattern Igual
        TQTD(T1, T2); // Teste Quadrado Tamanho Diferente Cores Iguais
        TQTICD(T1); // Teste Quadrados Tamanhos Iguais Cores Diferentes
        TQTDCD(T1, T2); // Teste Quadrados Tamanhos Diferentes e Cores Diferentes



        return 0;
    }


    // Isto aqui tá só para eu me ir orientando com a Análise da Função
    // Melhor Caso: Alturas Diferentes (1 Comparação)
    // Pior Caso: Imagens Iguais (4+Altura da Imagem (Algoritmo Analisa Imagem linha a linha e não pixel a pixel))