#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
__global__ void add(int *a, int *t1, int *t2)
{
int n=threadIdx.x, m=blockIdx.x, size=blockDim.x;
a[m*size+n]=t1[m*size+n]+t2[m*size+n];
}
int main(void)
{
int *a,*t1, *t2, m,n,i,j;
int *d_a,*d_t1, *d_t2;
printf("Enter the value of m: ");scanf("%d",&m);
printf("Enter the value of n: ");scanf("%d",&n);
int size=sizeof(int)*m*n;
a=(int*)malloc(m*n*sizeof(int));
t1=(int*)malloc(m*n*sizeof(int));
t2=(int*)malloc(m*n*sizeof(int));
printf("Enter input matrix:\n");
for(i=0;i<m*n;i++)
scanf("%d",&t1[i]);
printf("Enter input matrix:\n");
for(i=0;i<m*n;i++)
scanf("%d",&t2[i]);
cudaMalloc((void**)&d_a,size);
cudaMalloc((void**)&d_t1,size);
cudaMalloc((void**)&d_t2,size);
cudaMemcpy(d_t1,t1,size,cudaMemcpyHostToDevice);
cudaMemcpy(d_t2,t2,size,cudaMemcpyHostToDevice);
add<<<m,n>>>(d_a,d_t1, d_t2);
cudaMemcpy(a,d_a,size,cudaMemcpyDeviceToHost);
printf("Result vector is:\n");
for(i=0;i<n;i++)
{
for(j=0;j<m;j++)
printf("%d\t",a[i*m+j]);
printf("\n");
}
getchar();
cudaFree(d_a);
cudaFree(d_t1);
cudaFree(d_t2);
}