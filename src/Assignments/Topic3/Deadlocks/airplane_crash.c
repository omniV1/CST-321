#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>
#include <time.h>

#define LANDING_TIMEOUT 5
#define NUM_AIRPLANES 5

sem_t *runway;

void handle_airplane(int id) {
    time_t start, end;
    start = time(NULL);
    int landed = 0;

    while (!landed) {
        if (sem_trywait(runway) == 0) { // Attempt to land
            fprintf(stdout, "Airplane %d is landing.\n", id);
            sleep(2); // Simulate landing duration
            sem_post(runway);
            fprintf(stdout, "Airplane %d has landed successfully.\n", id);
            landed = 1;
        } else {
            end = time(NULL);
            if (difftime(end, start) > LANDING_TIMEOUT) { // Timeout check
                fprintf(stderr, "Airplane %d could not land due to timeout.\n", id);
                break;
            }
            sleep(1); // Retry after a short wait
        }
    }
}

int main() {
    runway = sem_open("/runway_semaphore", O_CREAT, S_IRUSR | S_IWUSR, 1);

    for (int i = 0; i < NUM_AIRPLANES; i++) {
        pid_t pid = fork();
        if (pid == 0) { // Child process
            handle_airplane(i + 1);
            exit(0); // Child exits after handling landing or timeout
        }
    }

    // Parent process waits for all children to finish
    while (wait(NULL) > 0);

    // Cleanup
    sem_close(runway);
    sem_unlink("/runway_semaphore");
    fprintf(stdout, "All airplanes have attempted to land.\n");
    return 0;
}
