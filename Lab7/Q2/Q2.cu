#include <cuda_runtime.h>
#include <stdio.h>
#include <stdlib.h>
#define BLOCK_SIZE 4
__global__ void matMultiply(float *A, float *B, float *C, int rowsA, int colsA, int rowsB, int colsB) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int j = blockIdx.x * blockDim.y + threadIdx.y;
    printf("i  = %d, j = %d\n", threadIdx.y, blockDim.y);
    if (i >= rowsA || j >= colsB) return;
    float sum = 0;
    for (int k = 0; k < rowsB; ++k) {
        sum += A[i * rowsB + k] * B[k * colsB + j];
    }
    C[i * colsB + j] = sum;
}

int main() {
    int rows = 4;
    int cols = 4;
    size_t size = sizeof(float)*rows*cols;
    float *A, *B, *C, *d_A, *d_B, *d_C;
    cudaMalloc((void **)&d_A, size);
    cudaMalloc((void **)&d_B, size);
    cudaMalloc((void **)&d_C, size);
    A = (float*)malloc(size);
    B = (float*)malloc(size);
    C = (float*)malloc(size);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            A[i * cols + j] = i % 2 == 0 ? 1.0f : 1.0f;
        }
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            B[i * cols + j] = i % 2 == 0 ? 1.0f : 1.0f;
        }
    }

    cudaMemcpy(d_A, A, rows * cols * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, rows * cols * sizeof(float), cudaMemcpyHostToDevice);

    int blocksPerGrid = (rows + BLOCK_SIZE - 1) / BLOCK_SIZE;
    dim3 gridSize(blocksPerGrid, 1, 1);
    dim3 blockSize(rows, cols, 1);

    matMultiply<<<gridSize, blockSize>>>(d_A, d_B, d_C, rows, cols, rows, cols);

    cudaMemcpy(C, d_C, rows * cols * sizeof(float), cudaMemcpyDeviceToHost);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%f ", C[i * cols + j] );
        }
        printf("\n");
    }

    cudaFree(A);
    cudaFree(B);
    cudaFree(C);

    return 0;
}