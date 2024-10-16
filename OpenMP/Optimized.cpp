#include <bits/stdc++.h>
#include <omp.h> // Include OpenMP library
using namespace std;
using namespace chrono;

const int MOD = 1000000007;
const int SIZE = 300000000;

vector<long long> fact;

// Function to calculate the factorial for a range [start, end]
void factorial(int start, int end)
{
    for (int i = start; i <= end; i++)
    {
        long long result = 1LL;
        for (int j = 1; j <= i; j++)
        {
            result = (result * j) % MOD;
        }
        fact[i] = result;
    }
}

int main()
{
    // Initialize the vector with zeros
    fact.resize(SIZE + 1, 0);

    // Start measuring time
    auto start_time = high_resolution_clock::now();

    // Function to store factorial values mod 10^9+7 using OpenMP
    #pragma omp parallel for num_threads(4)
    for (int i = 1; i <= SIZE; i++)
    {
        factorial(i, i);
    }

    // End measuring time
    auto end_time = high_resolution_clock::now();

    // Calculate the elapsed time in seconds
    auto execution_time = duration_cast<seconds>(end_time - start_time);

    cout << "Execution time: " << execution_time.count() << " seconds" << endl;

    return 0;
}
