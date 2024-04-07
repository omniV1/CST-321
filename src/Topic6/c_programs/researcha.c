#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PAGE_SIZE 4096 // 4KB page size
#define TLB_ENTRIES 64 // Number of TLB entries
#define INT_SIZE 4 // Size of an int in bytes
#define STEP_SIZE (PAGE_SIZE / INT_SIZE) // Jumping 1024 ints for a step size of 4KB
#define ARRAY_BLOCKS (TLB_ENTRIES + 1) // Use one more block of memory than the TLB can handle
#define ARRAY_SIZE (ARRAY_BLOCKS * STEP_SIZE) // Total array size

int main() {
    // Allocate an array large enough to cause TLB misses
    int *array = (int *)malloc(ARRAY_SIZE * sizeof(int));
    if (array == NULL) {
        perror("Memory allocation failed");
        return 1;
    }

    // Access pattern to cause TLB misses
    for (int i = 0; i < STEP_SIZE; i++) {
        for (int j = 0; j < ARRAY_BLOCKS; j++) {
            // Accessing the (j * STEP_SIZE + i)-th element to jump by page size each iteration
            array[j * STEP_SIZE + i] = i;
        }
    }

    // Optional: Read the array to cause TLB misses during reads
    volatile int read; // volatile to prevent compiler optimizations
    for (int i = 0; i < STEP_SIZE; i++) {
        for (int j = 0; j < ARRAY_BLOCKS; j++) {
            read = array[j * STEP_SIZE + i];
        }
    }

    // Cleanup
    free(array);
    printf("TLB miss pattern completed.\n");
    return 0;
}
