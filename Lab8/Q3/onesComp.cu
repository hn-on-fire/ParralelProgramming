#include <stdio.h>
#include "cuda_runtime.h"
#include <bitset>
__global__ void mul(int* a,dim3 mat ){
    int n = threadIdx.y * mat.x + threadIdx.x;
    if(threadIdx.y != 0 && threadIdx.x != 0 && threadIdx.y != mat.y -1 && threadIdx.x != mat.x -1)
        a[n] =  (int) std::bitset<8>(~a[n]).to_ulong();
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
    dim3 mat(m,n);
    mul<<<1, mat>>>(a_d,mat);
    cudaMemcpy(a, a_d, sizeof(a), cudaMemcpyDeviceToHost);
    for(int i =0;i<n*m;i++){
        printf("5d ", a[i]);
        if((i+1)%m ==0)
            printf("\n");
    }
    printf("\n");
    fflush(stdout);
}