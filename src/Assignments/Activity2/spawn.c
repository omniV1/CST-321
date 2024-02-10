// Owen Lindsey
// CST-321
// This work was done on my own along with the help of the
// padlet topic guide: Reha, M. (2024). Topic 2 Powerpoint guide: https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582473076
// assignment guide: Reha, M. (2024). Activity 2 Assignment guide: https://mygcuedu6961.sharepoint.com/:w:/r/sites/CSETGuides/_layouts/15/Doc.aspx?sourcedoc=%7BFD1AEEC0-81CF-40E1-A169-85CE23F53355%7D&file=CST-321-RS-T2-Activity2Guide%20.docx&action=default&mobileredirect=true


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
