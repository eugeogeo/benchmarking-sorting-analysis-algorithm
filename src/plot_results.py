import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Carregar dados do Problema 2
try:
    df = pd.read_csv('data/problema2.csv')

    # Calcular média e desvio padrão
    stats = df.groupby('Algoritmo')['Tempo'].agg(['mean', 'std']).reset_index()

    # Plotar gráfico de barras
    plt.figure(figsize=(10, 6))
    bars = plt.bar(stats['Algoritmo'], stats['mean'], yerr=stats['std'], capsize=10, color=['skyblue', 'salmon'])

    plt.title('Comparação de Tempo Médio: Heapsort vs Quicksort (Vetor Ordenado N=5000)')
    plt.ylabel('Tempo Médio (segundos)')
    plt.xlabel('Algoritmo')
    plt.grid(axis='y', linestyle='--', alpha=0.7)

    # Adicionar valores nas barras
    for bar in bars:
        yval = bar.get_height()
        plt.text(bar.get_x() + bar.get_width()/2, yval, f'{yval:.5f}s', va='bottom', ha='center')

    plt.tight_layout()
    plt.savefig('plots/grafico_problema2.png')
    print("Gráfico gerado com sucesso em plots/grafico_problema2.png")

except Exception as e:
    print(f"Erro ao gerar gráfico: {e}")
