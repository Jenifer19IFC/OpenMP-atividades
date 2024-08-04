#include <iostream>
#include <vector>
#include <omp.h>

int main() {
    
    std::vector<int> vetor = {1, 10, 5, 6};
    std::vector<int> vetor2 = {1, 10, 5, 6};
    
    int soma = 0;
    int prod = 1;

    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            for(int i = 0; i < vetor.size(); ++i) {
                printf("S1: Thread %d -> %d + %d\n", omp_get_thread_num(), soma, vetor[i]);
                soma += vetor[i];
            }
            #pragma omp section
            for(int i = 0; i < vetor2.size(); ++i) {
                printf("S2: Thread %d -> %d x %d\n", omp_get_thread_num(), prod, vetor2[i]);
                prod *= vetor2[i];
            }
        }
    }

    std::cout << "\nSoma total vetor = " << soma << std::endl;
    std::cout << "Produto total vetor2 = " << prod << std::endl;

    return 0;
}
