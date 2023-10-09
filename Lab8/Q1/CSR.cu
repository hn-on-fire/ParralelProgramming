#include <stdio.h>
#include "cuda_runtime.h"

__global__ void mul(int* a1, int* a2, int* o, int len){
    int n =threadIdx.x;
    o[n] = a1[n]*a2[n];
}

int main(){
    printf("Enter mat dim: ");
    int m,n;
    scanf("%d %d", &m,&n);
    int l1 = 0, l2 = 0;
    int a1[20], a2[20];
    printf("Enter Elements");
    for (int i = 0; i < m*n; i++)
    {
        scanf("%d", &a1[l1]);
        if(a1[l1]!=0){
            l1++;
        }
    }
    printf("Enter mat dim: ");
    scanf("%d %d", &m,&n);
    printf("Enter Elements");
    for (int i = 0; i < m*n; i++)
    {
        scanf("%d", &a2[l2]);
        if(a2[l2]!=0){
            l2++;
        }
    }

    int *a1_d, *a2_d, *o;
    int o_h[20];
    cudaMalloc((void**)&a1_d, sizeof(a1));
    cudaMalloc((void**)&a2_d, sizeof(a1));
    cudaMalloc((void**)&o, sizeof(a1));
    cudaMemcpy(a1_d, a1, sizeof(a1), cudaMemcpyHostToDevice);
    cudaMemcpy(a2_d, a2, sizeof(a2), cudaMemcpyHostToDevice);
    fflush(stdout);
    mul<<<1, l1>>>(a1_d,a2_d, o, l1);
    cudaMemcpy(o_h, o, sizeof(a1), cudaMemcpyDeviceToHost);
    for(int i =0;i<l1;i++){
        printf("%d ", o_h[i]);
    }
    printf("\n");
    fflush(stdout);
}