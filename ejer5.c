
#include <stdio.h>
#include <mpi.h>

#define N 3

void multiplicarMatrizVector(int matriz[N][N], int vector[N], int resultado[N]) {
    for (int i = 0; i < N; i++) {
        resultado[i] = 0;
        for (int j = 0; j < N; j++) {
            resultado[i] += matriz[i][j] * vector[j];
        }
    }
}

int main(int argc, char *argv[]) {
    int size, rank;
    int matriz[N][N] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int vector[N] = {1, 2, 3};
    int resultado_local[N]; // Resultado local de cada proceso
    int resultado_final[N]; // Resultado final en el proceso 0

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Dividir el trabajo entre los procesos MPI
    int elementos_por_proceso = N / size;
    int inicio = rank * elementos_por_proceso;
    int fin = inicio + elementos_por_proceso;

    // Cada proceso calcula su parte de la multiplicación
    multiplicarMatrizVector(matriz, &vector[inicio], resultado_local);

    // Reunir los resultados parciales en el proceso 0
    MPI_Send(resultado_local, N, MPI_INT, 0, 0, MPI_COMM_WORLD);

    // El proceso 0 recibe los resultados parciales de los otros procesos
    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            resultado_final[i] = resultado_local[i];
        }
        for (int i = 1; i < size; i++) {
            MPI_Recv(resultado_local, N, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for (int j = 0; j < N; j++) {
                resultado_final[j] += resultado_local[j];
            }
        }
        printf("Resultado de la multiplicación:\n");
        for (int i = 0; i < N; i++) {
            printf("%d ", resultado_final[i]);
        }
        printf("\n");
    }

    MPI_Finalize();

    return 0;
}
