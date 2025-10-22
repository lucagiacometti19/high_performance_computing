#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int rank, size;
    int data;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        data = 191;
    }
    else
    {
        MPI_Recv(&data, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    
    int step = 1;
    while (step < size)
    {
        if (rank % (2 * step) == 0)
        {
            int dst = rank + step;
            if (dst < size)
            {
                MPI_Send(&data, 1, MPI_INT, dst, 0, MPI_COMM_WORLD);
            }
        }
        step *= 2;
    }

    printf("Process %d received data: %d\n", rank, data);
    MPI_Finalize();
    return 0;
}