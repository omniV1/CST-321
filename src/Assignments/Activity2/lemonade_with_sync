#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_CUPS 5

// Global refrigerator mutex
pthread_mutex_t fridgeMutex = PTHREAD_MUTEX_INITIALIZER;

// Semaphore for limiting serving cups
sem_t cupsSemaphore;

// Use the refrigerator
void useRefrigerator(int kidId) {
    pthread_mutex_lock(&fridgeMutex);
    printf("Kid %d is using the refrigerator.\n", kidId);
    sleep(1); // Simulate time taken to use the refrigerator
    printf("Kid %d is done with the refrigerator.\n", kidId);
    pthread_mutex_unlock(&fridgeMutex);
}

// Serve lemonade
void* serveLemonade(void* arg) {
    int kidId = *(int*)arg;
    sem_wait(&cupsSemaphore); // Wait on semaphore
    printf("Kid %d is serving lemonade.\n", kidId);
    useRefrigerator(kidId); // Need to use the refrigerator to get more lemonade
    sleep(1); // Simulate serving time
    printf("Kid %d has served lemonade.\n", kidId);
    sem_post(&cupsSemaphore); // Signal semaphore
    free(arg); // Clean up dynamically allocated memory
    return NULL;
}

int main() {
    pthread_t kids[MAX_CUPS];
    sem_init(&cupsSemaphore, 0, MAX_CUPS);

    for(int i = 0; i < MAX_CUPS; i++) {
        int* kidId = malloc(sizeof(int));
        *kidId = i;
        pthread_create(&kids[i], NULL, serveLemonade, kidId);
    }

    for(int i = 0; i < MAX_CUPS; i++) {
        pthread_join(kids[i], NULL);
    }

    sem_destroy(&cupsSemaphore);
    pthread_mutex_destroy(&fridgeMutex);
    return 0;
}
