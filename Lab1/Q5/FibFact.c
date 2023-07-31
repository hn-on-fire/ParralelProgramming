#include<stdio.h>
#include<mpi.h>
int fib(int n){
    return n==1?0:n==2?1:fib(n-1)+fib(n-1);
}
int fact(int n){
    return n==1||n==0?1:n*fact(n-1);
}
int main(int argc, char **argv){
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("Rank = %d, %d\n",rank, rank%2==0?fact(rank):fib(rank));
    MPI_Finalize();
    return 0;
}