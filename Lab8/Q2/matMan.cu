#include <stdio.h>
#include "cuda_runtime.h"

__global__ void mul(int* a,int len){
    int n = threadIdx.y*len + threadIdx.x;
    if(threadIdx.y == 1)
        a[n] = a[n]*a[n];
    else if(threadIdx.y == 2)
        a[n] = a[n]*a[n]*a[n];
}

int main(){
    printf("Enter mat dim: ");
    int m,n;
    scanf("%d %d", &m,&n);
    int a[20];
    printf("Enter Elements");
    for (int i = 0; i < m*n; i++)
    {
        scanf("%d", &a[i]);
    }
    int *a_d;
    cudaMalloc((void**)&a_d, sizeof(a));
    cudaMemcpy(a_d, a, sizeof(a), cudaMemcpyHostToDevice);
    dim3 mat(3,3);
    mul<<<1, mat>>>(a_d,n);
    cudaMemcpy(a, a_d, sizeof(a), cudaMemcpyDeviceToHost);
    for(int i =0;i<n*m;i++){
        printf("%d ", a[i]);
        if((i+1)%m ==0)
            printf("\n");
    }
    printf("\n");
    fflush(stdout);
}