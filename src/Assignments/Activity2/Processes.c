// Owen Lindsey
// CST-321
// This work was done with the help of
//https://www.youtube.com/watch?v=9seb8hddeK4 : youtube guide provided by instructor
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        // If fork() returns -1, an error occurred
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        for (int i = 0; i < 10; i++) {
            printf("Child process message %d\n", i+1);
            printf("Child process going to sleep...\n");
            sleep(1); // Sleep for 1 second
            printf("Child process wakes up!\n");
        }
        exit(0); // Exit with return code 0
    } else {
        // Parent process
        for (int i = 0; i < 10; i++) {
            printf("Parent process message %d\n", i+1);
            printf("Parent process going to sleep...\n");
            sleep(2); // Sleep for 2 seconds
            printf("Parent process wakes up!\n");
        }
        exit(0); // Exit with return code 0
    }
}
