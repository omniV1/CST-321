

###### Owen Lindsey
###### CST -321
###### 2/18/2024
###### Resources at bottom
###### Loom video explanation: https://www.loom.com/share/090bce81c15c4215bac08d98a95d2c3e
# Deadlock Avoidance

## Scenario description

In this scenario, we simulate an airport runway management system where multiple airplanes need to land on a single runway. Each airplane is represented as a separate process, and the runway is a shared resource that can only be accessed by one airplane at a time. The goal is to ensure that airplanes land safely without colliding on the runway and to prevent deadlock situations where airplanes are unable to land due to resource contention.

`Runway and Airplane Representation:` The runway is represented as a semaphore, specifically initialized as a binary semaphore with an initial value of 1. Each airplane is simulated as a separate child process created using the fork() system call.

`Landing Process:` When an airplane process is spawned, it attempts to acquire the semaphore lock for the runway using sem_trywait(). If the semaphore lock is successfully acquired (indicating that the runway is available), the airplane proceeds to land. Otherwise, it is diverted due to a timeout to prevent potential deadlocks.

`Timeout Handling:` If an airplane process is unable to acquire the semaphore lock within a specified timeout period, it is diverted. This timeout mechanism prevents potential deadlock situations where airplanes may indefinitely wait for access to the runway, ensuring continuous operation of the airport.

`Synchronization:` The semaphore ensures that only one airplane can land on the runway at a time. This synchronization mechanism prevents collisions and ensures safe landing operations by providing mutually exclusive access to the shared resource (runway).

`Cleanup:` After all airplanes have landed or been diverted, the parent process (main program) waits for all child processes to finish execution using wait(). Once all airplanes have completed their landing operations, the semaphore associated with the runway is closed and removed from the system, ensuring proper cleanup of resources.

### flowchart
![Flowchart](https://github.com/omniV1/CST-321/blob/main/src/Assignments/Topic3/Deadlocks/screenshots/flowchart.png)

### Program flowchart Explanation

| Event                             | Explanation                                                                                                                                                                       |
|-----------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Airplane Attempts Landing        | Each airplane process attempts to land on a runway by acquiring a semaphore lock.                                                                                         |
| Successful Landing               | If the airplane successfully acquires the runway lock, it lands and clears the runway.                                                                                             |
| Deadlock Occurrence              | In some cases, multiple airplanes may attempt to acquire the same runway lock simultaneously, leading to a deadlock situation where none of the airplanes can proceed.          |
| Diversion Due to Timeout         | If the airplane is unable to acquire the runway lock within a predetermined timeout period, it is diverted to prevent deadlock and ensure that other airplanes can proceed.      |
| Runway Clearance                 | After an airplane successfully lands and clears the runway, the semaphore lock is released, allowing other airplanes to proceed with landing attempts.              |
| Program Completion               | Once all airplanes have either landed successfully or been diverted due to timeouts, the program completes execution, and the runway is clear for future use.               |

## Code:

```c
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



```



### Expected output

```Plain text
Airplane 1 is landing.
Airplane 1 has landed successfully.
Airplane 4 is landing.
Airplane 4 has landed successfully.
Airplane 3 is landing.
Airplane 2 is being diverted due to timeout.
Airplane 3 has landed successfully.
Airplane 5 is landing.
Airplane 5 has landed successfully.
All airplanes have been handled.

```

### Function and System Call Analysis

| Function/System Call       | Purpose                                                                                                                                                                        |
|----------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `sem_open()`               | Initializes the semaphore to control access to the runway.                                                                                                                      |
| `sem_wait()`               | Attempts to acquire the semaphore lock for the runway.                                                                                                                         |
| `sem_post()`               | Releases the semaphore lock for the runway after an airplane has landed and cleared the runway.                                                                                |
| `sem_trywait()`            | Non-blocking attempt to acquire the semaphore lock. Used to check if the runway is available without waiting indefinitely, preventing potential deadlock situations.     |
| `sleep()`                  | Simulates the time taken for an airplane to land and clear the runway, as well as the timeout period for diversion in case of deadlock avoidance.                               |
| `fork()`                   | Creates child processes (airplane processes) to simulate multiple airplanes attempting to land on the runway concurrently.                                                  |
| `exit()`                   | Terminates the child processes after they have completed landing attempts or been diverted due to timeouts.                                                                   |
| `wait(NULL)`               | Parent process waits for all child processes to finish execution before proceeding with cleanup and program completion.                                                       |
| `fprintf()`                | Outputs log messages to the console, providing information about the status of airplanes attempting to land, runway availability, and any diversions or successful landings. |

# Analysis of Timer Use for Deadlock Resolution

- The use of a timer in the semaphore-based program to terminate processes after a timeout can effectively prevent deadlocks by ensuring no process holds onto a resource indefinitely. However, this method has limitations, particularly when scaling to a larger number of processes or threads:

- Scalability Issues: As the number of concurrent processes increases, managing individual timers for each becomes more complex and resource-intensive.
Risk of Starvation: Processes might repeatedly be terminated before accessing the needed resource, leading to potential starvation, especially for lower-priority tasks.
Optimal Timeout Determination: Setting an appropriate timeout that balances between preventing deadlocks and not prematurely terminating processes is challenging and might not be one-size-fits-all.
Alternative Approach

- Instead of relying solely on timeouts, implementing a priority-based scheduling mechanism could offer a more nuanced solution. This system would allow processes with higher priority to access the resource first, while still using timeouts to prevent deadlocks. However, these timeouts would be dynamically adjusted based on the process's priority and the current system load, offering a more flexible and fair approach to resource allocation.

- Advantages: Prioritizing critical processes reduces the risk of important operations being terminated. Dynamically adjusting timeouts based on system conditions and process priority ensures a more responsive and efficient system, tailoring behavior to current needs.



# Resources

Reha, M. , (2024). Activity 3 Assignment guide: https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582473094

Reha, M. (2024). Topic 3 Lecture : https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582472940

Tanenbaum, A. (2023). Deadlocks. In Modern Operating Systems (Fifth).: https://bibliu.com/app/#/view/books/9780137618798/epub/OPS/xhtml/fileP700101801700000000000000000254A.html#page_456

Tillett, D. (n.d.). Danieltillett/simple-windows-POSIX-semaphore: A simple window posix semaphore library. GitHub. https://github.com/DanielTillett/Simple-Windows-Posix-Semaphore

Kadam, P. (2024). Signals in c language. geeksforgeeks : https://www.geeksforgeeks.org/signals-c-language/

Kerrisk, M. (n.d.). sem_wait, sem_timedwait, sem_trywait - lock a semaphore. SEM_WAIT(3) - linux manual page. https://man7.org/linux/man-pages/man3/sem_wait.3.html
