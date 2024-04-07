#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define RUN_TIME_MINUTES 1 // Run for 1 minute

int counter = 0; // Global counter variable
int run_time_seconds; // Global variable for run time in seconds

// Counter thread function
void* counter_thread_func(void* arg) {
    int elapsed_time = 0;
    while (elapsed_time < run_time_seconds) {
        counter++; // Increment the counter without mutex protection
        printf("Counter thread: counter = %d\n", counter);
        sleep(1); // Sleep for 1 second
        elapsed_time += 1;
    }
    return NULL;
}

// Monitor thread function
void* monitor_thread_func(void* arg) {
    int misses = 0;
    int elapsed_time = 0;
    while (elapsed_time < run_time_seconds) {
        // Access the counter without mutex protection
        int current_counter = counter; // Read the counter value
        // No mutex lock, so we cannot guarantee the counter won't change
        if (current_counter != counter) {
            // If the counter changed during reading, increment the misses
            misses++;
        } else {
            printf("Monitor thread: counter = %d\n", counter);
        }
        sleep(3); // Sleep for 3 seconds
        elapsed_time += 3;
    }
    printf("Monitor thread missed %d times.\n", misses);
    return NULL;
}

int main() {
    pthread_t counter_thread, monitor_thread;

    run_time_seconds = RUN_TIME_MINUTES * 60; // Convert minutes to seconds

    // Create the counter and monitor threads without mutex synchronization
    pthread_create(&counter_thread, NULL, counter_thread_func, NULL);
    pthread_create(&monitor_thread, NULL, monitor_thread_func, NULL);

    // Wait for both threads to finish their work
    pthread_join(counter_thread, NULL);
    pthread_join(monitor_thread, NULL);

    // Without mutex cleanup since we're not using one
    printf("Main program finished. Counter = %d\n", counter);
    return 0;
}
