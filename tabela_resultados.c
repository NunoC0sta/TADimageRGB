#include <stdio.h>

typedef struct {
    char descricao[200];
    double tempo;
    double caltime;
    int comparisons;
} Resultado;

int main() {
    Resultado dados[] = {
        {"Imagens quadradas iguais (5x5)", 0.000023, 0.000044, 9},
        {"Imagens quadradas iguais (50x50)", 0.000007, 0.000013, 54},
        {"Imagens quadradas iguais (500x500)", 0.000050, 0.000111, 504},
        {"Imagens quadradas iguais (5000x5000)", 0.003880, 0.008650, 5004},
        {"Imagens quadradas iguais (12000x12000)", 0.020614, 0.046251, 12004},
        {"Imagens quadradas mesmas dimensões, cores diferentes (5x5)", 0.000013, 0.000028, 4},
        {"Imagens quadradas mesmas dimensões, cores diferentes (50x50)", 0.000009, 0.000019, 4},
        {"Imagens quadradas mesmas dimensões, cores diferentes (500x500)", 0.000012, 0.000024, 4},
        {"Imagens quadradas mesmas dimensões, cores diferentes (5000x5000)", 0.000009, 0.000021, 4},
        {"Imagens quadradas mesmas dimensões, cores diferentes (12000x12000)", 0.000009, 0.000020, 4},
        {"Imagens quadradas tamanhos diferentes (5x5 vs 50x50)", 0.000008, 0.000018, 1},
        {"Imagens quadradas tamanhos diferentes (5x5 vs 500x500)", 0.000008, 0.000018, 1},
        {"Imagens quadradas tamanhos diferentes (5x5 vs 5000x5000)", 0.000009, 0.000020, 1},
        {"Imagens quadradas tamanhos diferentes (5x5 vs 12000x12000)", 0.000008, 0.000019, 1},
        {"Imagens quadradas tamanhos diferentes (50x50 vs 500x500)", 0.000008, 0.000017, 1},
        {"Imagens quadradas tamanhos diferentes (50x50 vs 5000x5000)", 0.000006, 0.000015, 1},
        {"Imagens quadradas tamanhos diferentes (50x50 vs 12000x12000)", 0.000008, 0.000018, 1},
        {"Imagens quadradas tamanhos diferentes (500x500 vs 5000x5000)", 0.000009, 0.000020, 1},
        {"Imagens quadradas tamanhos diferentes (500x500 vs 12000x12000)", 0.000006, 0.000014, 1},
        {"Imagens quadradas tamanhos diferentes (5000x5000 vs 12000x12000)", 0.000005, 0.000012, 1},
        {"Imagens retangulares iguais (5x10)", 0.000006, 0.000013, 14},
        {"Imagens retangulares iguais (50x100)", 0.000004, 0.000009, 104},
        {"Imagens retangulares iguais (500x1000)", 0.000108, 0.000240, 1004},
        {"Imagens retangulares iguais (12000x6000)", 0.009787, 0.021574, 6004},
        {"Imagens retangulares cores diferentes (5x10)", 0.000008, 0.000018, 4},
        {"Imagens retangulares cores diferentes (50x100)", 0.000004, 0.000009, 4},
        {"Imagens retangulares cores diferentes (500x1000)", 0.000007, 0.000016, 4},
        {"Imagens retangulares cores diferentes (12000x6000)", 0.000006, 0.000013, 4},
        {"Imagem quadrada com último pixel alterado (5x5)", 0.000006, 0.000013, 9},
        {"Imagem quadrada com último pixel alterado (50x50)", 0.000005, 0.000010, 54},
        {"Imagem quadrada com último pixel alterado (500x500)", 0.000052, 0.000112, 504},
        {"Imagem quadrada com último pixel alterado (5000x5000)", 0.003850, 0.008086, 5004},
        {"Imagem quadrada com último pixel alterado (12000x12000)", 0.025682, 0.054966, 12004}
    };

    FILE* f = fopen("tabela_resultados.csv", "w");
    if (!f) {
        printf("Erro ao criar arquivo CSV\n");
        return 1;
    }

    // Cabeçalho
    fprintf(f, "Tipo de Comparação,Tempo decorrido (último reset) (s),Tempo em unidades calibradas (s),Número de Comparações\n");

    int n = sizeof(dados)/sizeof(dados[0]);
    for(int i=0;i<n;i++){
        fprintf(f, "\"%s\",%.6f,%.6f,%d\n", dados[i].descricao, dados[i].tempo, dados[i].caltime, dados[i].comparisons);
    }

    fclose(f);
    printf("CSV gerado com sucesso: tabela_resultados.csv\n");
    return 0;
}
