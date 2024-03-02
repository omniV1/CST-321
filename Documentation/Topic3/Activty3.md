#### Owen Lindsey

#### CST-321

#### Activity 3

#### Resources at bottom of page

---

# 2. More signals in Linux


## Theory of operations

| Components                   | Description                                                                                          |
|------------------------------|------------------------------------------------------------------------------------------------------|
| **Initialization**           | Parent creates a shared circular buffer and forks a child process. Both prepare for message passing. |
| **Inter-Process Communication** | Parent sends characters to the buffer and signals the child. Child wakes on signal to process data.  |
| **Shared Buffer Management** | Circular buffer used by parent for writing and child for reading messages, ensuring FIFO order.      |
| **Signal Handling**          | Child waits on `SIGUSR1`, wakes to read buffer. Parent signals after each character sent.            |
| **Program Termination**      | Parent sends '\0' to signal end. Child exits upon receiving it, then parent cleans up and exits.     |





## code :  



```c
struct CIRCULAR_BUFFER {
    int start;
    int end;
    char buffer[MAX];
};

struct CIRCULAR_BUFFER *buffer = NULL;
pid_t otherPid;

void signalHandler(int signum) {
    // Empty handler, just to interrupt sleep
}

void putValue(char value) {
    if (((buffer->end + 1) % MAX) == buffer->start) {
        printf("Buffer is full, producer must wait...\n");
    }
    buffer->buffer[buffer->end] = value;
    buffer->end = (buffer->end + 1) % MAX;
    printf("Put '%c' into buffer.\n", value);
    if (value == '\0') {
        kill(otherPid, WAKEUP); // Notify consumer about termination signal
    } else {
        kill(otherPid, WAKEUP); // Notify consumer a new value is available
    }
}

char getValue() {
    if (buffer->start == buffer->end) {
        printf("Buffer is empty, consumer must wait...\n");
    }
    char value = buffer->buffer[buffer->start];
    buffer->start = (buffer->start + 1) % MAX;
    printf("Got '%c' from buffer.", value);
    return value;
}



void producer() {
    const char *message = "Owen Lindsey\0\n"; // Include null terminator in message
    printf("Producer starting...\n");
    for (int i = 0; message[i] != '\0'; i++) {
        while (((buffer->end + 1) % MAX) == buffer->start) {
            printf("Producer waiting, buffer full...\n");
            sleep(1); // Wait for consumer to consume some data
        }
        printf("Producer sending: '%c'\n", message[i]);
        putValue(message[i]);
    }
    printf("Producer finished sending.\n");
}

void consumer() {
    printf("Consumer starting...\n");
    while (1) {
        char value = getValue();
        if (value == '\0') {
            printf("\nConsumer received termination signal. Exiting.\n");
            exit(0); // Exit the process gracefully
        } else {
            printf("Consumer received: '%c'\n", value);
            fflush(stdout); // Ensure output is printed immediately
        }
    }
}


int main() {
    buffer = mmap(NULL, sizeof(struct CIRCULAR_BUFFER), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (buffer == MAP_FAILED) {
        perror("mmap failed");
        exit(EXIT_FAILURE);
    }
    memset(buffer, 0, sizeof(struct CIRCULAR_BUFFER));

    // Setup signal handling
    struct sigaction sa;
    sa.sa_handler = &signalHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(WAKEUP, &sa, NULL);

    otherPid = fork();
    if (otherPid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (otherPid == 0) { // Child process
        consumer();
    } else { // Parent process
        producer();
        wait(NULL); // Wait for the child process to finish

        if (munmap(buffer, sizeof(struct CIRCULAR_BUFFER)) == -1) {
            perror("munmap failed");
            exit(EXIT_FAILURE);
        }
        printf("Parent process exiting.\n");
    }

    return 0;
}


```
## Key Functions and System Calls


| Function/System Call    | Description                                                                                   |
|-------------------------|-----------------------------------------------------------------------------------------------|
| `fork()`                | Creates a child process that is a copy of the parent process.                                 |
| `mmap()`                | Allocates a region of memory shared between the forked processes.                             |
| `signal()`              | Registers a signal handler for specific signals (`SIGUSR1` in this case).                     |
| `kill()`                | Sends a signal (`SIGUSR1`) from the parent process to the child process to indicate new data. |
| `sleep(1)`  | Pauses the consumer process until a signal is received, indicating data is ready.             |
| `munmap()`              | Unmaps the shared memory region upon program completion.                                      |
| `exit()`                | Exits the process, either after sending the complete message or receiving the termination signal. |
| `wait(NULL)`            | Waits for the child process to terminate before the parent cleans up resources.               |
| `putValue()`            | Custom function to insert a character into the circular buffer and signal the consumer.         |
| `getValue()`            | Custom function for the consumer to retrieve a character from the circular buffer.              |
| `producer()`            | Custom function where the parent process writes characters to the shared buffer.                |
| `consumer()`            | Custom function where the child process reads and prints characters from the shared buffer.     |


### Video explanation:


# 3. More Signals and Mutexes in Linux

## Theory of operations
| Components                     | Description                                                                                                                                                                                                                                                             |
|--------------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Mutex Usage**                | Mutexes control access to a shared global variable, `counter`, ensuring only one thread can modify or read the variable at any given time to prevent race conditions and maintain data integrity.                                                                       |
| **Counter Thread Operation**   | Locks the mutex before incrementing the counter for exclusive access, then sleeps for a second with the mutex locked, simulating a workload and allowing the monitor thread an opportunity to access the counter.                                                      |
| **Monitor Thread Operation**   | Attempts to lock the mutex every 3 seconds with `pthread_mutex_trylock`. If successful, it reads and prints the counter value. If it fails to acquire the lock because the counter thread has it, it increments a "misses" count.                                      |
| **Purpose of Sleep Mechanism** | Simulates realistic operational delays: in the counter thread, it represents the time taken to increment; in the monitor thread, it represents periodic checking of the counter value.                                                                                |
| **Handling of Resource Contention** | Demonstrates resource contention management via `pthread_mutex_trylock` in the monitor thread, preventing indefinite blocking if the mutex is already locked by the counter thread, and by incrementing a "misses" count when access to the counter is not possible. |
| **Program Termination**        | Runs based on a specified duration (`run_time_seconds`), with the main function waiting for both threads to complete their execution using `pthread_join` before cleaning up resources and exiting.                                                                     |

## Code:

```c

#define RUN_TIME_MINUTES 1 // Specify run time in minutes

pthread_mutex_t mutex;
int counter = 0; // Global counter variable
int run_time_seconds; // Total run time in seconds

// Counter thread function
void* counter_thread_func(void* arg) {
    int elapsed_time = 0;
    while (elapsed_time < run_time_seconds) {
        pthread_mutex_lock(&mutex); // Lock the mutex
        counter++; // Increment the counter
        printf("Counter incremented to: %d\n", counter);
        sleep(1); // Sleep for 1 second with the mutex locked
        pthread_mutex_unlock(&mutex); // Unlock the mutex after sleeping
        elapsed_time++;
    }
    return NULL;
}

// Monitor thread function
void* monitor_thread_func(void* arg) {
    int misses = 0;
    int elapsed_time = 0;
    while (elapsed_time < run_time_seconds) {
        if (pthread_mutex_trylock(&mutex) == 0) { // Try to lock the mutex
            printf("Monitor read: Counter value: %d\n", counter);
            pthread_mutex_unlock(&mutex); // Unlock the mutex
        } else {
            misses++; // Increment misses if the mutex is locked
        }
        sleep(3); // Sleep for 3 seconds
        elapsed_time += 3;
    }
    printf("Total misses by monitor thread: %d\n", misses);
    return NULL;
}

int main() {
    pthread_t counter_thread, monitor_thread;
    pthread_mutex_init(&mutex, NULL); // Initialize the mutex

    run_time_seconds = RUN_TIME_MINUTES * 60; // Convert run time from minutes to seconds

    // Create the counter and monitor threads
    pthread_create(&counter_thread, NULL, counter_thread_func, NULL);
    pthread_create(&monitor_thread, NULL, monitor_thread_func, NULL);

    // Wait for both threads to finish
    pthread_join(counter_thread, NULL);
    pthread_join(monitor_thread, NULL);

    // Clean up and exit
    pthread_mutex_destroy(&mutex);
    printf("Main program finished.\n");
    return 0;
}


```

## Key Functions and System Calls

| Function Name            | Description                                                                                       |
|--------------------------|---------------------------------------------------------------------------------------------------|
| `counter_thread_func`    | Function for the counter thread that locks the mutex, increments the counter, sleeps for a second with the mutex locked, then unlocks it. |
| `monitor_thread_func`    | Function for the monitor thread that attempts to lock the mutex every 3 seconds to read the counter. If the lock is unavailable, increments a "misses" count. |
| `pthread_mutex_lock`     | Function that locks the mutex to ensure exclusive access to the global counter variable.         |
| `pthread_mutex_unlock`   | Function that unlocks the mutex, allowing other threads to access the counter variable.          |
| `pthread_mutex_trylock`  | Function that attempts to lock the mutex without blocking. If the mutex is already locked, the function returns immediately with an error. |
| `pthread_create`         | Function that creates a new thread and starts it with a specified function and arguments.        |
| `pthread_join`           | Function that waits for a thread to terminate, ensuring that the main program synchronizes with thread completions. |
| `pthread_mutex_init`     | Function that initializes a mutex before it is used.                                             |
| `pthread_mutex_destroy`  | Function that destroys a mutex, releasing any resources it might hold.                           |
| `sleep`                  | Function that suspends execution of the current thread for a specified number of seconds, used to simulate processing or wait time. |


### Video explanation:

# 4. More Signals and Semaphores in Linux

# Theory of operations
| Component                 | Description                                                                                                     |
|---------------------------|-----------------------------------------------------------------------------------------------------------------|
| **Semaphore Creation**    | A semaphore with an initial count of 1 is created, shared between the parent and child processes.               |
| **Child Process**         | Executes `childProcesses()` function, locks the semaphore, simulates a long task, releases semaphore, then exits. |
| **Parent Process**        | Starts a `checkThread` that sleeps for 10 seconds, then tries to lock the semaphore with `sem_trywait`.         |
| **Semaphore Lock Check**  | If `sem_trywait` fails, the `status` is set to 1, indicating the semaphore is still locked (child is hung).     |
| **Thread Joining**        | The parent process joins the `checkThread`. If `status` is 1, it sends `SIGKILL` to terminate the hung child.   |
| **Semaphore Re-acquisition** | After child termination, the parent tries to lock the semaphore again to ensure it's released.                  |
| **Resource Cleanup**      | The semaphore is destroyed using `sem_destroy`, and the parent process exits cleanly.                           |

##  Code:

```c

sem_t semaphore;
pid_t child_pid;

void* monitor_child(void* arg) {
    printf("Parent process is monitoring the child process...\n");
    sleep(10); // Sleep for 10 seconds to give child process time to lock the semaphore
    if (sem_trywait(&semaphore) != 0) {
        printf("Child process might be hung. Parent process needs to take action...\n");
        return (void*)1;
    }
    sem_post(&semaphore); // Release the semaphore if acquired
    return (void*)0;
}

void child_process() {
    sem_wait(&semaphore); // Child process locks the semaphore
    printf("Child process has locked the semaphore, starting long operation...\n");
    sleep(60); // Simulate long operation
    printf("Child process has completed the operation, releasing semaphore...\n");
    sem_post(&semaphore); // Release semaphore
    _exit(0); // Child process exits
}

int main() {
    sem_init(&semaphore, 0, 1); // Initialize semaphore with count 1
    child_pid = fork();
    if (child_pid == 0) {
        child_process();
    } else {
        pthread_t tid;
        void* result;
        pthread_create(&tid, NULL, monitor_child, NULL);
        pthread_join(tid, &result);
        if ((long)result == 1) {
            kill(child_pid, SIGKILL); // Terminate the hung child process
            waitpid(child_pid, NULL, 0); // Wait for the child process to terminate
        }
        sem_destroy(&semaphore); // Destroy the semaphore
        printf("Parent process exiting...\n");
    }
    return 0;
}
```


## Key Functions and System Calls

| Function Name        | Description                                                                                          |
|----------------------|------------------------------------------------------------------------------------------------------|
| `sem_init`           | Initializes the semaphore before it is used.                                                         |
| `fork`               | Creates a new process by duplicating the calling process.                                            |
| `sem_wait`           | Locks the semaphore by decreasing its count, blocking if the count is zero.                          |
| `sem_post`           | Unlocks the semaphore by increasing its count, allowing other processes to acquire it.               |
| `sem_trywait`        | Non-blocking attempt to lock the semaphore. Returns an error if the semaphore cannot be acquired.    |
| `pthread_create`     | Creates a new thread to monitor the child process.                                                   |
| `pthread_join`       | Waits for the thread to terminate and collects the exit status.                                      |
| `kill`               | Sends a signal to a process or a group of processes, typically to terminate the process.             |
| `waitpid`            | Waits for the child process to change state, used to collect the termination details of the child.   |
| `sem_destroy`        | Destroys the semaphore, releasing any resources it might hold.                                       |
| `sleep`              | Suspends the execution of the



# 5. Research Question:

## System State: Deadlocked vs. Safe

Yes, a system can be in a state that is neither deadlocked nor safe, which is often referred to as an "unsafe" state. An unsafe state is a situation where there is a sequence of resource allocations that could potentially lead to a deadlock, but the deadlock has not yet occurred. This means that while the current sequence of actions could lead to a scenario where no progress is possible (deadlock), the system is currently not in deadlock.

### Example of an Unsafe State:
Imagine a system with two processes, P1 and P2, and two types of resources, R1 and R2, each with one instance available. The following scenario illustrates an unsafe state:
- P1 holds R1 and requests R2.
- P2 holds R2 and requests R1.

This is an unsafe state because there exists a sequence of events (P1 acquiring R2 and P2 acquiring R1) that would lead to a circular wait and therefore a deadlock. However, the system is not deadlocked yet because the requests have not been granted.

A "safe" state, in contrast, is one where there is at least one sequence of resource allocation that allows all processes to complete successfully without any possibility of deadlock.

## 1. Deadlock Prevention Using Time Limits

The described method of using time limits for resource requests is a strategy to prevent deadlock by imposing a waiting time constraint on resource acquisition. This is not a comprehensive solution to the problem of deadlock for several reasons:

### 2. Resource Thrashing:
If the time limit is too short, it may cause processes to repeatedly timeout and retry, leading to resource thrashing where a significant amount of system time is spent on context switching rather than productive work.

### 3. Starvation:
Some processes may starve and never get the resources they need because they always hit the time limit due to heavy contention, especially if the system is under high load.

### 4. Complexity and Overhead:
Implementing timers adds complexity to the resource management system and additional overhead in terms of system resources (like memory for timer structures and CPU time for managing these structures).

### 5. Does Not Address Underlying Issues:
This strategy does not solve the fundamental issues that lead to deadlocks, such as circular waits and uncontrolled allocation of resources. It merely tries to mitigate the impact by forcefully interrupting waiting processes.

While time limits can be part of a broader strategy for deadlock avoidance or detection and recovery, they are not sufficient on their own as a prevention mechanism. A more robust approach to deadlock prevention might involve a combination of hierarchical ordering of resources, pre-emptive resource allocation strategies, and careful management of process states and resource requests.


# Resources:

Barnes, R. (2020). Mutex vs Semaphore. tutorialspoint: https://www.tutorialspoint.com/mutex-vs-semaphore

Frasier, B. (2015). Mutex Synchronization in Linux with Pthreads. Youtube: https://www.youtube.com/watch?v=GXXE42bkqQk

//Kadam, P. (2024). Signals in c language. geeksforgeeks : https://www.geeksforgeeks.org/signals-c-language/

 Reha, M. , (2024). Activity 3 Assignment guide: https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582473094

 Reha, M. (2024). Topic 3 Lecture : https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582472940


Tanenbaum, A. (2023). Deadlocks. In Modern Operating Systems (Fifth).: https://bibliu.com/app/#/view/books/9780137618798/epub/OPS/xhtml/fileP700101801700000000000000000254A.html#page_456
