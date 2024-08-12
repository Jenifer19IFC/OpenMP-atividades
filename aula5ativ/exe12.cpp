#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define TOTAL_PONTOS 100000

int main() {
    int pontos_dentro_do_circulo = 0; // Contador global
    double x, y;
    srand(time(NULL)); // Inicializa a semente para números aleatórios

    #pragma omp parallel private(x, y) reduction(+:pontos_dentro_do_circulo) 
    {

        #pragma omp for
        for (int i = 0; i < TOTAL_PONTOS; i++) {
            // Gera pontos aleatórios entre 0 e 1
            x = (double)rand() / RAND_MAX; 
            y = (double)rand() / RAND_MAX; 
            double distancia = x * x + y * y ;
            printf("\nThread %d gerou o ponto (%f, %f)",  omp_get_thread_num(), x, y);

            // Verifica se o ponto está dentro do círculo
            if (distancia <= 1.0) {
                #pragma omp atomic
                pontos_dentro_do_circulo++; // Atualiza contador
            }
        }

        #pragma omp barrier 
    } 

    // Cálculo final de PI
    double pi = 4.0 * pontos_dentro_do_circulo / TOTAL_PONTOS;
    printf("\nPontos dentro do círculo: %d\nTotal de pontos: %d\n", pontos_dentro_do_circulo, TOTAL_PONTOS);
    printf("\nEstimativa de PI: %f\n", pi);

    return 0;
}