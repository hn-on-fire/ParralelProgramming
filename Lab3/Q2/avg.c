#include <mpi.h>
#include<stdlib.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    int rank,size, M;
    char str[20];
    int A[10], recv[10] ;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    float c =0, B[3];
    if(rank==0){
        printf("Enter M:");
        fflush(stdin);
        scanf("%d", &M);
        fflush(stdout);
        printf("Enter %d elements:", M*size);
        for(int i=0;i<M*size;i++){
            scanf("%d",&A[i]);
        }
    }
    MPI_Bcast( &M , 1 , MPI_INT , 0 , MPI_COMM_WORLD);
    MPI_Scatter( A , M , MPI_INT , recv , M , MPI_INT , 0 , MPI_COMM_WORLD);
    for(int i=0;i<M;i++){
        c+=recv[i];
    }
    c=c/M;
    MPI_Gather( &c , 1 , MPI_FLOAT , B , 1 , MPI_FLOAT , 0 , MPI_COMM_WORLD);
    if(rank == 0){
        c = 0;
        for(int i=0;i<size;i++){
            c+=B[i];
        }
        printf("%lf", c/size);
        fflush(stdout);
    }
    
}