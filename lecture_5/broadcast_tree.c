#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv) {
    int rank, size;
    int data;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int step = 1;
    while (step < size) {
        if (rank % (2 * step) == 0) {
            int dst = rank + step;
            if (dst < size) {
                if (rank == 0) {
                    data = 42;
                    MPI_Send(&data, 1, MPI_INT, dst, 0, MPI_COMM_WORLD);
                } else {
                    MPI_Recv(&data, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    MPI_Send(&data, 1, MPI_INT, dst, 0, MPI_COMM_WORLD);
                }
            }
        } else {
            MPI_Recv(&data, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        step *= 2;
    }


    printf("Process %d received data: %d\n", rank, data);
    MPI_Finalize();
    return 0;
}