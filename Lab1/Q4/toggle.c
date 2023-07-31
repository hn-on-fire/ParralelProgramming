#include <stdio.h>
#include <mpi.h>
#include<stdlib.h>
int main(int argc, char **argv){
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    char tog[6] = "HELLO";
    tog[rank] = tog[rank] + 32;
    printf("%s\n",tog);
    MPI_Finalize();
    return 0;
}   