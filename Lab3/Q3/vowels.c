#include <mpi.h>
#include<stdlib.h>
#include <stdio.h>
#include<string.h>
int main(int argc, char *argv[])
{
    int rank,size, M;
    char str[20], rec[5];
   
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
     int A[size], c ;
    if(rank == 0){
        printf("Enter String:");
        fgets(str, 20, stdin);
    }
    MPI_Bcast( str , 20 , MPI_CHAR , 0 , MPI_COMM_WORLD);
    MPI_Scatter( str , 5 , MPI_CHAR , rec , 5, MPI_CHAR , 0 , MPI_COMM_WORLD);
    c =0;
    for(int i =0;i<5;i++){
        if(rec[i] == 'a' || rec[i] =='e' || rec[i] =='i' || rec[i] =='o' || rec[i] =='u' )
            ++c;

    }
    MPI_Gather( &c , 1 , MPI_INT , A , 1 , MPI_INT , 0 , MPI_COMM_WORLD);
    MPI_Barrier( MPI_COMM_WORLD);
    if(rank == 0){
        c = 0;
        for(int i =0;i<size;i++){
            printf("A[i] = %d\n", A[i]);
            fflush(stdout);
            c+=A[i];
        }
        printf("Total = %d\n", c);
        fflush(stdout);
    }
}