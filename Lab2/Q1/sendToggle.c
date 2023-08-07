    #include <stdio.h>
    #include <mpi.h>
    #include <string.h>
    #include<stdlib.h>
    int main(int argc, char** argv){
        MPI_Init( &argc , &argv);
        int rank;
        MPI_Comm_rank( MPI_COMM_WORLD , &rank);
        int  len= strlen(argv[1]);
        //printf("%s %d\n", argv[1], rank);
        char *str = argv[1];
        char str1[15] = "";
        if(rank == 0){
            MPI_Send( str , len+1, MPI_CHAR , 1 , 1 , MPI_COMM_WORLD);
        for(int i =2;i<len+2;i++){
                MPI_Recv( str , len , MPI_CHAR , 1 , i, MPI_COMM_WORLD , MPI_STATUS_IGNORE);
                printf("%s\n", str);
                fflush(stdout);
            
        }}
        if(rank ==1){
                MPI_Recv( str1 , len+1, MPI_CHAR , 0 , 1, MPI_COMM_WORLD , MPI_STATUS_IGNORE);
                printf("Recieved: %d %s \n", len, str1);
                fflush(stdout);
            for(int i =2;i<len+2;i++){
                str[i-2] = str[i-2] +32;
                MPI_Send( str , len, MPI_CHAR , 0 , i, MPI_COMM_WORLD);
            }
        }
        MPI_Finalize();
        return 0;
    }