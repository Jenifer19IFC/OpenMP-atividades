#include <stdio.h>
#include <omp.h>

#define TAMVETOR 9  
#define VALORBUSCADO 1  

int main() {
    int vetor[TAMVETOR] = {2, 1, 3, 4, 5, 1, 2, 3, 4};  
    int posicao = -1;  
    int encontrado = 0;  

    #pragma omp parallel shared(posicao, encontrado)
    {
        // Busca paralela
        #pragma omp for
        for (int i = 0; i < TAMVETOR; i++) {
            printf("\nThread %d processando %d",  omp_get_thread_num(), vetor[i]);
            if (!encontrado && vetor[i] == VALORBUSCADO) {
                #pragma omp critical
                {
                    if (!encontrado) {  
                        posicao = i;
                        encontrado = 1;
                        printf("\nThread %d encontrou %d na posição %d",  omp_get_thread_num(), VALORBUSCADO, i);
                    }
                }
            }
        }

        #pragma omp single
        {
            if (posicao != -1) {
                printf("\nValor %d encontrado na posição %d\n", VALORBUSCADO, posicao);
            } else {
                printf("\nValor %d não encontrado no vetor\n", VALORBUSCADO);
            }
        }
    }

    return 0;
}
