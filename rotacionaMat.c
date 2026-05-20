#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h> 


// Função que aloca uma matriz NxN em uma única etapa
int **alocarMatriz(int N) {
    
    size_t tamanho_ponteiros = N * sizeof(int *);
    size_t tamanho_dados = N * N * sizeof(int);
    

    int **matriz = malloc(tamanho_ponteiros + tamanho_dados);
    
    if (matriz == NULL) {
        printf("Erro de alocação de memória!\n");
        exit(1);
    }

    int *dados = (int *)(matriz + N);

    for (int i = 0; i < N; i++) {
        matriz[i] = dados + (i * N);
    }

    return matriz;
}

// Estrutura para passar argumentos para as threads
typedef struct {
    int id;
    int N;
    int num_threads;
    int **matriz_orig;
    int **matriz_rot;
    double tempo_execucao; 
} ThreadArgs;

// Função que cada thread vai executar
void *rotacionar_parte(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    struct timespec t_inicio, t_fim;

    clock_gettime(CLOCK_MONOTONIC, &t_inicio);

    int tamanho_fatia = args->N / args->num_threads;
    int linha_inicio = args->id * tamanho_fatia;
   
    int linha_fim = (args->id == args->num_threads - 1) ? args->N : linha_inicio + tamanho_fatia;

    for (int i = linha_inicio; i < linha_fim; i++) {
        for (int j = 0; j < args->N; j++) {
            args->matriz_rot[j][args->N - 1 - i] = args->matriz_orig[i][j];
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &t_fim);
    args->tempo_execucao = (t_fim.tv_sec - t_inicio.tv_sec);
    args->tempo_execucao += (t_fim.tv_nsec - t_inicio.tv_nsec) / 1000000000.0;

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

    if (argc != 5) {
        printf("Uso correto: %s <N> <T> <Arquivo Entrada> <Arquivo Saida>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    int T = atoi(argv[2]);
    char *arquivo_entrada = argv[3];
    char *arquivo_saida = argv[4];

    printf("Iniciando programa com Matriz %dx%d, usando %d threads.\n", N, N, T);
    printf("Lendo de: %s | Gravando em: %s\n", arquivo_entrada, arquivo_saida);

    int **matriz_original = alocarMatriz(N);
    int **matriz_rotacionada = alocarMatriz(N);

    printf("Matrizes alocadas com sucesso em etapa unica!\n");

    FILE *file_in = fopen(arquivo_entrada, "r");
    if (file_in == NULL) {
        printf("Erro: Nao foi possivel abrir o arquivo %s\n", arquivo_entrada);
        free(matriz_original);
        free(matriz_rotacionada);
        return 1;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (fscanf(file_in, "%d", &matriz_original[i][j]) != 1) {
                printf("Erro: Faltam dados no arquivo ou formato incorreto!\n");
                fclose(file_in);
                free(matriz_original);
                free(matriz_rotacionada);
                return 1;
            }
        }
    }
    fclose(file_in);
    printf("Matriz carregada com sucesso do arquivo!\n");



    struct timespec inicio, fim;
    double tempoTotal;

    // Marca o tempo de INÍCIO
    clock_gettime(CLOCK_MONOTONIC, &inicio);

    pthread_t threads[T];
    ThreadArgs args[T];

    // 1. Disparando (criando) as threads
    for (int i = 0; i < T; i++) {
        args[i].id = i;
        args[i].N = N;
        args[i].num_threads = T;
        args[i].matriz_orig = matriz_original;
        args[i].matriz_rot = matriz_rotacionada;
        
        if (pthread_create(&threads[i], NULL, rotacionar_parte, (void *)&args[i]) != 0) {
            printf("Erro ao criar a thread %d\n", i);
            exit(1);
        }
    }

    // 2. Aguardando todas as threads terminarem e imprimindo os tempos
    for (int i = 0; i < T; i++) {
        pthread_join(threads[i], NULL);
        printf("Tempo de execucao do Thread %d: %f segundos.\n", i, args[i].tempo_execucao);
    }

    // Marca o tempo de FIM
    clock_gettime(CLOCK_MONOTONIC, &fim);


    tempoTotal = (fim.tv_sec - inicio.tv_sec);
    tempoTotal += (fim.tv_nsec - inicio.tv_nsec) / 1000000000.0;

    printf("Tempo total de execucao: %f segundos.\n", tempoTotal);

    FILE *file_out = fopen(arquivo_saida, "w");
    if (file_out == NULL) {
        printf("Erro: Nao foi possivel criar o arquivo %s\n", arquivo_saida);
        free(matriz_original);
        free(matriz_rotacionada);
        return 1;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fprintf(file_out, "%d", matriz_rotacionada[i][j]);

            if (j < N - 1) {
                fprintf(file_out, " ");
            }
        }
        fprintf(file_out, "\n");
    }

    fclose(file_out);
    printf("Matriz rotacionada salva com sucesso em %s!\n", arquivo_saida);

    free(matriz_original);
    free(matriz_rotacionada);

    return 0;

}