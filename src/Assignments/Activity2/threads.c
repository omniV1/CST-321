// Owen Lindsey
// CST-321
// This work was done on my own along with the help of the
// padlet topic guide: Reha, M. (2024). Topic 2 Powerpoint guide: https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582473076
// assignment guide: Reha, M. (2024). Activity 2 Assignment guide: https://mygcuedu6961.sharepoint.com/:w:/r/sites/CSETGuides/_layouts/15/Doc.aspx?sourcedoc=%7BFD1AEEC0-81CF-40E1-A169-85CE23F53355%7D&file=CST-321-RS-T2-Activity2Guide%20.docx&action=default&mobileredirect=true
// online resources: Kadam, P. (2024). Multithreading in c . geeksforgeeks: https://www.geeksforgeeks.org/multithreading-in-c/


#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

volatile int turn = 0; // Shared variable to control the turn
const int NUM_SIMULATIONS = 5; // Number of flight simulations

// Function for the 'Pilot' thread
void *pilot(void *arg) {
    for (int i = 0; i < NUM_SIMULATIONS; ++i) {
        while (turn != 0) {
            // Wait for the pilot's turn
        }
        printf("Pilot: Running flight simulation %d\n", i + 1);
        sleep(1); // Simulate the time taken for the flight simulation
        printf("Pilot: Simulation %d complete, passing controls to Co-Pilot.\n", i + 1);
        turn = 1; // Pass control to the co-pilot
    }
    return NULL;
}

// Function for the 'Co-Pilot' thread
void *coPilot(void *arg) {
    for (int i = 0; i < NUM_SIMULATIONS; ++i) {
        while (turn != 1) {
            // Wait for the co-pilot's turn
        }
        printf("Co-Pilot: Running flight simulation %d\n", i + 1);
        sleep(1); // Simulate the time taken for the flight simulation
        printf("Co-Pilot: Simulation %d complete, passing controls back to Pilot.\n", i + 1);
        turn = 0; // Pass control back to the pilot
    }
    return NULL;
}

int main() {
    pthread_t pilotThread, coPilotThread;

    // Create threads
    pthread_create(&pilotThread, NULL, pilot, NULL);
    pthread_create(&coPilotThread, NULL, coPilot, NULL);

    // Wait for threads to finish
    pthread_join(pilotThread, NULL);
    pthread_join(coPilotThread, NULL);

    printf("Main: Flight simulation exercises completed successfully.\n");

    return 0;
}
