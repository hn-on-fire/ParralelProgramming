    #include <stdio.h>
    #include <mpi.h>
    #include <string.h>
    #include<stdlib.h>
    int main(int argc, char** argv){
        MPI_Init( &argc , &argv);
        int rank, size, n = atoi(argv[1]);
        MPI_Comm_rank( MPI_COMM_WORLD , &rank);
        void* ptr = malloc(sizeof(int)*500);
        MPI_Buffer_attach(  ptr , sizeof(int)*500);
        int arr[n], recv;
        if(rank == 0){
            printf("Enter %d elements: \n", n);
            for (int i = 0; i < n; i++)
            {
                scanf("%d", &arr[i]);
            }
            for(int i =0;i<n;i++){
            MPI_Bsend( &arr[i] , 1 , MPI_INT , i+1 , 0, MPI_COMM_WORLD);
            
        }}
        else{
                MPI_Recv( &recv , 1, MPI_INT , 0 , 0 , MPI_COMM_WORLD , MPI_STATUS_IGNORE);
                printf("Recieved: %d; Rank = %d; Out = %d\n",  recv, rank, rank%2==0?recv*recv: recv*recv*recv);
        }
        MPI_Finalize();
        return 0;
    }