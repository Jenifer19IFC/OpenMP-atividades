#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>

void imprimirMatriz(const std::vector<std::vector<int>>& matriz) {
    for(const auto& linha : matriz) {
        for(int valor : linha) {
            std::cout << valor << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    const int linhas = 2;
    const int colunas = 2;

    std::vector<std::vector<int>> matriz(linhas, std::vector<int>(colunas));

    #pragma omp single
    {
        srand(static_cast<unsigned int>(time(nullptr)));
        printf("Matriz inicializada apenas uma vez...\n");
        // imprimirMatriz(matriz);
    }

    // Preenche a matriz em paralelo com valores aleatórios
    #pragma omp parallel for 
    for(int i = 0; i < linhas; ++i) {
        for(int j = 0; j < colunas; ++j) {
            matriz[i][j] = rand() % 100 + 1; // Gera um número aleatório entre 1 e 100
            printf("Thread %d -> [%d,%d] = %d\n", omp_get_thread_num(), i, j, matriz[i][j]);
        }
    }

    printf("\nMatriz final:\n");
    imprimirMatriz(matriz);

    return 0;
}
