#include <mpi.h>
#include<stdlib.h>
#include <stdio.h>
#include <math.h>
double calc(int i, int n){
    return 4.0/(1+((i-0.5)*(i-0.5)/(n*n)));
}
int main(int argc, char *argv[])
{
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    double A[size],c,d;
    if(rank ==0){
        for (int i = 0; i < size; i++)
        {
            A[i] = calc(i, size);
        }
        
    }
    MPI_Scatter( A , 1 , MPI_DOUBLE , &c , 1 , MPI_DOUBLE , 0, MPI_COMM_WORLD);
    MPI_Scan( &c , &d, 1 , MPI_DOUBLE , MPI_SUM , MPI_COMM_WORLD);
    if(rank==size-1){
    d/=(size);
    printf("Rank = %d; Pi = %lf; Error = %lf\n", rank, d,M_PI-d);
    
    }
    MPI_Finalize();
    return 0;}