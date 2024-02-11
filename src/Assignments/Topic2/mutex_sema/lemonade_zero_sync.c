#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define KIDS 5
#define USES 3

// Global variables to simulate shared resources
int refrigeratorOpen = 0; // Represents if the refrigerator is being used
int availableCups = 2; // Simulates a limited number of cups

// Thread function to simulate kids serving lemonade without synchronization
void* serveLemonade(void* arg) {
    int kidId = *(int*)arg;
    for (int i = 0; i < USES; i++) {
        // Attempt to use the refrigerator
        if (!refrigeratorOpen) {
            refrigeratorOpen = 1; // Refrigerator is now being used
            printf("Kid %d is using the refrigerator.\n", kidId);
            sleep(1); // Simulate time to get lemonade
            refrigeratorOpen = 0; // Done using the refrigerator
            printf("Kid %d is done with the refrigerator.\n", kidId);
        } else {
            printf("Kid %d couldn't use the refrigerator because it's already in use.\n", kidId);
        }

        // Attempt to serve lemonade
        if (availableCups > 0) {
            availableCups--; // Take a cup
            printf("Kid %d is serving lemonade. Cups left: %d\n", kidId, availableCups);
            sleep(1); // Simulate serving time
            availableCups++; // Return the cup
        } else {
            printf("Kid %d couldn't serve lemonade because there are no cups available.\n", kidId);
        }
    }
    free(arg); // Clean up dynamically allocated memory
    return NULL;
}

int main() {
    pthread_t kids[KIDS];

    // Create threads for each kid
    for (int i = 0; i < KIDS; i++) {
        int* kidId = malloc(sizeof(int));
        *kidId = i;
        if(pthread_create(&kids[i], NULL, serveLemonade, kidId) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Wait for all kids to finish
    for (int i = 0; i < KIDS; i++) {
        pthread_join(kids[i], NULL);
    }

    printf("All kids are done serving lemonade.\n");
    return 0;
}
