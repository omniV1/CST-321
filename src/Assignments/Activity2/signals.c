// Owen Lindsey
// CST-321
// This work was done on my own along with the help of the
// padlet topic guide: Reha, M. (2024). Topic 2 Powerpoint guide: https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582473076
// assignment guide: Reha, M. (2024). Activity 2 Assignment guide: https://mygcuedu6961.sharepoint.com/:w:/r/sites/CSETGuides/_layouts/15/Doc.aspx?sourcedoc=%7BFD1AEEC0-81CF-40E1-A169-85CE23F53355%7D&file=CST-321-RS-T2-Activity2Guide%20.docx&action=default&mobileredirect=true
// online resources: Kadam, P. (2024). Signals in c language. geeksforgeeks : https://www.geeksforgeeks.org/signals-c-language/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

// Define the signal as per POSIX standard
#define WAKEUP SIGUSR1

// Function to handle WAKEUP signal for the consumer
void wakeup_handler(int signum) {
    // Signal handler code
}

// Function for the consumer process
void consumer() {
    // Register signal handler
    signal(WAKEUP, wakeup_handler);

    // Pause the consumer process to wait for the signal
    pause();

    // Run consumer operations
    for (int i = 0; i < 20; i++) {
        printf("Consumer working on iteration %d\n", i + 1);
        sleep(1);
    }

    // Exit with a specific return code
    exit(1);
}

// Function for the producer process
void producer(pid_t consumer_pid) {
    // Run producer operations
    for (int i = 0; i < 30; i++) {
        printf("Producer working on iteration %d\n", i + 1);
        sleep(1);

        // Send WAKEUP signal after 5 iterations
        if (i == 5) {
            kill(consumer_pid, WAKEUP);
        }
    }

    // Exit with a specific return code
    exit(1);
}

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        // Fork failed
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Consumer process
        consumer();
    } else {
        // Producer process
        producer(pid);
    }

    return 0;
}
