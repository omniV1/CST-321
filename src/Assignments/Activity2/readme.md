### Owen Lindsey
### Activity 2
### CST 321
---
# 1. Theory of Operation for POSIX `posix_spawn()` and `waitpid()`

The provided C program demonstrates the use of the `posix_spawn()` and `waitpid()` functions to execute an external application and wait for its completion.

## `posix_spawn()`
The `posix_spawn()` function is part of the POSIX operating system API, which is used to create a new child process in a manner similar to `fork()` followed by `exec()`. However, `posix_spawn()` is designed to be more efficient than the combination of `fork()` and `exec()` because it may avoid copying the address space of the parent process when that's not necessary.

When `posix_spawn()` is called, it takes the following parameters:

- `pid`: A pointer to a `pid_t` variable where the process ID of the spawned child process will be stored.
- `path`: The path to the program to be executed.
- `file_actions`: A set of file actions that are to be performed before the new program is executed, such as opening or closing files. This is typically passed as `NULL` if no file actions are needed.
- `attr`: The attributes for the new process, which control things like signal masks and scheduling. In this example, the default attributes are used.
- `argv`: An array of argument strings passed to the new program.
- `environ`: The environment of the spawned process, typically the same as the parent.

In the example, `posix_spawn()` is used to create a new process that executes the application provided as a command line argument. The process ID is printed to the console.

## `waitpid()`
After spawning the new process, the parent process needs to wait for the new child process to complete. This is done using the `waitpid()` function, which suspends execution of the calling process until the specified child process terminates.

The `waitpid()` function takes the following parameters:

- `pid`: The process ID of the child process to wait for. If set to `-1`, `waitpid()` waits for any child process.
- `status`: A pointer to an integer variable where the exit status of the child process will be stored.
- `options`: Options that modify the behavior of `waitpid()`. Passing `0` means that `waitpid()` will behave in a blocking mode, waiting for the child process to terminate.

In this program, `waitpid()` is called immediately after `posix_spawn()`. It waits for the spawned child process to terminate and then prints a message indicating that the process has finished.

This combination of `posix_spawn()` and `waitpid()` allows the program to execute another application, wait for it to complete, and obtain its exit status, all while providing feedback to the user via the console.

---

# 2. Theory of Operation for `fork()` and Signals in Linux

This C program demonstrates inter-process communication using the `fork()` system call and UNIX signals. The program creates two processes: a parent (producer) and a child (consumer). The child process waits for a `WAKEUP` signal from the parent process before it begins its operation.

## Signal Handling
The program defines a signal handler function `wakeup_handler` that prints a message when invoked. The signal handler is registered for the `SIGUSR1` signal using the `sigaction` system call, which is a user-defined signal in Linux often used for inter-process communication.

## Child Process
Upon creation, the child process enters a paused state by calling `pause()`, which suspends the process until a signal is received. Once the `SIGUSR1` signal is sent by the parent, the child's signal handler is invoked,

---

# 3. Theory of Operation for Fork and Signal Handling in Linux

## Overview

This program demonstrates inter-process communication (IPC) through signals in a Linux environment using the `fork()` system call to create two processes: a parent (producer) and a child (consumer). The communication is facilitated by UNIX signals, specifically custom signals (`SIGUSR1` and `SIGUSR2`) to synchronize actions between the processes.

## Process Creation and Roles
- **Forking**: The program starts by forking a new process using `fork()`. This creates two processes running concurrently: the parent process takes on the role of a consumer, and the forked child process acts as a producer.

- **Producer**: The child process, acting as the producer, runs a loop for 30 iterations. In each iteration, it prints a message to the console and sleeps for 1 second. When the iteration count reaches 5 and 15, it sends a `SIGUSR2` signal to the consumer (parent process) indicating a production event.

- **Consumer**: The parent process, acting as the consumer, initially waits for a `SIGUSR1` signal from the producer. Upon receiving the signal, it enters a loop of 20 iterations, where it prints a message and sleeps for 1 second in each iteration, simulating consumption. At iteration counts 2 and 10, it sends back a `SIGUSR1` signal to the producer, potentially to request more data or acknowledge receipt.

## Signal Handling
- **Registration**: Each process registers a signal handler at the beginning of the program. The producer process registers `signalProducer` to handle `SIGUSR1`, and the consumer process registers `signalConsumer` to handle `SIGUSR2`. These handlers print a message indicating the signal received, aiding in debugging and visualization of the IPC mechanism.

- **Sending Signals**: The `kill()` function is used by both processes to send signals to each other. The `otherPid` variable, set after forking, identifies the target process for the signal.

## Synchronization
- **Initial Wait**: The consumer process uses a blocking `pause()` call or similar mechanism to wait for the initial `WAKEUP` signal (`SIGUSR1`) from the producer before starting its consumption loop. This ensures that the consumer does not proceed without an initial go-ahead from the producer.

- **Intermittent Communication**: By sending signals at specific iteration counts, the processes demonstrate a simple protocol for intermittent synchronization, where the consumer can signal the producer to potentially alter its production rate or signal readiness for more data.

## Summary

This program showcases basic IPC through signals between a parent and child process in Linux, illustrating how signals can be used for synchronization and communication in concurrent programming. It also demonstrates process creation and management through the `fork()` system call, signal handling setup and invocation, and the use of process exit codes to indicate the outcome of each process.

---
# 4. Theory of Operations for Pthreads Program

## Overview

This C program demonstrates the use of POSIX threads (pthreads) to perform concurrent operations. It creates two threads named `pilot` and `maintainer`, which simulate the roles of an aircraft pilot and a maintenance engineer, respectively. The program highlights the creation, execution, and synchronization of threads in a Linux environment.

## Thread Functions

- **Pilot Thread**: The `pilot` function represents a pilot navigating through a series of checkpoints. The function runs a loop where it prints a message for each checkpoint and sleeps for 1 second, simulating the time taken to reach the next checkpoint.

- **Maintainer Thread**: The `maintainer` function represents a maintenance engineer performing routine checks. Similar to the `pilot` function, it runs a loop for maintenance rounds, printing a message and sleeping for 2 seconds to simulate the maintenance duration.

## Main Function

- The `main` function is the entry point of the program. It begins by creating two threads using `pthread_create()`:

  - The first thread executes the `pilot` function.
  - The second thread executes the `maintainer` function.

- After thread creation, `main` uses `pthread_join()` to wait for each thread to complete its tasks. This function ensures that the main program waits for the threads to finish their execution before terminating.

- The use of `pthread_join()` allows for proper synchronization, making sure that the `main` function only concludes after both threads (`pilot` and `maintainer`) have completed their execution.

- The `-pthread` flag in the compilation command links the pthread library and enables the use of pthread functions.

## Compilation and Execution

- The program is compiled with the `gcc` compiler using the `-pthread` flag to ensure the pthreads library is correctly linked.

- Upon execution, the program outputs the status messages from both threads, demonstrating their operation in parallel. The `sleep()` calls introduce a delay between messages, emulating real-time operations.

## Summary

The provided C program successfully illustrates the basic concepts of thread creation, execution, and synchronization in a Linux environment using the pthreads library. By personalizing the thread functions to represent a `pilot` and `maintainer`, the program also showcases how pthreads can be used to model real-world scenarios and concurrent tasks in software design.

---

# 5. Theory of Operation: Synchronizing Access to Bank Balance

In the context of a simulated bank program, two primary methods of thread synchronization are explored: mutexes and semaphores. Both approaches aim to prevent race conditions by ensuring that multiple threads do not concurrently modify the shared bank balance. This document explains the operational theory behind each method and their implications in the program.

## Mutex Implementation

The mutex version of the bank program utilizes a `pthread_mutex_t` object to manage exclusive access to the critical section where the bank balance is updated.

### Key Components:

- **Initialization**: `pthread_mutex_init(&mutex, NULL);`
- **Locking and Unlocking**:
    ```c
    pthread_mutex_lock(&mutex);
    balance += depositAmount;
    pthread_mutex_unlock(&mutex);
    ```
- **Finalization**: `pthread_mutex_destroy(&mutex);`

### Operation:

1. **Locking**: Before entering the critical section, a thread must acquire the mutex lock. If another thread already holds the lock, the requesting thread will block until the lock becomes available.
2. **Critical Section**: The section where the shared resource (bank balance) is modified is protected by the mutex. Only one thread can execute this section at a time.
3. **Unlocking**: After updating the balance, the thread releases the mutex lock, allowing other threads waiting for the lock to proceed.

### Outcome:

By serializing access to the critical section, the mutex implementation ensures that each deposit operation is processed fully before another begins, resulting in an accurate final balance of $2,000,000.

## Semaphore Implementation

The semaphore version employs a `sem_t` object, using the POSIX Semaphore API to regulate access to the critical section in a similar manner.

### Key Components:

- **Initialization**: `mutex = sem_open("Mutex", O_CREAT, 0644, 1);`
- **Wait and Post**:
    ```c
    sem_wait(mutex);
    balance += depositAmount;
    sem_post(mutex);
    ```
- **Finalization**: `sem_close(mutex);`

### Operation:

1. **Waiting (sem_wait)**: This operation decrements the semaphore. If the resulting value is negative, the thread blocks until the semaphore value is incremented by another thread.
2. **Critical Section**: Access to the bank balance update is controlled by the semaphore, ensuring that only one thread can make the deposit at any given time.
3. **Posting (sem_post)**: This increments the semaphore, potentially unblocking a thread waiting in `sem_wait`.

### Outcome:

Semaphores, like mutexes, effectively prevent concurrent access to the critical section. The final balance accurately reflects the total deposits, achieving the expected $2,000,000.

## Summary

Both mutexes and semaphores are effective synchronization primitives that can be used to protect shared resources in multithreaded applications. The choice between using a mutex or a semaphore can depend on specific program requirements and the desired level of control over thread execution order.
