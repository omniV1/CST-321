// Owen Lindsey
//CST-321
// This was done with the help of
//Reha, M. , (2024). Activity 3 Assignment guide: https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582473094
//Reha, M. (2024). Topic 3 Lecture : https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582472940
//Kadam, P. (2024). Signals in c language. geeksforgeeks : https://www.geeksforgeeks.org/signals-c-language/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// Global Variables
sem_t semaphore;
pid_t otherpid;

void signalHandler1(int signum) {
    printf("Caught signal: %d\n", signum);
    printf("Exiting child process.\n");
    sem_post(&semaphore);
    _exit(0);
}

void signalHandler2(int signum) {
    printf("I am alive\n");
}

void childProcesses() {
    // Setup some Signal handlers
    signal(SIGUSR1, signalHandler1);
    signal(SIGUSR2, signalHandler2);

    // Child process simulates a long-running or stuck process waiting on a Semaphore
    printf("Child process is waiting on semaphore.\n");
    sem_wait(&semaphore);

    printf("Child process has acquired semaphore, entering long operation...\n");
    for (int x = 0; x < 60; ++x) {
        sleep(1);
    }

    printf("Child process completing long operation and releasing semaphore.\n");
    sem_post(&semaphore);

    _exit(0); // Use _exit in child processes to avoid flushing stdio buffers of the parent
}

void* checkHungChild(void *arg) {
    int *status = (int*)arg;
    printf("Parent thread checking for hung child process...\n");
    sleep(10);

    if (sem_trywait(&semaphore) != 0) {
        printf("Child process appears to be hung.\n");
        *status = 1;
    } else {
        printf("Child process is not hung.\n");
        sem_post(&semaphore); // Release semaphore if acquired
        *status = 0;
    }
    pthread_exit(NULL);
}

int main() {
    int status = 0;

    // Initialize semaphore
    sem_init(&semaphore, 0, 1);

    otherpid = fork();
    if (otherpid == 0) {
        childProcesses();
    } else {
        pthread_t tid;
        pthread_create(&tid, NULL, checkHungChild, &status);
        pthread_join(tid, NULL);

        if (status == 1) {
            kill(otherpid, SIGKILL);
            waitpid(otherpid, NULL, 0); // Ensure child process termination
            printf("Child process was terminated.\n");
        }

        sem_destroy(&semaphore);
        printf("Parent process exiting.\n");
    }

    return 0;
}
