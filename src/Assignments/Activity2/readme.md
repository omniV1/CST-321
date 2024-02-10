##### Owen Lindsey
##### CST-321
##### This work was done on my own along with the help of the
##### padlet topic guide: Reha, M. (2024). [Topic 2 Powerpoint guide](https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/158247307)
##### assignment guide: Reha, M. (2024). [Activity 2 Assignment guide](https://mygcuedu6961.sharepoint.com/:w:/r/sites/CSETGuides/_layouts/15/Doc.aspx?sourcedoc=%7BFD1AEEC0-81CF-40E1-A169-85CE23F53355%7D&file=CST-321-RS-T2-Activity2Guide%20.docx&action=default&mobileredirect=true)

##### online resources: Kadam, P. (2024). Multithreading in c . [geeksforgeeks](https://www.geeksforgeeks.org/multithreading-in-c/)
##### online resources: Kadam, P. (2024). Signals in c language. [geeksforgeeks](https://www.geeksforgeeks.org/signals-c-language/)
##### online resources: https://www.youtube.com/watch?v=9seb8hddeK4 : [youtube](guide provided by instructor)
##### online resources: Barnes, R. (2020). Mutex vs Semaphore. [tutorialspoint](https://www.tutorialspoint.com/mutex-vs-semaphore)
##### online resources: Frasier, B. (2015). Mutex Synchronization in Linux with Pthreads.  [Youtube:](https://www.youtube.com/watch?v=GXXE42bkqQk)


# 1. Theory of Operation for `fork()` and Signal Handling in Linux

### Overview
The C program employs `fork()` to instantiate a producer-consumer scenario where the producer is the parent process and the consumer is the child. Communication and synchronization between them are managed via UNIX signals.

### Process Dynamics

| Producer (Parent Process) | Consumer (Child Process) |
| ------------------------- | ------------------------ |
| Initiates the `SIGUSR1` signal to the consumer after 5 iterations within a 30-iteration loop, each iteration representing a production cycle. | Enters a passive wait state until the `SIGUSR1` signal is received, then performs 20 iterations of a task, symbolizing the consumption of data. |

### Signal Mechanics

- **Signal Registration**: Custom signal handlers are assigned to `SIGUSR1` and `SIGUSR2`, setting up a controlled communication protocol between the producer and consumer.
- **Signal Execution**: The `kill()` function is utilized to send signals, orchestrating the execution flow of the consumer process based on the producer's state.

# 2. Theory of Operation for Creating Threads in Linux

### Overview
This program introduces threads in a Linux environment, utilizing the `pthread_create()` function to simultaneously run two threads performing separate tasks.

### Thread Behavior

- **Thread 1**: Acts as a 'pilot', iterating through a sequence of checkpoints with a 1-second pause, emulating the process of navigating a flight path.
- **Thread 2**: Represents a 'maintainer', conducting a series of maintenance checks with a 2-second interval, mimicking the systematic verification of systems.

### Thread Synchronization

- **Execution**: Both threads start their sequences in parallel, demonstrating the non-blocking nature of thread execution.
- **Completion**: Utilizing `pthread_join()`, the program ensures that the main process awaits the completion of both threads, maintaining execution integrity.

# 3. Theory of Operation for Mutexes in Bank Program

### Overview
In the context of a simulated banking application, mutexes are utilized to manage concurrent access to a shared bank balance, ensuring accurate updates despite simultaneous deposit attempts by multiple threads.

### Critical Section Management

| Action      | Description |
| ----------- | ----------- |
| Mutex Lock  | Before entering the critical section where the bank balance is updated, a mutex lock is acquired to prevent other threads from entering this section. |
| Update Sequence | The balance is safely incremented within the locked section, thus avoiding any race conditions or data inconsistencies. |
| Mutex Unlock | Upon updating, the mutex is released, permitting other threads to enter the critical section and perform their updates. |

# 4. Theory of Operation for Semaphores in Bank Program

### Overview
Semaphores serve a similar purpose to mutexes but are often used as signaling mechanisms. In this banking application, semaphores are used to signal when a thread can safely enter the critical section and update the shared balance.

### Semaphore Workflow

- **Semaphore Initialization**: A semaphore is initialized with a value that determines the number of threads allowed to access the critical section simultaneously.
- **Deposit Loop**: Each thread waits on the semaphore before accessing the critical section and posts to the semaphore after completing the update, signaling that another thread can proceed.

By controlling access to the critical section using semaphores, the program ensures that the final bank balance is accurately calculated, reflecting all the intended deposit transactions.


# Research Question 1: Mutual Exclusion with `turn` Variable

The C program implements a mutual exclusion protocol between two threads, `pilot` and `coPilot`, utilizing a `turn` variable. Each thread executes a series of flight simulations, sequentially accessing a critical section based on the value of the `turn` variable.

### Pilot Thread Function

The `pilot` thread executes its flight simulation loop when `turn` is set to 0. Upon completion of its critical section, it signals the `coPilot` by setting `turn` to 1, indicating it's the `coPilot`'s turn to execute.

```c
while (turn != 0) {
    // Wait for the pilot's turn
}
// Critical section
turn = 1;
```
### Co-Pilot Thread Function
- In contrast, the Co-Pilot awaits its turn when turn equals 1. After finishing its critical section, it hands control back to the pilot by resetting turn to 0.

```c
while (turn != 1) {
    // Wait for the co-pilot's turn
}
// Critical section
turn = 0;

```
- The main function initiates both pilot and coPilot threads and waits for them to complete their tasks. The orderly execution of flight simulations showcases successful mutual exclusion.

```c
pthread_create(&pilotThread, NULL, pilot, NULL);
pthread_create(&coPilotThread, NULL, coPilot, NULL);
// Await completion of both threads
pthread_join(pilotThread, NULL);
pthread_join(coPilotThread, NULL);

```
# Research Question 2: Number of Child Processes

The C program demonstrates process creation using the `fork()` system call. It's designed to explore the number of child processes spawned when `fork()` is called multiple times within the same program.

###  theory of operation

The main function contains a sequence of `fork()` calls, each creating a child process. The program outputs the process ID (PID) of each process, helping to determine the number of processes created.

- Upon execution, the main process forks twice, creating two child processes at each fork() call.

- Each child process also executes the printf() statement, printing its own PID.

- The output shows that each process continues to execute independently after the fork(), resulting in three child processes in addition to the original parent process .

```c
#include <stdio.h>
#include <unistd.h> // For fork()
#include <stdlib.h> // For exit()

void main() {
    fork();
    printf("PID: %d\n", getpid());

    fork();
    printf("PID: %d\n", getpid());

    exit(0);
}
```

### visual representation 

    P0
   /  \
 P1    P2
 |
 P3

