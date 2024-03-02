#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define TOTAL_PILOTS 20
#define TOTAL_AIRPLANES 10

sem_t airplaneSemaphore; // Semaphore to manage airplane availability

void* assignAirplane(void* arg) {
    int pilotId = *(int*)arg;
    sem_wait(&airplaneSemaphore); // Wait for an airplane to become available
    printf("Pilot %d is assigned an airplane.\n", pilotId);
    sleep(1); // Simulate preparation time for the flight
    printf("Pilot %d's airplane is now ready for takeoff.\n", pilotId);
    sem_post(&airplaneSemaphore); // Signal that the airplane is now ready for another pilot
    free(arg); // Free the allocated memory
    return NULL;
}

int main() {
    sem_init(&airplaneSemaphore, 0, TOTAL_AIRPLANES); // Initialize semaphore with the number of available airplanes

    pthread_t pilots[TOTAL_PILOTS]; // Thread identifiers for pilots

    // Create and start threads for each pilot
    for(int i = 0; i < TOTAL_PILOTS; i++) {
        int* pilotId = malloc(sizeof(int)); // Dynamically allocate memory for the pilot ID
        *pilotId = i; // Set pilot ID
        pthread_create(&pilots[i], NULL, assignAirplane, pilotId); // Start the thread
    }

    // Wait for all threads to complete
    for(int i = 0; i < TOTAL_PILOTS; i++) {
        pthread_join(pilots[i], NULL); // Wait for thread to finish
    }

    sem_destroy(&airplaneSemaphore); // Destroy semaphore
    printf("All pilots have been assigned airplanes.\n"); // All pilots are done
    return 0;
}
