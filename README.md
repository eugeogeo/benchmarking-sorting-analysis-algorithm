# Trabalho Prático: Benchmarking e Análise Empírica de Algoritmos de Ordenação

Este projeto contém a implementação e análise de desempenho de seis algoritmos de ordenação: BubbleSort, InsertionSort, SelectionSort, ShellSort, Quicksort e Heapsort.

## Estrutura do Projeto

- `src/`: Contém o código-fonte em C (`main.c`) e o script de plotagem (`plot_results.py`).
- `data/`: Contém os arquivos CSV gerados com os resultados dos experimentos.
- `plots/`: Contém as visualizações geradas a partir dos dados.

## Requisitos

- Compilador GCC
- Python 3 (com pandas e matplotlib para os gráficos)

## Como Compilar e Executar

### 1. Compilar o código C
```bash
gcc src/main.c -o programa -lm
```

### 2. Executar os experimentos
Como o Quicksort clássico pode causar estouro de pilha em vetores ordenados (cenário do Problema 2), recomenda-se aumentar o limite da pilha antes de executar:
```bash
ulimit -s unlimited
./programa
```

### 3. Gerar os gráficos
```bash
python3 src/plot_results.py
```

## Algoritmos Implementados
1. **BubbleSort**: Versão otimizada que interrompe a execução se não houver trocas em uma passada.
2. **InsertionSort**: Implementação clássica com contagem de métricas.
3. **SelectionSort**: Implementação clássica.
4. **ShellSort**: Utiliza a sequência de gaps de Shell (N/2, N/4, ..., 1).
5. **Quicksort**: Versão clássica utilizando o último elemento como pivô.
6. **Heapsort**: Implementação clássica utilizando heap máximo.

## Métricas Coletadas
Para cada execução, são registradas:
- Tempo total de execução (segundos)
- Número de comparações de chaves
- Número de trocas/escritas no vetor
