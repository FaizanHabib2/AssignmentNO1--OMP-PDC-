#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define N 1000000 // Size of the array
#define MAX_VALUE 100 // Assuming values are between 0 and 99

int find_mode(int arr[], int size) {
    int freq[MAX_VALUE] = {0}; // Frequency array initialized to 0
    int mode = arr[0];
    int max_count = 0;

    for (int i = 0; i < size; i++) {
        freq[arr[i]]++; // Increment the frequency of the element
        if (freq[arr[i]] > max_count) {
            max_count = freq[arr[i]];
            mode = arr[i]; // Update mode
        }
    }

    return mode;
}

int main() {
    int arr[N];

    // Initialize the array with random values
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % MAX_VALUE; // Random values between 0 and 99
    }

    clock_t start = clock();
    int mode = find_mode(arr, N);
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Mode value: %d\n", mode);
    printf("Time taken for sequential execution: %f seconds\n", time_taken);
    
    return 0;
}