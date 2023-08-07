    #include <stdio.h>
    #include <mpi.h>
    #include <string.h>
    #include<stdlib.h>
    int main(int argc, char** argv){
        MPI_Init( &argc , &argv);
        int rank, num=1;
        MPI_Comm_rank( MPI_COMM_WORLD , &rank);
        if(rank == 0){
            MPI_Ssend( &num , 1, MPI_INT , 1 , 0 , MPI_COMM_WORLD);
            MPI_Recv( &num , 1, MPI_INT , 1 , 0 , MPI_COMM_WORLD , MPI_STATUS_IGNORE);
            }
        
        else{
                MPI_Ssend( &num , 1, MPI_INT , 0 , 0 , MPI_COMM_WORLD);
                MPI_Recv( &num , 1, MPI_INT , 0 , 0 , MPI_COMM_WORLD , MPI_STATUS_IGNORE);
                printf("%d", num);
        }
        MPI_Finalize();
        return 0;
    }