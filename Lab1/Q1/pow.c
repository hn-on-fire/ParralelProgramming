#include <stdio.h>
#include <mpi.h>
#include<stdlib.h>
#include <stdio.h>
#include <math.h>
int main(int argc, char **argv){
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("%d ^ %d = %lf\n", atoi(argv[1]), rank, pow(atoi(argv[1]), rank));
    MPI_Finalize();
    return 0;
}   