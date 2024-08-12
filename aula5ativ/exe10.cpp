#include <stdio.h>
#include <omp.h>

#define N 8  // Número de threads

int main() {
    
    omp_set_num_threads(N);

 
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();  

        // 1° etapa
        printf("Thread %d: Iniciando a primeira etapa.\n", thread_id);
        
        // Simulação de trabalho 
        for (int i = 0; i < 5; i++) {
            printf("Thread %d: Processando na primeira etapa, i = %d.\n", thread_id, i);
        }

        printf("\nBARRIER: Sincronizando as threads...\n");
        // Sincroniza todas as threads antes de prosseguir
        #pragma omp barrier

        // 2° etapa
        printf("Thread %d: Iniciando a segunda etapa.\n", thread_id);

        // Simulação de trabalho
        for (int i = 0; i < 5; i++) {
            printf("Thread %d: Processando na segunda etapa, i = %d.\n", thread_id, i);
        }
    }

    return 0;
}
