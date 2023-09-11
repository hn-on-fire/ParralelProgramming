#include <mpi.h>
#include<stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int A[size], c,d;
    if(rank==0){
    for(int i =0;i<size;i++)
        A[i] = i+1; }
    MPI_Scatter(A , 1 , MPI_INT, &c, 1 , MPI_INT , 0, MPI_COMM_WORLD);
   // MPI_Barrier(MPI_COMM_WORLD);
    MPI_Scan( &c , &d, 1 , MPI_INT , MPI_PROD , MPI_COMM_WORLD);
    printf("%d::%d\n",rank,d);
    MPI_Finalize();
    return 0;
}