
#include <stdio.h>
#include <omp.h>

#define MAX_THREADS 8  // Definir el número máximo de hilos que esperamos usar
#define N 20  // Número de términos a generar

int main() {
    int M = omp_get_max_threads();  // Número de procesadores (hilos) disponibles


    // Calcular el tamaño del segmento de la serie para cada procesador
    int segment_size = N / M;
    int remainder = N % M;

    // Crear un array para almacenar los vectores
    int series[MAX_THREADS][N];

    // Inicializar el array con ceros
    for (int i = 0; i < MAX_THREADS; i++) {
        for (int j = 0; j < N; j++) {
            series[i][j] = 0;
        }
    }

    // Configurar el número de hilos
    omp_set_num_threads(M);

    // Paralelizar el cálculo de la serie
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int start = thread_id * segment_size;
        int end = start + segment_size;

        if (thread_id == M - 1) {
            end += remainder;  // Agregar el resto al último procesador
        }

        for (int i = start; i < end; i++) {
            series[thread_id][i - start] = 2 * (i + 1);
        }
    }

    // Imprimir los vectores generados
    for (int i = 0; i < M; i++) {
        printf("Vector %d: ", i);
        int limit = (i == M - 1) ? segment_size + remainder : segment_size;
        for (int j = 0; j < limit; j++) {
            printf("%d ", series[i][j]);
        }
        printf("\n");
    }

    return 0;
}
