#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define NUM_AIRPLANES 5
#define LANDING_DURATION 2

void attempt_landing(int id) {
    printf("Airplane %d is trying to land...\n", id);
    sleep(LANDING_DURATION); // Simulates the landing process
    printf("Airplane %d landed without coordinating with others.\n", id);
}

int main() {
    printf("Airport runway simulation started.\n");

    for (int i = 0; i < NUM_AIRPLANES; i++) {
        pid_t pid = fork();
        if (pid == 0) { // Child process
            attempt_landing(i + 1);
            exit(0); // Exit after attempting to land
        }
    }

    // Wait for all child processes to finish
    while (wait(NULL) > 0);

    printf("All airplanes have attempted to land.\n");

    return 0;
}
