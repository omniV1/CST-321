// Owen Lindsey
// CST-321
// This work was done on my own along with the help of the
// padlet topic guide: Reha, M. (2024). Topic 2 Powerpoint guide: https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582473076
// assignment guide: Reha, M. (2024). Activity 2 Assignment guide: https://mygcuedu6961.sharepoint.com/:w:/r/sites/CSETGuides/_layouts/15/Doc.aspx?sourcedoc=%7BFD1AEEC0-81CF-40E1-A169-85CE23F53355%7D&file=CST-321-RS-T2-Activity2Guide%20.docx&action=default&mobileredirect=true
// online resources: Frasier, B. (2015). Mutex Synchronization in Linux with Pthreads. Youtube: https://www.youtube.com/watch?v=GXXE42bkqQk
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define KIDS 5
#define USES 3
#define TOTAL_CUPS 2

pthread_mutex_t fridgeMutex; // Mutex to control fridge access
sem_t cupsSemaphore; // Semaphore to control cup availability

// Prints the current number of available cups
void printCupCount(const char* action, int kidId) {
    int cups;
    sem_getvalue(&cupsSemaphore, &cups); // Get the current value of the semaphore
    printf("Kid %d %s lemonade. Cups available: %d\n", kidId, action, cups);
}

// Function for each kid to serve lemonade
void* serveLemonade(void* arg) {
    int kidId = *(int*)arg;
    for (int i = 0; i < USES; i++) {
        pthread_mutex_lock(&fridgeMutex); // Acquire the mutex lock to use the fridge
        printf("Kid %d is using the refrigerator.\n", kidId);
        sleep(1); // Simulate time to use the refrigerator
        printf("Kid %d is done with the refrigerator.\n", kidId);
        pthread_mutex_unlock(&fridgeMutex); // Release the mutex lock

        sem_wait(&cupsSemaphore); // Acquire a cup to serve lemonade
        printCupCount("starts serving", kidId); // Print number of cups before serving
        sleep(1); // Simulate time to serve lemonade
        printCupCount("has served", kidId); // Print number of cups after serving
        sem_post(&cupsSemaphore); // Release the cup back to the pool
    }
    free(arg); // Free the allocated memory
    return NULL;
}

int main() {
    pthread_mutex_init(&fridgeMutex, NULL); // Initialize the mutex
    sem_init(&cupsSemaphore, 0, TOTAL_CUPS); // Initialize the semaphore with total cups

    pthread_t kids[KIDS]; // Thread identifiers for kids

    // Create and start threads for each kid
    for(int i = 0; i < KIDS; i++) {
        int* kidId = malloc(sizeof(int)); // Dynamically allocate memory for the kid ID
        *kidId = i; // Set kid ID
        pthread_create(&kids[i], NULL, serveLemonade, kidId); // Start the thread
    }

    // Wait for all threads to complete
    for(int i = 0; i < KIDS; i++) {
        pthread_join(kids[i], NULL); // Wait for thread to finish
    }

    // Clean up mutex and semaphore
    pthread_mutex_destroy(&fridgeMutex); // Destroy mutex
    sem_destroy(&cupsSemaphore); // Destroy semaphore

    printf("All kids are done serving lemonade.\n"); // All kids are done
    return 0;
}
