#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TOTAL_PILOTS 20
#define TOTAL_AIRPLANES 10

int airplanesAvailable = TOTAL_AIRPLANES; // Counter for available airplanes

void* attemptToAssignAirplane(void* arg) {
    int pilotId = *(int*)arg;
    if (airplanesAvailable > 0) {
        printf("Pilot %d attempts to get an airplane.\n", pilotId);
        // Simulate the delay in getting to the airplane
        sleep(1);
        airplanesAvailable--; // Unsafely decrement the count of available airplanes
        printf("Pilot %d is assigned an airplane. Airplanes left: %d\n", pilotId, airplanesAvailable);
        // Simulate the flight preparation time
        sleep(1);
        airplanesAvailable++; // Unsafely increment the count, assuming the airplane is back
    } else {
        printf("Pilot %d cannot find an available airplane.\n", pilotId);
    }
    free(arg);
    return NULL;
}

int main() {
    pthread_t pilots[TOTAL_PILOTS]; // Thread identifiers for pilots

    // Attempt to start threads for each pilot without proper synchronization
    for(int i = 0; i < TOTAL_PILOTS; i++) {
        int* pilotId = malloc(sizeof(int));
        *pilotId = i;
        pthread_create(&pilots[i], NULL, attemptToAssignAirplane, pilotId);
    }

    // Wait for all pilots to complete their attempts
    for(int i = 0; i < TOTAL_PILOTS; i++) {
        pthread_join(pilots[i], NULL);
    }

    printf("All pilots have attempted to get airplanes.\n");
    return 0;
}
