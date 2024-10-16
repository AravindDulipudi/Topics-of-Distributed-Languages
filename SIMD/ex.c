#include <stdio.h>
#include <immintrin.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000

void elementwise_multiply(double *a, double *b, double *result, int n) {
    for (int i = 0; i < n; i++) {
        result[i] = a[i] * b[i];
    }
}

void simd_elementwise_multiply(double *a, double *b, double *result, int n) {
    int i;
    for (i = 0; i <= n-4; i += 4) {
        __m256d vec_a = _mm256_loadu_pd(&a[i]);
        __m256d vec_b = _mm256_loadu_pd(&b[i]);
        __m256d vec_res = _mm256_mul_pd(vec_a, vec_b);
        _mm256_storeu_pd(&result[i], vec_res);
    }

    // Handle any remaining elements
    for (; i < n; i++) {
        result[i] = a[i] * b[i];
    }
}

int main() {
    double *a = malloc(N * sizeof(double));
    double *b = malloc(N * sizeof(double));
    double *result = malloc(N * sizeof(double));

    for (int i = 0; i < N; i++) {
        a[i] = (double)rand() / RAND_MAX;
        b[i] = (double)rand() / RAND_MAX;
    }

    clock_t start, end;

    // Regular multiplication
    start = clock();
    elementwise_multiply(a, b, result, N);
    end = clock();
    printf("Regular multiplication time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    // SIMD multiplication
    start = clock();
    simd_elementwise_multiply(a, b, result, N);
    end = clock();
    printf("SIMD multiplication time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    free(a);
    free(b);
    free(result);

    return 0;
}
