#include <mpi.h>
#include<stdlib.h>
#include <stdio.h>
int fact(int n){
    return n<=1?1:n*fact(n-1);
}
int main(int argc, char *argv[])
{
    int rank,size, c;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int A[size], B[size];
    if(rank==0){
        printf("Enter %d elements:", size);
        for(int i =0;i<size;i++){
            scanf("%d", &A[i]);
        }
    }
        MPI_Scatter( A , 1 , MPI_INT , &c , 1 , MPI_INT , 0 , MPI_COMM_WORLD);
        c=fact(c);
        MPI_Gather(&c, 1 , MPI_INT , B , 1 , MPI_INT , 0 , MPI_COMM_WORLD);
    if(rank==0){
        c = 0;
        for(int i =0;i<size;i++)
            c+=B[i];
        printf("Result = %d\n", c);
        fflush(stdout);
    }
}