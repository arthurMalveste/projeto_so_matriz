#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int N = 1000;
    FILE *f = fopen("matriz1000.dat", "w");
    if (!f) {
        printf("Erro ao criar arquivo.\n");
        return 1;
    }

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));
    
    // Gera a matriz 1000x1000 com números aleatórios entre -100 e 99
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fprintf(f, "%d", (rand() % 200) - 100);
            if (j < N - 1) fprintf(f, " ");
        }
        fprintf(f, "\n");
    }
    
    fclose(f);
    printf("Arquivo matriz1000.dat gerado com sucesso!\n");
    return 0;
}