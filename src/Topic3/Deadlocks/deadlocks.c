// Owen Lindsey
// CST-321
// This work was done with the help of
//Reha, M. (2024). Topic 3 Lecture : https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582472940
//Tanenbaum, A. (2023). Deadlocks. In Modern Operating Systems (Fifth).: https://bibliu.com/app/#/view/books/9780137618798/epub/OPS/xhtml/fileP700101801700000000000000000254A.html#page_456
//Tillett, D. (n.d.). Danieltillett/simple-windows-POSIX-semaphore: A simple window posix semaphore library. GitHub. https://github.com/DanielTillett/Simple-Windows-Posix-Semaphore
//Kadam, P. (2024). Signals in c language. geeksforgeeks : https://www.geeksforgeeks.org/signals-c-language/
//Kerrisk, M. (n.d.). sem_wait, sem_timedwait, sem_trywait - lock a semaphore. SEM_WAIT(3) - linux manual page. https://man7.org/linux/man-pages/man3/sem_wait.3.html

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
                fprintf(stderr, "Airplane %d is being diverted due to timeout.\n", id);
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
            exit(0); // Child exits after handling landing or diversion
        }
    }

    // Parent process waits for all children to finish
    while (wait(NULL) > 0);

    // Cleanup
    sem_close(runway);
    sem_unlink("/runway_semaphore");
    fprintf(stdout, "All airplanes have been handled.\n");
    return 0;
}
