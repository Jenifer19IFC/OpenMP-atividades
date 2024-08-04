#include <iostream>
#include <vector>
#include <omp.h>

int main() {
    
    std::vector<int> vetor = {1, 2, 1, 2};
    
    int soma = 0;

    #pragma omp parallel for reduction(+:soma)
    for(int i = 0; i < vetor.size(); ++i) {
        soma += vetor[i];
        printf("Thread %d somando %d\n", omp_get_thread_num(), vetor[i]);
    }

    std::cout << "\nSoma total = " << soma << std::endl;

    return 0;
}
