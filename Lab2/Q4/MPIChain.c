    #include <stdio.h>
    #include <mpi.h>
    #include <string.h>
    #include<stdlib.h>
    int main(int argc, char** argv){
        MPI_Init( &argc , &argv);
        int rank, recv, num=atoi(argv[1]), size;
        MPI_Comm_rank( MPI_COMM_WORLD , &rank);
        MPI_Comm_size( MPI_COMM_WORLD , &size);
        if(rank ==0 ){
            MPI_Send( &num , 1, MPI_INT , 1 , 0 , MPI_COMM_WORLD);
            MPI_Recv( &recv , 1, MPI_INT , size-1 , 0 , MPI_COMM_WORLD , MPI_STATUS_IGNORE);
            printf("%d; Rank = %d\n", recv, rank);fflush(stdout);
        }
        else if(rank!=size-1){
                MPI_Recv( &recv , 1, MPI_INT , rank-1 , 0 , MPI_COMM_WORLD , MPI_STATUS_IGNORE);
                recv+=1;
                MPI_Send( &recv , 1, MPI_INT , rank+1 , 0 , MPI_COMM_WORLD);
                
        }
        else{
            MPI_Recv( &recv , 1, MPI_INT , rank-1 , 0 , MPI_COMM_WORLD , MPI_STATUS_IGNORE);
                recv+=1;
            MPI_Send( &recv , 1, MPI_INT , 0 , 0 , MPI_COMM_WORLD);

        }
        MPI_Finalize();
        return 0;
    }