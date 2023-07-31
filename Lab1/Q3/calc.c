#include <stdio.h>
#include <mpi.h>
#include<stdlib.h>
int main(int argc, char **argv){
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    switch(rank%4){
        case 0:
            printf("%d + %d = %d\n", atoi(argv[1]), atoi(argv[2]), atoi(argv[1]) + atoi(argv[2]));
            break;
        case 1:
            printf("%d - %d = %d\n", atoi(argv[1]), atoi(argv[2]), atoi(argv[1]) - atoi(argv[2]));
            break;
        case 2:
            printf("%d * %d = %d\n", atoi(argv[1]), atoi(argv[2]), atoi(argv[1])* atoi(argv[2]));
            break;
        case 3:
            printf("%d / %d = %d\n", atoi(argv[1]), atoi(argv[2]), atoi(argv[1]) / atoi(argv[2]));
            break;
    }
    MPI_Finalize();
    return 0;
}   