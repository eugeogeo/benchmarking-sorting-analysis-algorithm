#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CLOCK_MONOTONIC 1

// Estrutura para contabilizar as métricas do algoritmo
typedef struct
{
  unsigned long long comparacoes;
  unsigned long long trocas;
  double tempo_segundos;
} Metricas;
// ---- ESPAÇO PARA AS IMPLEMENTAÇÕES DOS ALUNOS ----
void insertionSort(int *vetor, int n, Metricas *m)
{
  m->comparacoes = 0;
  m->trocas = 0;

  // EXEMPLO DE IMPLEMENTAÇÃO E INSTRUMENTAÇÃO:
  for (int i = 1; i < n; i++)
  {
    int chave = vetor[i];
    int j = i - 1;

    // Cada entrada no laço testa a condição (j >= 0 e vetor[j] > chave)
    while (j >= 0)
    {
      m->comparacoes++; // Conta a comparação feita no 'if' conceitual do while
      if (vetor[j] > chave)
      {
        vetor[j + 1] = vetor[j];
        m->trocas++; // Conta o deslocamento/escrita
        j--;
      }
      else
      {
        break;
      }
    }
    // Se saiu do laço porque j < 0, a última comparação falhou e já foi contada.
    // Se saiu pelo 'break', também já foi contada.
    vetor[j + 1] = chave;
  }
}
// ---- FUNÇÕES AUXILIARES DE GERAÇÃO DE DADOS ----
void gerarVetorAleatorio(int *v, int n)
{
  for (int i = 0; i < n; i++)
    v[i] = rand() % 100000;
}
void gerarVetorOrdenado(int *v, int n)
{
  for (int i = 0; i < n; i++)
    v[i] = i;
}
void gerarVetorInverso(int *v, int n)
{
  for (int i = 0; i < n; i++)
    v[i] = n - i;
}
int main()
{
  int N = 30000; // Exemplo de tamanho
  int *vetor = (int *)malloc(N * sizeof(int));
  if (vetor == NULL)
    return 1;

  srand(42); // Semente fixa para garantir que todos testem os mesmos dados
  gerarVetorAleatorio(vetor, N);
  struct timespec inicio, fim;
  Metricas m;
  // Medição de tempo de CPU de alta resolução
  clock_gettime(CLOCK_MONOTONIC, &inicio);
  insertionSort(vetor, N, &m);
  clock_gettime(CLOCK_MONOTONIC, &fim);
  // Cálculo do tempo decorrido em segundos
  m.tempo_segundos = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
  printf("Resultados:\nTempo: %f s\nComparacoes: %llu\nTrocas: %llu\n",
         m.tempo_segundos, m.comparacoes, m.trocas);
  free(vetor);

  return (0);
}