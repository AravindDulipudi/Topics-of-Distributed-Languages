#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 100000      // Number of computations
#define MAX_NUM 100  // Maximum number for factorial calculation
#define REPEAT 10000 // Number of repetitions for each factorial calculation

// Function to calculate factorial
long long factorial(int n) {
    long long fact = 1;
    for (int i = 2; i <= n; ++i) {
        fact *= i;
    }
    return fact;
}

int main() {
    int nums[N];
    long long results[N];
    double start_time, end_time, time_serial, time_parallel;

    srand(time(NULL)); 

    // Generating random numbers between 1 and MAX_NUM
    for (int i = 0; i < N; i++) {
        nums[i] = rand() % MAX_NUM + 1;
    }

    // Serial computation with repetitions
    start_time = omp_get_wtime();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < REPEAT; j++) {
            results[i] = factorial(nums[i]);
        }
    }
    end_time = omp_get_wtime();
    time_serial = end_time - start_time;

    // Parallel computation with repetitions
    start_time = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic) num_threads(6)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < REPEAT; j++) {
            results[i] = factorial(nums[i]);
        }
    }
    end_time = omp_get_wtime();
    time_parallel = end_time - start_time;

    // Output the results
printf("Serial execution  time: %.1f seconds\n", time_serial);
printf("Parallel execution time: %.1f seconds\n", time_parallel);

if (time_serial > 0) {
    printf("Optimized (parallel) code is %.1fx times faster than non-optimized (serial).\n", time_serial / time_parallel);
}

    return 0;
}