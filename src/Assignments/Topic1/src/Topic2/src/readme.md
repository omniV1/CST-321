##### Owen Lindsey
##### CST-321
##### Resources at bottom of the page 
---
# 1.2 Process Dynamics

| Producer (Parent Process) | Consumer (Child Process) |
| ------------------------- | ------------------------ |
| Initiates the `SIGUSR1` signal to the consumer after 5 iterations within a 30-iteration loop, each iteration representing a production cycle. | Enters a passive wait state until the `SIGUSR1` signal is received, then performs 20 iterations of a task, symbolizing the consumption of data. |

## Program Execution

The `main()` function begins by calling `fork()`. Depending on the return value, the program distinguishes between parent and child process operations.

## Key Functions and System Calls

| Function/System Call | Description |
| ---------------------| ----------- |
| `fork()`             | Creates a new process by duplicating the calling process. |
| `perror()`           | Prints a descriptive error message to stderr. |
| `sleep()`            | Suspends process execution for a specified number of seconds. |
| `exit()`             | Terminates the calling process and returns an exit status. |

## Code Explanation

```c
int main() {
    pid_t pid = fork();  // Attempt to create a child process

    if (pid == -1) {
        // If fork() returns -1, an error occurred
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process executes this block
        for (int i = 0; i < 10; i++) {
            printf("Child process message %d\n", i+1);
            sleep(1); // Child sleeps for 1 second
        }
        exit(0); // Child process exits with status 0
    } else {
        // Parent process executes this block
        for (int i = 0; i < 10; i++) {
            printf("Parent process message %d\n", i+1);
            sleep(2); // Parent sleeps for 2 seconds
        }
        exit(0); // Parent process exits with status 0
    }
```
![processes binary](
https://github.com/omniV1/CST-321/blob/main/src/Assignments/Topic2/research_screenshots/processes.png)

---
# 1.3 Processes in Linux: Using `posix_spawn()` and `waitpid()`

### Overview
1. The program starts by checking if a command-line argument is provided, which is the application to spawn.
2. It initializes the `posix_spawnattr_t` structure to its default values.
3. The `posix_spawn()` function is called to create a new process that runs the specified application.
4. The parent process waits for the spawned process to finish using `waitpid()`.

## Key Functions

| Function          | Description |
| ----------------- | ----------- |
| `posix_spawn()`   | Spawns a new process based on the specified application. |
| `waitpid()`       | Waits for the spawned process to change state, typically to finish execution. |


```c
// Error checking for command-line arguments
if (argc < 2) {
    fprintf(stderr, "Usage: %s <application>\n", argv[0]);
    return EXIT_FAILURE;
}

pid_t pid;
int status;
posix_spawnattr_t attr;

posix_spawnattr_init(&attr);

// Spawning a new process
if (posix_spawn(&pid, argv[1], NULL, &attr, &argv[1], environ) != 0) {
    perror("posix_spawn failed");
    return EXIT_FAILURE;
}
printf("Spawned process ID: %d\n", pid);

// Waiting for the spawned process to end
if (waitpid(pid, &status, 0) == -1) {
    perror("waitpid failed");
    return EXIT_FAILURE;
}

printf("Process %d finished\n", pid);

```
![spawn binary](https://github.com/omniV1/CST-321/blob/main/src/Assignments/Topic2/research_screenshots/spawn.png)

---
# 2. Signals in Linux: Inter-Process Communication

| Action | Description |
| ------ | ----------- | 
| Signal Registration | Custom signal handlers are assigned to `SIGUSR1` and `SIGUSR2`, setting up a controlled communication protocol between the producer and consumer. |
| Signal Execution | The `kill()` function is utilized to send signals, orchestrating the execution flow of the consumer process based on the producer's state. |

## Program Structure

The program consists of a producer process and a consumer process. The consumer waits for a `SIGUSR1` (denoted as `WAKEUP`) signal from the producer before starting its operations. The producer, after a certain condition is met, sends the signal to the consumer to commence its processing.

## Key Functions and Signals

| Function/Signal | Description |
| --------------- | ----------- |
| `fork()`        | Creates a child process from the current process. |
| `signal()`      | Registers a signal handler for a specific signal. |
| `pause()`       | Suspends the process until a signal is received. |
| `kill()`        | Sends a signal to a specific process. |
| `WAKEUP` (SIGUSR1) | User-defined signal used for communication between processes. |

## Signal Handling

```c
// Define the signal as per POSIX standard
#define WAKEUP SIGUSR1

// Function to handle WAKEUP signal for the consumer
void wakeup_handler(int signum) {
    // Code to handle signal
}
```
  ![signals binary](https://github.com/omniV1/CST-321/blob/main/src/Assignments/Topic2/research_screenshots/signals.png)
---
# 3. Theory of Operation for Creating Threads in Linux

### Thread Behavior
| Action | Description |
| ------ | ----------- | 
| Thread 1 | Acts as a 'pilot', iterating through a sequence of checkpoints with a 1-second pause, emulating the process of navigating a flight path. | 
| Thread 2 | Represents a 'maintainer', conducting a series of maintenance checks with a 2-second interval, mimicking the systematic verification of systems. |

### Thread Synchronization
| Action | Description |
| ------ | ----------- | 
| Execution | Both threads start their sequences in parallel, demonstrating the non-blocking nature of thread execution. |
| Completion |  Utilizing `pthread_join()`, the program ensures that the main process awaits the completion of both threads, maintaining execution integrity. | 

```c
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
```

- The main function creates two threads for a pilot and co-pilot to run flight simulations, waits for them to complete, and then prints a success message.
```c
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
```
![threads binary](https://github.com/omniV1/CST-321/blob/main/src/Assignments/Topic2/research_screenshots/threads.png)
---

# 4. Theory of Operation for Mutexes in Bank Program

### Critical Section Management

| Action      | Description |
| ----------- | ----------- |
| Mutex Lock  | Before entering the critical section where the bank balance is updated, a mutex lock is acquired to prevent other threads from entering this section. |
| Update Sequence | The balance is safely incremented within the locked section, thus avoiding any race conditions or data inconsistencies. |
| Mutex Unlock | Upon updating, the mutex is released, permitting other threads to enter the critical section and perform their updates. |

- The deposit function simulates deposit operations into a bank account using a mutex for thread synchronization, ensuring each operation on the shared balance variable is executed safely in a critical section.
```c
// Thread function to deposit money into the bank
void *deposit(void *a) {
    int x, tmp;
    for (x = 0; x < MAX_DEPOSITS; x++) {
      // *** start of critical region ***
      pthread_mutex_lock(&mutex);

      // Not Thread Safe
      // Copy the balance to a local variable, add $1 to the balance and
      // save the balance in a global variable
        tmp = balance;
        tmp = tmp + depositAmount;
        balance = tmp;

        // *** End of Critical Region ***
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
```
- The main function initializes a mutex, creates two threads to perform deposit operations into a shared bank account, waits for them to complete, checks if the final balance matches the expected amount, then cleans up by destroying the mutex and exiting.

```c
int main() {
    pthread_t tid1, tid2;

    // create a mutex to be used in a critical region of our code
    pthread_mutex_init(&mutex, 0);

    // Create 2 threads (users) to deposit funds into bank
    if (pthread_create(&tid1, NULL, deposit, NULL)) {
        printf("\n ERROR creating deposit thread 1");
        exit(1);
    }
    if (pthread_create(&tid2, NULL, deposit, NULL)) {
        printf("\n ERROR creating deposit thread 2");
        exit(1);
    }

    // Wait for threads (users) to finish depositing funds into bank
    if (pthread_join(tid1, NULL)) {
        printf("\n ERROR joining deposit thread 1");
        exit(1);
    }
    if (pthread_join(tid2, NULL)) {
        printf("\n ERROR joining deposit thread 2");
        exit(1);
    }

    // Check balance
    if (balance != 2 * MAX_DEPOSITS) {
        printf("\n BAD Balance: bank balance is %d and should be %d\n", balance, 2 * MAX_DEPOSITS);
    } else {
        printf("\n GOOD Balance: bank balance is %d\n", balance);
    }


    // Thread creation cleanupand mutex clean up
    pthread_mutex_destroy(&mutex);
    pthread_exit(NULL);
}
```

![Mutex binary](https://github.com/omniV1/CST-321/blob/main/src/Assignments/Topic2/research_screenshots/goodbank-mutex.png)
---
# 5. Theory of Operation for Semaphores in Bank Program

### Semaphore Workflow
| Action | Description | 
| ------ | ---------- | 
| **Semaphore Initialization** | A semaphore is initialized with a value that determines the number of threads allowed to access the critical section simultaneously. |
| **Deposit Loop** | Each thread waits on the semaphore before accessing the critical section and posts to the semaphore after completing the update, signaling that another thread can proceed. |

   -  By controlling access to the critical section using semaphores, the program ensures that the final bank balance is accurately calculated, reflecting all the intended deposit transactions.

- The deposit function is a thread routine that simulates bank deposits by safely incrementing a shared balance using a semaphore for mutual exclusion to prevent race conditions.
```c 
// Thread function to deposit money
void *deposit(void *a) {
    int x, tmp;
    for (x = 0; x < MAX_DEPOSITS; x++) {
        sem_wait(mutex);  // Start of critical region: acquire the semaphore
        tmp = balance;    // Read balance to local variable
        tmp = tmp + depositAmount; // Add deposit amount to local variable
        balance = tmp;    // Write updated balance back to global variable
        sem_post(mutex);  // End of critical region: release the semaphore
    }
    return NULL;
}

```
-  The main function initializes a semaphore for mutual exclusion, spawns two threads for deposit operations, waits for their completion, checks if the final balance is correct, closes the semaphore, and exits the threads.
  ```c
int main() {
    // Create and initialize semaphore for mutual exclusion
    mutex = sem_open("Mutex", O_CREAT, 0644, 1);

    // Create two threads to deposit funds into the bank
    pthread_create(&tid1, NULL, deposit, NULL);
    pthread_create(&tid2, NULL, deposit, NULL);

    // Wait for both threads to complete deposit operations
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    // Check final balance against expected value
    if (balance != 2 * MAX_DEPOSITS) {
        printf("\n BAD Balance: bank balance is %d and should be %d\n", balance, 2 * MAX_DEPOSITS);
    } else {
        printf("\n GOOD Balance: bank balance is %d\n", balance);
    }

    // Cleanup: close semaphore and exit threads
    sem_close(mutex);
    pthread_exit(NULL);
}
```
![goodbank sema](https://github.com/omniV1/CST-321/blob/main/src/Assignments/Topic2/research_screenshots/goodbank-sema.png)
---
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
![research1 binary](
https://github.com/omniV1/CST-321/blob/main/src/Assignments/Topic2/research_screenshots/research1.png)

---
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

```
    P0
   /  \
 P1    P2
 |
 P3
```
![research2 binary](https://github.com/omniV1/CST-321/blob/main/src/Assignments/Topic2/research_screenshots/research2.png)
---
# Resources: 

##### padlet topic guide: Reha, M. (2024). [Topic 2 Powerpoint guide](https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/158247307)
##### assignment guide: Reha, M. (2024). [Activity 2 Assignment guide](https://mygcuedu6961.sharepoint.com/:w:/r/sites/CSETGuides/_layouts/15/Doc.aspx?sourcedoc=%7BFD1AEEC0-81CF-40E1-A169-85CE23F53355%7D&file=CST-321-RS-T2-Activity2Guide%20.docx&action=default&mobileredirect=true)

##### online resources: Kadam, P. (2024). Multithreading in c . [geeksforgeeks](https://www.geeksforgeeks.org/multithreading-in-c/)
##### online resources: Kadam, P. (2024). Signals in c language. [geeksforgeeks](https://www.geeksforgeeks.org/signals-c-language/)
##### online resources: https://www.youtube.com/watch?v=9seb8hddeK4 : [youtube](guide provided by instructor)
##### online resources: Barnes, R. (2020). Mutex vs Semaphore. [tutorialspoint](https://www.tutorialspoint.com/mutex-vs-semaphore)
##### online resources: Frasier, B. (2015). Mutex Synchronization in Linux with Pthreads.  [Youtube:](https://www.youtube.com/watch?v=GXXE42bkqQk)

