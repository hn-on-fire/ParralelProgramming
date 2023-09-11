#include <mpi.h>
#include<stdlib.h>
#include <stdio.h>
#include <math.h>
int main(int argc, char *argv[])
{
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int A[4][4],c,d, row, prt;
    if(rank ==0){
        printf("Enter Elements: ");
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                scanf("%d", &A[i][j]);
            }
            
        }

    }
    MPI_Scatter( A , 4 , MPI_INT , row , 4 , MPI_INT , 0 , MPI_COMM_WORLD);
   //MPI_Scan( A , row , 4 , MPI_INT , MPI_SUM , MPI_COMM_WORLD);
    MPI_Reduce( row , &prt , 1 , MPI_INT , MPI_SUM , 0 , MPI_COMM_WORLD);
    MPI_Barrier( MPI_COMM_WORLD);
    for(int i=0;i<4;i++){
        printf( "%d ", prt);
    }
    printf("\n");
    MPI_Finalize();
    return 0;}