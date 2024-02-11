##include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define KIDS 5
#define USES 3

int refrigeratorOpen = 0;
int availableCups = 2;

// Function to increment cups safely
void incrementCups() {
    availableCups = availableCups + 1;
}

// Function to decrement cups safely
void decrementCups() {
    if (availableCups > 0) {
        availableCups = availableCups - 1;
    }
}

void* serveLemonade(void* arg) {
    int kidId = *(int*)arg;
    for (int i = 0; i < USES; i++) {
        if (!refrigeratorOpen) {
            refrigeratorOpen = 1;
            printf("Kid %d is using the refrigerator.\n", kidId);
            sleep(1);
            refrigeratorOpen = 0;
            printf("Kid %d is done with the refrigerator.\n", kidId);
        } else {
            printf("Kid %d couldn't use the refrigerator because it's already in use.\n", kidId);
        }

        // Serve lemonade if cups are available
        if (availableCups > 0) {
            decrementCups(); // Decrement safely
            printf("Kid %d is serving lemonade. Cups left: %d\n", kidId, availableCups);
            sleep(1);
            incrementCups(); // Increment safely
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

