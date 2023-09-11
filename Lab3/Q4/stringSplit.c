#include <mpi.h>
#include<stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank,size, c;
    char *s1= "hellos", *s2 = "worlds", r1[3], r2[3],s[6], recv[12];
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Scatter( s1 , 3 , MPI_CHAR , r1 , 3 , MPI_CHAR , 0 , MPI_COMM_WORLD);
    MPI_Scatter( s2 , 3 , MPI_CHAR , r2 , 3 , MPI_CHAR , 0 , MPI_COMM_WORLD);
    for(int i =0;i<3;i++){
        s[i*2] = s1[i];
        s[i*2 + 1] = s2[i];
    }
    MPI_Gather( s , 6 , MPI_CHAR , recv , 6 , MPI_CHAR , 0 , MPI_COMM_WORLD);
    if(rank ==0)
    printf("%s", recv);