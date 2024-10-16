#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h> // AVX2

#define n 128  // Increase the tensor size
#define NUM_ITERATIONS 100  // Number of iterations to amplify the effect

void regular_tensor_multiply(double A[n][n][n], double B[n][n][n], double C[n][n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j][k] = A[i][j][k] * B[i][j][k];
            }
        }
    }
}

void simd_tensor_multiply(double A[n][n][n], double B[n][n][n], double C[n][n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k += 4) { // Process 4 elements at a time
                __m256d vecA = _mm256_loadu_pd(&A[i][j][k]);
                __m256d vecB = _mm256_loadu_pd(&B[i][j][k]);
                __m256d vecC = _mm256_mul_pd(vecA, vecB);
                _mm256_storeu_pd(&C[i][j][k], vecC);
            }
        }
    }
}

int main() {
    double A[n][n][n], B[n][n][n], C[n][n][n];

    // Initialize tensors with random values
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                A[i][j][k] = (double)rand() / RAND_MAX;
                B[i][j][k] = (double)rand() / RAND_MAX;
            }
        }
    }

    clock_t start, end;

    // Time regular tensor multiplication
    start = clock();
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        regular_tensor_multiply(A, B, C);
    }
    end = clock();
    double time_taken_regular = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Time taken for regular tensor multiplication: %.2f seconds\n", time_taken_regular);

    // Time SIMD tensor multiplication
    start = clock();
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        simd_tensor_multiply(A, B, C);
    }
    end = clock();
    double time_taken_simd = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Time taken for SIMD tensor multiplication (AVX2): %.2f seconds\n", time_taken_simd);

    return 0;
}
