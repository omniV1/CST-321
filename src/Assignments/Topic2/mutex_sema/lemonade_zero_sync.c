#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define KIDS 5
#define USES 3

int refrigeratorOpen = 0; // 1 if the refrigerator is being used, otherwise 0
int availableCups = 2;    // Start with 2 available cups

void* serveLemonade(void* arg) {
    int kidId = *(int*)arg;
    for (int i = 0; i < USES; i++) {
        if (!refrigeratorOpen) {
            refrigeratorOpen = 1; // Refrigerator is now being used
            printf("Kid %d is using the refrigerator.\n", kidId);
            sleep(1); // Simulate time to use the refrigerator
            refrigeratorOpen = 0; // Done using the refrigerator
            printf("Kid %d is done with the refrigerator.\n", kidId);
        } else {
            printf("Kid %d couldn't use the refrigerator because it's already in use.\n", kidId);
        }

        if (availableCups > 0) {
            availableCups -= 1; // Decrement the number of available cups
            printf("Kid %d is serving lemonade. Cups left: %d\n", kidId, availableCups);
            sleep(1); // Simulate serving time
            availableCups += 1; // Increment the number of available cups
        } else {
            printf("Kid %d couldn't serve lemonade because there are no cups available.\n", kidId);
        }
    }
    free(arg);
    return NULL;
}

int main() {
    pthread_t kids[KIDS];

    for(int i = 0; i < KIDS; i++) {
        int* kidId = malloc(sizeof(int));
        *kidId = i;
        pthread_create(&kids[i], NULL, serveLemonade, kidId);
    }

    for(int i = 0; i < KIDS; i++) {
        pthread_join(kids[i], NULL);
    }

    printf("All kids are done serving lemonade.\n");
    return 0;
}
