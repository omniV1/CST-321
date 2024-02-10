// Owen Lindsey
// CST-321
// This work was done on my own along with the help of the
// padlet topic guide: Reha, M. (2024). Topic 2 Powerpoint guide: https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582473076
// assignment guide: Reha, M. (2024). Activity 2 Assignment guide: https://mygcuedu6961.sharepoint.com/:w:/r/sites/CSETGuides/_layouts/15/Doc.aspx?sourcedoc=%7BFD1AEEC0-81CF-40E1-A169-85CE23F53355%7D&file=CST-321-RS-T2-Activity2Guide%20.docx&action=default&mobileredirect=true
// online resources: https://www.youtube.com/watch?v=9seb8hddeK4 : youtube guide provided by instructor


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
