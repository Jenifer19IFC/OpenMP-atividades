#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 3 

void imprimeMatriz(int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int A[N][N], B[N][N], C[N][N];

    // Matriz A
    A[0][0] = 1; A[0][1] = 2; A[0][2] = 3;
    A[1][0] = 2; A[1][1] = 2; A[1][2] = 1;
    A[2][0] = 1; A[2][1] = 2; A[2][2] = 3;

    // Matriz B
    B[0][0] = 1; B[0][1] = 3; B[0][2] = 1;
    B[1][0] = 4; B[1][1] = 3; B[1][2] = 2;
    B[2][0] = 0; B[2][1] = 3; B[2][2] = 1;

    // Inicializando a matriz resultante C com zeros
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
        }
    }

    #pragma omp parallel
    {
        #pragma omp sections
        {
            // Processa as primeiras metades das linhas
            #pragma omp section
            {
                #pragma omp parallel for collapse(2)
                for (int i = 0; i < N / 2; i++) {
                    for (int j = 0; j < N; j++) {
                        C[i][j] = 0;
                        for (int k = 0; k < N; k++) {
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }

            // Processa as últimas metades das linhas
            #pragma omp section
            {
                #pragma omp parallel for collapse(2)
                for (int i = N / 2; i < N; i++) {
                    for (int j = 0; j < N; j++) {
                        C[i][j] = 0;
                        for (int k = 0; k < N; k++) {
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }

    printf("\nMatriz A:\n");
    imprimeMatriz(A);

    printf("Matriz B:\n");
    imprimeMatriz(B);

    printf("Matriz C (Resultado de A * B):\n");
    imprimeMatriz(C);

    return 0;
}
