#include <stdio.h>
#include <stdlib.h>  // Include for rand() and srand()
#include <time.h>    // Include for time()
#include <omp.h>

#define SIZE 1000  // Size of the array
#define MAX_VALUE 100  // Maximum value in the array

int main() {
    int array[SIZE];  // Input array
    int count[MAX_VALUE + 1] = {0};  // Count array for occurrences
    int mode = 0;  // Variable to store the mode
    int maxCount = 0;  // Variable to store the maximum count

    // Initialize the array with random values
    srand(time(NULL));  // Seed the random number generator
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % (MAX_VALUE + 1);
    }

    // Start measuring execution time
    double start_time = omp_get_wtime();

    // Parallel region with static scheduling
     #pragma omp parallel num_threads(2)
    // #pragma omp parallel num_threads(4)
    {
        int thread_id = omp_get_thread_num();
        int local_freq[MAX_VALUE + 1] = {0}; // Local frequency array for each thread

        // Static scheduling
        #pragma omp for schedule(static)
        for (int i = 0; i < SIZE; i++) {
            local_freq[array[i]]++; // Increment the local frequency of the element
        }

        // Combine results from all threads
        #pragma omp critical
        {
            for (int i = 0; i <= MAX_VALUE; i++) {
                count[i] += local_freq[i];
                if (count[i] > maxCount) {
                    maxCount = count[i];
                    mode = i; // Update mode
                }
            }
        }
    }

    // End measuring execution time
    double end_time = omp_get_wtime();
    double execution_time = end_time - start_time;

    printf("Mode value: %d\n", mode);
    printf("Execution time: %f seconds\n", execution_time);
    
    return 0;
}