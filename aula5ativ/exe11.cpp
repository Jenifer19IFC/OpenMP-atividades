#include <stdio.h>
#include <omp.h>

int dado_produzido = 0; // Variável compartilhada para armazenar os dados produzidos

void produtor(int thread_id) {
    for (int i = 1; i <= 10; ++i) {
        dado_produzido = i; // Produzindo dados...
        printf("Thread %d produziu: %d\n", thread_id, dado_produzido);
        #pragma omp flush(dado_produzido) // Sincronização de memória
        #pragma omp barrier // Sincroniza com as threads consumidoras
    }
}

void consumidor(int thread_id) {
    #pragma omp barrier // Sincroniza com a thread produtora
    for (int i = 1; i <= 10; ++i) {
        #pragma omp flush(dado_produzido) // Sincronização de memória
        printf("Consumidor %d consumiu: %d\n", thread_id, dado_produzido);
        #pragma omp barrier 
    }
}

int main() {

    #pragma omp parallel num_threads(4)
    {
        int thread_id = omp_get_thread_num();

        #pragma omp single // Garante apenas uma thread produtora
        {
            produtor(thread_id);
        }

        consumidor(thread_id); // Restante é consumidora
    }

    return 0;
}
