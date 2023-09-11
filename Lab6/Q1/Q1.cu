#include <iostream>
#include <cuda_runtime.h>
#define BLOCK_SIZE 1

__global__ void countWords(int* wordFrequencies, char* sentence, int sentenceLength, char* word, int wordLength) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= sentenceLength-wordLength) return;

    char currChar = sentence[idx];
    int wordStart = 0;
    for(int i =0; i<wordLength; i++){
        if(word[i]!= sentence[idx+i])
        return;
    }
    atomicAdd(wordFrequencies, 1);
}

int main() {
    char sentence[] = "The quick brown fox jumps over the lazy dog", *d_s;
    int sentenceLength = strlen(sentence), d_sl;
    char word[] = "fox", *d_word;
    int wordLength = strlen(word), *d_wl;

    int wordFrequencies, *d_wf;
    cudaMalloc((void**)&d_wf, sizeof(int));
    cudaMalloc((void**)&d_word, sizeof(char)*wordLength);
    cudaMalloc((void**)&d_s, sizeof(char)*sentenceLength);
    cudaMalloc((void**)&d_sl, sizeof(int));
    int numBlocks = (sentenceLength + BLOCK_SIZE - 1) / BLOCK_SIZE;
    cudaMemcpy(d_s, sentence, sizeof(char)*sentenceLength, cudaMemcpyHostToDevice);
    cudaMemcpy(d_word, word, sizeof(char)*wordLength, cudaMemcpyHostToDevice);
    cudaMemcpy(d_wf, wordFrequencies, sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_word, word, sizeof(char)*wordLength, cudaMemcpyHostToDevice);
    cudaMemcpy(d_word, word, sizeof(char)*wordLength, cudaMemcpyHostToDevice);
    countWords<<<numBlocks, BLOCK_SIZE>>>(&wordFrequencies,sentence, sentenceLength, word, wordLength);

    cudaDeviceSynchronize();

    

    printf("Max frequency of %s in %s is %d\n", word, sentence, maxFrequency);

    cudaFree(wordFrequencies);
    return 0;
}