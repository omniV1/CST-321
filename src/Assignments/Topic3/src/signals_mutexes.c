// Owen Lindsey
// CSt-321
// This assignment was completed with the help of
// Reha, M. , (2024). Activity 3 Assignment guide: https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582473094
//Reha, M. (2024). Topic 3 Lecture : https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582472940
// Frasier, B. (2015). Mutex Synchronization in Linux with Pthreads. Youtube: https://www.youtube.com/watch?v=GXXE42bkqQk

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define RUN_TIME_MINUTES 1 // Specify run time in minutes

pthread_mutex_t mutex;
int counter = 0; // Global counter variable
int run_time_seconds; // Total run time in seconds

// Counter thread function
void* counter_thread_func(void* arg) {
    int elapsed_time = 0;
    while (elapsed_time < run_time_seconds) {
        pthread_mutex_lock(&mutex); // Lock the mutex
        counter++; // Increment the counter
        printf("Counter incremented to: %d\n", counter);
        sleep(1); // Sleep for 1 second with the mutex locked
        pthread_mutex_unlock(&mutex); // Unlock the mutex after sleeping
        elapsed_time++;
    }
    return NULL;
}

// Monitor thread function
void* monitor_thread_func(void* arg) {
    int misses = 0;
    int elapsed_time = 0;
    while (elapsed_time < run_time_seconds) {
        if (pthread_mutex_trylock(&mutex) == 0) { // Try to lock the mutex
            printf("Monitor read: Counter value: %d\n", counter);
            pthread_mutex_unlock(&mutex); // Unlock the mutex
        } else {
            misses++; // Increment misses if the mutex is locked
        }
        sleep(3); // Sleep for 3 seconds
        elapsed_time += 3;
    }
    printf("Total misses by monitor thread: %d\n", misses);
    return NULL;
}

int main() {
    pthread_t counter_thread, monitor_thread;
    pthread_mutex_init(&mutex, NULL); // Initialize the mutex

    run_time_seconds = RUN_TIME_MINUTES * 60; // Convert run time from minutes to seconds

    // Create the counter and monitor threads
    pthread_create(&counter_thread, NULL, counter_thread_func, NULL);
    pthread_create(&monitor_thread, NULL, monitor_thread_func, NULL);

    // Wait for both threads to finish
    pthread_join(counter_thread, NULL);
    pthread_join(monitor_thread, NULL);

    // Clean up and exit
    pthread_mutex_destroy(&mutex);
    printf("Main program finished.\n");
    return 0;
}
