#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define VALOR_MAXIMO 100  
#define TAM 10            

int main() {
    
    int vetor[TAM] = {5, 10, 15, 20, 5, 10, 5, 25, 100, 100}; 
    int histograma[VALOR_MAXIMO + 1] = {0}; // Inicializa com zeros

    printf("Vetor: ");
    for (int i = 0; i < TAM; i++) {
        printf("%d ", vetor[i]);
    }

    printf("\n");
    
    // Paralelização da leitura do vetor original
    #pragma omp parallel for
    for (int i = 0; i < TAM; i++) {
        int valor = vetor[i];

        // Proteção para atualização do histograma
        #pragma omp critical
        {
            histograma[valor]++;
        
        }
    }

    printf("\nHistograma:\n");
    for (int i = 0; i <= VALOR_MAXIMO; i++) {
        if (histograma[i] > 0) {
            printf("%d: %d\n", i, histograma[i]);
        }
    }

    return 0;
}