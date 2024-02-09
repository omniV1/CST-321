// Owen Lindsey
// CST-321
// This was done with the help of
//

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// Function for the 'Pilot' thread
void *pilot(void *arg) {
    for (int i = 0; i < 10; i++) {
        printf("Pilot: Navigating through checkpoint %d\n", i + 1);
        sleep(1); // Simulate the time taken to reach the next checkpoint
    }
    printf("Pilot: Journey complete, preparing for landing.\n");
    return NULL;
}

// Function for the 'Maintainer' thread
void *maintainer(void *arg) {
    for (int i = 0; i < 10; i++) {
        printf("Maintainer: Performing maintenance round %d\n", i + 1);
        sleep(2); // Simulate the time taken for maintenance tasks
    }
    printf("Maintainer: All systems checked, ready for the next flight.\n");
    return NULL;
}

int main() {
    pthread_t pilotThread, maintainerThread;

    // Create threads
    pthread_create(&pilotThread, NULL, pilot, NULL);
    pthread_create(&maintainerThread, NULL, maintainer, NULL);

    // Wait for threads to finish
    pthread_join(pilotThread, NULL);
    pthread_join(maintainerThread, NULL);

    printf("Main: The flight crew has completed their duties.\n");

    return 0;
}
