#include "/usr/include/mpich/mpi.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool isPrime(int n)
{
    int d;

    for(d=2; d*d<=n; d++) {
        if (n % d == 0) {
            return false;
        }
    }

    return true;
}

int getPrimeByPosition(int Position)
{
    int counter = 0;
    int number = 1;

    while(counter < Position) {
        number++;

        if (isPrime(number)) {
            counter++;
        }
    }

    return number;
}

int writePrimeNumbers(int N, int prime)
{
    if (N % prime == 0) {
        printf("%d\n", prime);
        N = N/prime;
        writePrimeNumbers((N), prime);
    } else {
        return N;
    }
}

int main(int argc, char** argv) {
    int N = atof(argv[1]);

    int size;
    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int i;
    if (rank != 0) {
        MPI_Send(&N, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else {
        for (i=1; i < size; i++) {
            N = writePrimeNumbers(N, getPrimeByPosition(i));
            MPI_Recv(&N, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
        }
    }

    // Finalize the MPI environment. No more MPI calls can be made after this
    MPI_Finalize();
}
