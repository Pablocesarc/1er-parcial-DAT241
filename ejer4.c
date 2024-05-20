#include <stdio.h>
#include <omp.h>

#define N 2

void main() {

    float matriz[N][N] = {
        {2, 3},
        {4, 5},
    
    };
    float vector[N] = {1, 2};
    int resultado[N];

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        int suma = 0;
        #pragma omp parallel for reduction(+:suma)
        for (int j = 0; j < N; j++) {
            suma += matriz[i][j] * vector[j];
        }
        resultado[i] = suma;
    }

    printf("Resultado de la multiplicación:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", resultado[i]);
    }
    printf("\n");
}
