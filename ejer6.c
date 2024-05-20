#include <stdio.h>
#include <math.h>
#include <mpi.h>

#define TERMS_PER_PROCESS 100000

double nilakantha_sum(int start, int end) {
    double sum = 0.0;
    double sign = 1.0;
    for (int i = start; i <= end; ++i) {
        double denominator = 2.0 * i * (2.0 * i + 1) * (2.0 * i + 2);
        sum += sign * 4.0 / denominator;
        sign = -sign;
    }
    return sum;
}

int main(int argc, char *argv[]) {
    int rank, size;
    double partial_sum, total_sum;
    double pi = 3.0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Divide el trabajo entre los procesos MPI
    int start = rank * TERMS_PER_PROCESS + 1;
    int end = (rank + 1) * TERMS_PER_PROCESS;

    // Calcula la suma parcial en cada proceso
    partial_sum = nilakantha_sum(start, end);

    // Suma todas las sumas parciales
    MPI_Reduce(&partial_sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // El proceso 0 calcula el valor de pi
    if (rank == 0) {
        pi += total_sum;
        printf("Valor de pi: %.16f\n", pi);
    }

    MPI_Finalize();

    return 0;
}
