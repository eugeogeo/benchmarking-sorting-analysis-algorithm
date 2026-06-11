#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

// Estrutura para contabilizar as métricas do algoritmo
typedef struct {
    unsigned long long comparacoes;
    unsigned long long trocas;
    double tempo_segundos;
} Metricas;

// --- IMPLEMENTAÇÃO DOS ALGORITMOS ---

void bubbleSort(int *vetor, int n, Metricas *m) {
    m->comparacoes = 0;
    m->trocas = 0;
    int i, j, trocou;
    for (i = 0; i < n - 1; i++) {
        trocou = 0;
        for (j = 0; j < n - i - 1; j++) {
            m->comparacoes++;
            if (vetor[j] > vetor[j + 1]) {
                int temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
                m->trocas++;
                trocou = 1;
            }
        }
        if (trocou == 0) break; // Melhoria sugerida no PDF
    }
}

void insertionSort(int *vetor, int n, Metricas *m) {
    m->comparacoes = 0;
    m->trocas = 0;
    for (int i = 1; i < n; i++) {
        int chave = vetor[i];
        int j = i - 1;
        while (j >= 0) {
            m->comparacoes++;
            if (vetor[j] > chave) {
                vetor[j + 1] = vetor[j];
                m->trocas++;
                j--;
            } else {
                break;
            }
        }
        vetor[j + 1] = chave;
    }
}

void selectionSort(int *vetor, int n, Metricas *m) {
    m->comparacoes = 0;
    m->trocas = 0;
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            m->comparacoes++;
            if (vetor[j] < vetor[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int temp = vetor[min_idx];
            vetor[min_idx] = vetor[i];
            vetor[i] = temp;
            m->trocas++;
        }
    }
}

void shellSort(int *vetor, int n, Metricas *m) {
    m->comparacoes = 0;
    m->trocas = 0;
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = vetor[i];
            int j;
            for (j = i; j >= gap; j -= gap) {
                m->comparacoes++;
                if (vetor[j - gap] > temp) {
                    vetor[j] = vetor[j - gap];
                    m->trocas++;
                } else {
                    break;
                }
            }
            vetor[j] = temp;
        }
    }
}

// Quicksort Clássico (pivô = último elemento)
void quicksort_recursive(int *vetor, int low, int high, Metricas *m) {
    if (low < high) {
        int pivot = vetor[high];
        int i = (low - 1);
        for (int j = low; j < high; j++) {
            m->comparacoes++;
            if (vetor[j] < pivot) {
                i++;
                int temp = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = temp;
                m->trocas++;
            }
        }
        int temp = vetor[i + 1];
        vetor[i + 1] = vetor[high];
        vetor[high] = temp;
        m->trocas++;
        int pi = i + 1;

        quicksort_recursive(vetor, low, pi - 1, m);
        quicksort_recursive(vetor, pi + 1, high, m);
    }
}

void quickSort(int *vetor, int n, Metricas *m) {
    m->comparacoes = 0;
    m->trocas = 0;
    quicksort_recursive(vetor, 0, n - 1, m);
}

void heapify(int *vetor, int n, int i, Metricas *m) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n) {
        m->comparacoes++;
        if (vetor[l] > vetor[largest])
            largest = l;
    }

    if (r < n) {
        m->comparacoes++;
        if (vetor[r] > vetor[largest])
            largest = r;
    }

    if (largest != i) {
        int temp = vetor[i];
        vetor[i] = vetor[largest];
        vetor[largest] = temp;
        m->trocas++;
        heapify(vetor, n, largest, m);
    }
}

void heapSort(int *vetor, int n, Metricas *m) {
    m->comparacoes = 0;
    m->trocas = 0;
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(vetor, n, i, m);

    for (int i = n - 1; i > 0; i--) {
        int temp = vetor[0];
        vetor[0] = vetor[i];
        vetor[i] = temp;
        m->trocas++;
        heapify(vetor, i, 0, m);
    }
}

// --- FUNÇÕES AUXILIARES DE GERAÇÃO DE DADOS ---

void gerarVetorAleatorio(int *v, int n) {
    for (int i = 0; i < n; i++) v[i] = rand() % 100000;
}

void gerarVetorOrdenado(int *v, int n) {
    for (int i = 0; i < n; i++) v[i] = i;
}

void gerarVetorInverso(int *v, int n) {
    for (int i = 0; i < n; i++) v[i] = n - i;
}

void gerarVetorQuaseOrdenado(int *v, int n) {
    for (int i = 0; i < n; i++) v[i] = i;
    int trocas = (int)(n * 0.005); // 0,5%
    for (int i = 0; i < trocas; i++) {
        int idx = rand() % (n - 1);
        int temp = v[idx];
        v[idx] = v[idx + 1];
        v[idx + 1] = temp;
    }
}

// Função para medir tempo
void medir(void (*sortFunc)(int*, int, Metricas*), int *vetor, int n, Metricas *m) {
    struct timespec inicio, fim;
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    sortFunc(vetor, n, m);
    clock_gettime(CLOCK_MONOTONIC, &fim);
    m->tempo_segundos = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
}

int main() {
    srand(42);
    FILE *f1 = fopen("data/problema1.csv", "w");
    fprintf(f1, "Algoritmo,Cenario,N,Tempo,Comparacoes,Trocas\n");

    int N1 = 30000;
    int *v = malloc(N1 * sizeof(int));
    int *temp_v = malloc(N1 * sizeof(int));
    Metricas m;

    char *cenarios[] = {"Aleatorio", "Ordenado", "Inverso"};
    void (*algos1[])(int*, int, Metricas*) = {bubbleSort, insertionSort, selectionSort};
    char *names1[] = {"BubbleSort", "InsertionSort", "SelectionSort"};

    for (int c = 0; c < 3; c++) {
        if (c == 0) gerarVetorAleatorio(v, N1);
        else if (c == 1) gerarVetorOrdenado(v, N1);
        else gerarVetorInverso(v, N1);

        for (int a = 0; a < 3; a++) {
            memcpy(temp_v, v, N1 * sizeof(int));
            medir(algos1[a], temp_v, N1, &m);
            fprintf(f1, "%s,%s,%d,%f,%llu,%llu\n", names1[a], cenarios[c], N1, m.tempo_segundos, m.comparacoes, m.trocas);
        }
    }
    fclose(f1);
    free(v);
    free(temp_v);

    // Problema 2
    FILE *f2 = fopen("data/problema2.csv", "w");
    fprintf(f2, "Algoritmo,Execucao,Tempo\n");
    int N2 = 5000;
    v = malloc(N2 * sizeof(int));
    temp_v = malloc(N2 * sizeof(int));
    
    for (int i = 0; i < 10; i++) {
        // Heapsort
        gerarVetorOrdenado(v, N2);
        memcpy(temp_v, v, N2 * sizeof(int));
        medir(heapSort, temp_v, N2, &m);
        fprintf(f2, "Heapsort,%d,%f\n", i+1, m.tempo_segundos);

        // Quicksort
        memcpy(temp_v, v, N2 * sizeof(int));
        medir(quickSort, temp_v, N2, &m);
        fprintf(f2, "Quicksort,%d,%f\n", i+1, m.tempo_segundos);
    }
    fclose(f2);
    free(v);
    free(temp_v);

    // Problema 3
    FILE *f3 = fopen("data/problema3.csv", "w");
    fprintf(f3, "Algoritmo,Tempo\n");
    int N3 = 50000;
    v = malloc(N3 * sizeof(int));
    temp_v = malloc(N3 * sizeof(int));
    
    gerarVetorQuaseOrdenado(v, N3);
    
    memcpy(temp_v, v, N3 * sizeof(int));
    medir(insertionSort, temp_v, N3, &m);
    fprintf(f3, "InsertionSort,%f\n", m.tempo_segundos);

    memcpy(temp_v, v, N3 * sizeof(int));
    medir(shellSort, temp_v, N3, &m);
    fprintf(f3, "ShellSort,%f\n", m.tempo_segundos);

    fclose(f3);
    free(v);
    free(temp_v);

    printf("Experimentos concluidos. Dados salvos em data/\n");
    return 0;
}