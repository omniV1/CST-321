// Owen Lindsey
// CST-321
// This was done with the help of
//

#include <stdio.h>
#include <stdlib.h>
#include <spawn.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **environ;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <application>\n", argv[0]);
        return EXIT_FAILURE;
    }

    pid_t pid;
    int status;
    posix_spawnattr_t attr;

    posix_spawnattr_init(&attr);

    // Spawn a new process
    if (posix_spawn(&pid, argv[1], NULL, &attr, &argv[1], environ) != 0) {
        perror("posix_spawn failed");
        return EXIT_FAILURE;
    }
    printf("Spawned process ID: %d\n", pid);

    // Wait for the process to end
    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid failed");
        return EXIT_FAILURE;
    }

    printf("Process %d finished\n", pid);

    return EXIT_SUCCESS;
}
