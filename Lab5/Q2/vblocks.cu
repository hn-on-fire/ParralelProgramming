#include <stdio.h>

#define N 10

__global__
void add_vectors(double *a, double *b, double *c)
{
	int id = blockDim.x * blockIdx.x + threadIdx.x;
	if(id < N) c[id] = a[id] + b[id];
}
int main()
{
	size_t bytes = N*sizeof(double);
	double *A = (double*)malloc(bytes);
	double *B = (double*)malloc(bytes);
	double *C = (double*)malloc(bytes);

	double *d_A, *d_B, *d_C;
	cudaMalloc(&d_A, bytes);
	cudaMalloc(&d_B, bytes);
	cudaMalloc(&d_C, bytes);
	for(int i=0; i<N; i++)
	{
		A[i] = 1.0;
		B[i] = 2.0;
	}
	cudaMemcpy(d_A, A, bytes, cudaMemcpyHostToDevice);
	cudaMemcpy(d_B, B, bytes, cudaMemcpyHostToDevice);
	add_vectors<<< ceil( float(N) / 256 ) ,256 >>>(d_A, d_B, d_C);

	cudaMemcpy(C, d_C, bytes, cudaMemcpyDeviceToHost);

	free(A);
	free(B);
	free(C);
	for(int i =0;i<N;i++){
		printf(" %lf %lf %lf ",A[i], B[i], C[i]);
	}
	cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);

	printf("\n---------------------------\n");
	printf("__SUCCESS__\n");


	return 0;
}