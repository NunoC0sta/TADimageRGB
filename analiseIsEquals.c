    #include "instrumentation.h"
    #include "imageRGB.h"
    #include <stdio.h>

    void TQTI(int tamanho){
        InstrName[0] = "comparisons";
        InstrCalibrate();

        // Tamanho para imagens quadradas
        int size = 4;

        // Criar duas imagens iguais
        Image img1 = ImageCreateChess(size, size, 2, 0xFF0000);
        Image img2 = ImageCreateChess(size, size, 2, 0xFF0000);

        // Resetar contadores antes da execução
        InstrReset();

        // Chamar a função que vamos medir
        int equal = ImageIsEqual(img1, img2);

        // Imprimir resultados
        printf("Comparação de Imagens iguais\n\n");
        printf("AS imagens de tamanho %dx%d são iguais? %s\n", size, size, equal ? "Sim" : "Não");
        InstrPrint();

        // Liberar memória
        ImageDestroy(&img1);
        ImageDestroy(&img2);
        printf("\n");
    }


    void TQTD(int tamanho1, int tamanho2){
        InstrName[0] = "comparisons";
        InstrCalibrate();

        // Criar duas imagens iguais
        Image img1 = ImageCreateChess(tamanho1, tamanho1, 2, 0xFF0000);
        Image img2 = ImageCreateChess(tamanho2, tamanho2, 2, 0xFF0000);

        // Resetar contadores antes da execução
        InstrReset();

        // Chamar a função que vamos medir
        int equal = ImageIsEqual(img1, img2);

        // Imprimir resultados
        printf("Comparação de Imagens iguais\n\n");
        printf("AS imagens de tamanho %dx%d  e %dx%d são iguais? %s\n", tamanho1, tamanho1, tamanho2, tamanho2, equal ? "Sim" : "Não");
        InstrPrint();

        // Liberar memória
        ImageDestroy(&img1);
        ImageDestroy(&img2);
        printf("\n");
    }

    int main() {
        int T1 = 4; //Mudar para alterar o Tamanho
        TQTI(T1);   //Teste Quadrados Tamanho Igual pattern Igual
        int T2 = 5; //Mudar para alterar o Tamanho
        TQTD(T1, T2); // Teste Quadrado Tamanho Diferente Cores Iguais
        


        return 0;
    }
