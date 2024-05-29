#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int rank, size, N = 10;
    int* sequence = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int local_N = N / size; // Número de elementos a calcular por cada procesador

    // El último procesador puede tener más elementos si N no es divisible por size
    if (rank == size - 1) {
        local_N += N % size;
    }

    // Cada procesador calculará una parte de la secuencia
    int* local_sequence = (int*)malloc(local_N * sizeof(int));
    int start = rank * (N / size) * 2 + 2;

    for (int i = 0; i < local_N; i++) {
        local_sequence[i] = start + i * 2;
    }

    if (rank == 0) {
        sequence = (int*)malloc(N * sizeof(int));
    }

    // Gather all parts of the sequence into the root processor
    int* recvcounts = NULL;
    int* displs = NULL;

    if (rank == 0) {
        recvcounts = (int*)malloc(size * sizeof(int));
        displs = (int*)malloc(size * sizeof(int));

        for (int i = 0; i < size; i++) {
            recvcounts[i] = (N / size) + (i == size - 1 ? N % size : 0);
            recvcounts[i] *= sizeof(int);
            displs[i] = i * (N / size) * sizeof(int);
        }
    }

    MPI_Gatherv(local_sequence, local_N, MPI_INT, sequence, recvcounts, displs, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Generated sequence: ");
        for (int i = 0; i < N; i++) {
            printf("%d ", sequence[i]);
        }
        printf("\n");
    }

    // Liberar memoria
    free(local_sequence);
    if (rank == 0) {
        free(sequence);
        free(recvcounts);
        free(displs);
    }

    MPI_Finalize();
    return 0;
}
