// Owen Lindsey
// CST-321
// This code was written with the help of:
//Reha, M. , (2024). Activity 3 Assignment guide: https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582473094
//Reha, M. (2024). Topic 3 Lecture : https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582472940
//Kadam, P. (2024). Signals in c language. geeksforgeeks : https://www.geeksforgeeks.org/signals-c-language/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX 30
#define WAKEUP SIGUSR1

struct CIRCULAR_BUFFER {
    int start;
    int end;
    char buffer[MAX];
};

struct CIRCULAR_BUFFER *buffer = NULL;
pid_t otherPid;

void signalHandler(int signum) {
    // Empty handler, just to interrupt sleep
}

void putValue(char value) {
    if (((buffer->end + 1) % MAX) == buffer->start) {
        printf("Buffer is full, producer must wait...\n");
    }
    buffer->buffer[buffer->end] = value;
    buffer->end = (buffer->end + 1) % MAX;
    printf("Put '%c' into buffer.\n", value);
    if (value == '\0') {
        kill(otherPid, WAKEUP); // Notify consumer about termination signal
    } else {
        kill(otherPid, WAKEUP); // Notify consumer a new value is available
    }
}

char getValue() {
    if (buffer->start == buffer->end) {
        printf("Buffer is empty, consumer must wait...\n");
    }
    char value = buffer->buffer[buffer->start];
    buffer->start = (buffer->start + 1) % MAX;
    printf("Got '%c' from buffer.", value);
    return value;
}



void producer() {
    const char *message = "Owen Lindsey\0\n"; // Include null terminator in message
    printf("Producer starting...\n");
    for (int i = 0; message[i] != '\0'; i++) {
        while (((buffer->end + 1) % MAX) == buffer->start) {
            printf("Producer waiting, buffer full...\n");
            sleep(1); // Wait for consumer to consume some data
        }
        printf("Producer sending: '%c'\n", message[i]);
        putValue(message[i]);
    }
    printf("Producer finished sending.\n");
}

void consumer() {
    printf("Consumer starting...\n");
    while (1) {
        char value = getValue();
        if (value == '\0') {
            printf("\nConsumer received termination signal. Exiting.\n");
            exit(0); // Exit the process gracefully
        } else {
            printf("Consumer received: '%c'\n", value);
            fflush(stdout); // Ensure output is printed immediately
        }
    }
}


int main() {
    buffer = mmap(NULL, sizeof(struct CIRCULAR_BUFFER), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (buffer == MAP_FAILED) {
        perror("mmap failed");
        exit(EXIT_FAILURE);
    }
    memset(buffer, 0, sizeof(struct CIRCULAR_BUFFER));

    // Setup signal handling
    struct sigaction sa;
    sa.sa_handler = &signalHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(WAKEUP, &sa, NULL);

    otherPid = fork();
    if (otherPid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (otherPid == 0) { // Child process
        consumer();
    } else { // Parent process
        producer();
        wait(NULL); // Wait for the child process to finish

        if (munmap(buffer, sizeof(struct CIRCULAR_BUFFER)) == -1) {
            perror("munmap failed");
            exit(EXIT_FAILURE);
        }
        printf("Parent process exiting.\n");
    }

    return 0;
}
