#include <stdio.h>
#include <mpi.h>

#define N 10 // Número de términos de Fibonacci a calcular

int fibonacci(int n) {
    if (n <= 1)
        return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(int argc, char *argv[]) {
    int rank, size, i;
    int result[N]; // Arreglo para almacenar los términos de Fibonacci

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        printf("Este programa necesita al menos 2 procesadores\n");
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) { // Procesador MASTER
        for (i = 0; i < N; i++) {
            int term;
            MPI_Recv(&term, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            result[i] = term;
        }

        // Imprimir la secuencia de Fibonacci
        printf("Secuencia de Fibonacci:\n");
        for (i = 0; i < N; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
    } else { // Procesadores SLAVE
        for (i = 0; i < N; i++) {
            int term = fibonacci(i);
            MPI_Send(&term, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}
