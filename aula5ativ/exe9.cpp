#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define TAM 10

int main() {

    int vetor[TAM] = {5, 8, 3, 12, 7, 9, 2, 6, 1, 11}; 
    int contPares = 0;
    int contImpares = 0;

    printf("Vetor: ");
    for (int i = 0; i < TAM; i++) {
        printf("%d ", vetor[i]);
    }

    // Paraleliza a iteração sobre o vetor
    #pragma omp parallel for
    for (int i = 0; i < TAM; i++) {
        if (vetor[i] % 2 == 0) {
            #pragma omp atomic
            contPares++; // Atualização da contagem 'pares'
        } else {
            #pragma omp atomic 
            contImpares++; // Atualização da contagem 'ímpares'
        }
    }

    // Exibindo os resultados
    printf("\n\n%d números pares\n", contPares);
    printf("%d números ímpares\n", contImpares);

    return 0;
}