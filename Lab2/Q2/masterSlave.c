    #include <stdio.h>
    #include <mpi.h>
    #include <string.h>
    #include<stdlib.h>
    int main(int argc, char** argv){
        MPI_Init( &argc , &argv);
        int rank, recv, num=atoi(argv[1]), size;
        MPI_Comm_rank( MPI_COMM_WORLD , &rank);
        MPI_Comm_size( MPI_COMM_WORLD , &size);
        if(rank == 0){
            for(int i = 1;i<size;i++){
            MPI_Send( &num , 1, MPI_INT , i , 0 , MPI_COMM_WORLD);
            }
        }
        else{
                MPI_Recv( &recv , 1, MPI_INT , 0 , 0 , MPI_COMM_WORLD , MPI_STATUS_IGNORE);
                printf("Recieved: %d \n",  recv);
                fflush(stdout);
        }
        MPI_Finalize();
        return 0;
    }