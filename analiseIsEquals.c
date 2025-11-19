#include "instrumentation.h"
#include "imageRGB.h"
#include <stdio.h>
#include <stdlib.h>

// Função auxiliar que testa duas imagens e imprime o resultado
void CompareImages(Image img1, Image img2, const char* descricao) {
    InstrName[0] = "comparisons";
    InstrCalibrate();

    InstrReset();
    int equal = ImageIsEqual(img1, img2);

    printf("%s\n\n", descricao);
    printf("As imagens são iguais? %s\n", equal ? "Sim" : "Não");
    InstrPrint();
    printf("\n");
}

// Função para alterar pixels de maneira controlada
void AlterPixel(Image img, int x, int y, rgb_t cor) {
    // Substituir pelo código real da função que altera pixels
    // Ex: ImageSetPixel(img, x, y, cor);
}

// Função que gera descrições automáticas para alterações
void GenerateAlteredTests(Image img1, Image img2, int size, const char* tipoAlteracao) {
    char desc[200];
    sprintf(desc, "Imagem %dx%d com %s", size, size, tipoAlteracao);
    CompareImages(img1, img2, desc);
}

void RunAllTests() {
    // Tamanhos quadrados
    int sizes_square[] = {1, 5, 50, 500, 5000, 12000};
    int n_square = sizeof(sizes_square) / sizeof(sizes_square[0]);

    // Tamanhos retangulares
    int rects[][2] = {{1,2}, {2,1}, {5,10}, {10,5}, {50,100}, {100,50}, {500,1000}, {1000,500}, {12000,6000}, {6000,12000}};
    int n_rect = sizeof(rects) / sizeof(rects[0]);

    // --- Testes básicos quadrados iguais ---
    for(int i=0; i<n_square; i++){
        int t = sizes_square[i];
        Image img1 = ImageCreateChess(t, t, 1, 0xFF0000);
        Image img2 = ImageCreateChess(t, t, 1, 0xFF0000);
        char desc[200];
        sprintf(desc, "Imagens quadradas iguais (%dx%d)", t, t);
        CompareImages(img1, img2, desc);
        ImageDestroy(&img1);
        ImageDestroy(&img2);
    }

    // --- Testes quadradas cores diferentes ---
    for(int i=0; i<n_square; i++){
        int t = sizes_square[i];
        Image img1 = ImageCreateChess(t, t, 1, 0xFF0000);
        Image img2 = ImageCreateChess(t, t, 1, 0x00FF00);
        char desc[200];
        sprintf(desc, "Imagens quadradas mesmas dimensões, cores diferentes (%dx%d)", t, t);
        CompareImages(img1, img2, desc);
        ImageDestroy(&img1);
        ImageDestroy(&img2);
    }

    // --- Testes quadrados tamanhos diferentes ---
    for(int i=0; i<n_square; i++){
        for(int j=i+1; j<n_square; j++){
            int t1 = sizes_square[i];
            int t2 = sizes_square[j];
            Image img1 = ImageCreateChess(t1, t1, 1, 0xFF0000);
            Image img2 = ImageCreateChess(t2, t2, 1, 0xFF0000);
            char desc[200];
            sprintf(desc, "Imagens quadradas tamanhos diferentes (%dx%d vs %dx%d)", t1, t1, t2, t2);
            CompareImages(img1, img2, desc);
            ImageDestroy(&img1);
            ImageDestroy(&img2);
        }
    }

    // --- Testes retangulares ---
    for(int i=0; i<n_rect; i++){
        int w = rects[i][0];
        int h = rects[i][1];
        Image img1 = ImageCreateChess(w, h, 1, 0xFF0000);
        Image img2 = ImageCreateChess(w, h, 1, 0xFF0000);
        char desc[200];
        sprintf(desc, "Imagens retangulares iguais (%dx%d)", w, h);
        CompareImages(img1, img2, desc);
        ImageDestroy(&img1);
        ImageDestroy(&img2);
    }

    // --- Testes retangulares cores diferentes ---
    for(int i=0; i<n_rect; i++){
        int w = rects[i][0];
        int h = rects[i][1];
        Image img1 = ImageCreateChess(w, h, 1, 0xFF0000);
        Image img2 = ImageCreateChess(w, h, 1, 0x0000FF);
        char desc[200];
        sprintf(desc, "Imagens retangulares cores diferentes (%dx%d)", w, h);
        CompareImages(img1, img2, desc);
        ImageDestroy(&img1);
        ImageDestroy(&img2);
    }

    // --- Testes de alterações de pixels ---
    for(int i=0; i<n_square; i++){
        int t = sizes_square[i];
        Image img1 = ImageCreateChess(t, t, 1, 0xFF0000);

        // 1. Primeiro pixel
        Image img2 = ImageCopy(img1);
        AlterPixel(img2, 0, 0, 0x00FF00);
        GenerateAlteredTests(img1, img2, t, "primeiro pixel alterado");
        ImageDestroy(&img2);

        // 2. Último pixel
        img2 = ImageCopy(img1);
        AlterPixel(img2, t-1, t-1, 0x00FF00);
        GenerateAlteredTests(img1, img2, t, "último pixel alterado");
        ImageDestroy(&img2);

        // 3. Meio da imagem
        img2 = ImageCopy(img1);
        AlterPixel(img2, t/2, t/2, 0x00FF00);
        GenerateAlteredTests(img1, img2, t, "pixel no meio alterado");
        ImageDestroy(&img2);

        // 4. Pixel qualquer da primeira linha (não primeiro)
        img2 = ImageCopy(img1);
        AlterPixel(img2, t/2, 0, 0x00FF00);
        GenerateAlteredTests(img1, img2, t, "pixel alterado na primeira linha");
        ImageDestroy(&img2);

        // 5. Pixel qualquer da última linha (exceto último)
        img2 = ImageCopy(img1);
        AlterPixel(img2, t/2, t-1, 0x00FF00);
        GenerateAlteredTests(img1, img2, t, "pixel alterado na última linha");
        ImageDestroy(&img2);

        ImageDestroy(&img1);
    }

    // --- Comparações entre quadrados e retângulos ---
    for(int i=0; i<n_square; i++){
        for(int j=0; j<n_rect; j++){
            int t = sizes_square[i];
            int w = rects[j][0];
            int h = rects[j][1];
            Image img1 = ImageCreateChess(t, t, 1, 0xFF0000);
            Image img2 = ImageCreateChess(w, h, 1, 0xFF0000);
            char desc[200];
            sprintf(desc, "Comparação quadrado (%dx%d) vs retângulo (%dx%d)", t, t, w, h);
            CompareImages(img1, img2, desc);
            ImageDestroy(&img1);
            ImageDestroy(&img2);
        }
    }
}

int main() {
    RunAllTests();
    return 0;
}
