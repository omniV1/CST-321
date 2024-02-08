### Topic 2 notes: 

---

### What is a Process? 

- A process is an instance of an executing program, including the current values of the program counter, registers, and variables. 
- The real CPU switches back and forth between processes, a concept called multiprogramming. 
- If there are two cores in a CPU or two single-core CPUs, each of them can only run one process at a time. 
- A single processor may be shared among several processes, with some scheduling algorithm being accustomed to determining when to stop work on one process and service a different one. 
- In contrast, a program is something that may be stored on disk, not doing anything. 
- **Multitasking is managed by the Linux kernel via the Process Scheduler**.
- **Stack**: The process Stack contains temporary data such as method/function parameters, return address, and local variables. 
- **Heap**: This is dynamically allocated memory to a process during its runtime. 
- **Text**: This includes the current activity represented by the value of the processor's registers. 
- **Data**: This section contains the global and static variables. 

---

### What are the states of a Process

- **Running**: Actually using the CPU in that instant.
- **Ready**: Runnable; temporarily stopped to let another process run.
- **Blocked**: Unable to run until some external event happens. 
- **Process Scheduler** controls the states of a Process.

---

### What is a Process environment

- The Process's environment is inherited from its parent and is composed of two null-terminated vectors: 
    1. The argument vector lists the command-line arguments used to invoke the running program; conventionally starts with the name of the program itself.
    2. The environment vector is a list of "Name=Value" pairs that associates named environment variables with arbitrary textual values. 
- Passing environment variables mechanism provides customization of the operating system that can be set on a per-process basis as opposed to being configured for the system as a whole. 

---

### How do I terminate a Process

- Typical conditions which terminate a process:
    1. Normal exit (Voluntary)
    2. Error exit (Voluntary)
    3. Fatal error (involuntary)
    4. Killed by another process (involuntary)
    - In Linux, you can kill a stubborn process with the `kill` shell command (`kill pid`) or in case the process is not terminated use a more drastic option `kill -9 pid`.

---

### Research POSIX Process Functions 
- **What is POSIX?**
    - POSIX is a family of standards specified by the IEEE Computer Society for maintaining compatibility between operating systems. POSIX defines both the system and user-level application programming interfaces (APIs), along with command line shells and utility interfaces, for software compatibility (portability) with variants of Unix and other operating systems. POSIX is also a trademark of the IEEE. POSIX is intended to be used by both application and system developers.

- **What POSIX functions can be used to manage a process?**
     
    1. `fork()`: Creates a new process. The new process is a copy of the calling process.
    2. `exec()` Family: Replaces the current process image with a new process image. It includes various functions like execl(), execp(), execle(), execv(), execve(), execvp().
    3. `wait()` and `waitpid()`: These functions are used to wait for state changes in a child of the calling process, and capture the exit status.
    4. `_exit()` or `exit_group()`: Terminates the current process. `_exit()` is used for a single-threaded process, while `exit_group()` is used to exit all threads in a process.
    5. `abort()`: Sends the SIGABRT signal to the current process to cause an abnormal process termination.
    6. `kill()`: Sends a signal to a process or a group of processes. Usually used to terminate processes.
    7. `getpid()`: Returns the process ID of the calling process.
    8. `getppid()`: Returns the parent process ID of the calling process.
    9. `getpgid()` and `setpgid()`: These functions get and set the process group ID of a process respectively.
    10. `setsid()`: Creates a new session and sets the process group ID.
    11. `nice()`: Changes the nice value of a process, affecting its scheduling priority.
    12. `setpriority()` and `getpriority()`: Get or set the nice value of a process, process group, or user.
    13. `clone()`: Creates a new process, in a manner similar to fork(). It's used to implement threads.
    14. `setuid()`, `setgid()`, `seteuid()`, `setegid()`: Set the user/group identity of the process.
    15. `sigaction()`, `sigprocmask()`, `pause()`, `alarm()`, `sleep()`: Functions for handling signals.
    16. `sched_setscheduler()`, `sched_getscheduler()`, `sched_setparam()`, `sched_getparam()`: Functions for setting and getting the scheduling policy and parameters of a process.
    17. `exit()`: Ends the process, with cleanup and flushing of I/O buffers.
    18. `atexit()`: Registers a function to be called at normal process termination, either via exit() or return from the program's main().
    19. `raise()`: Sends a signal to the current process.

---

## Why inter-process communication? 

- Processes do not have access to memory between one another.
- To communicate across processes: shared memory buffer, file, pipe, and a **signal**.
- This is known as inter-process communication.

---

### What is a thread

- Essentially the flow of execution through the process code.
- A lightweight process allows parallelism to enhance application performance.
- Each thread belongs to one process, and no thread can exist outside of a process.

### Differences between Process and Threads

| Process                                      | Thread                                                           |
| -------------------------------------------- | ---------------------------------------------------------------- |
| Heavyweight                                  | Lightweight                                                      |
| Switching requires interaction with OS       | Does not need to interact with OS for switching                  |
| Executes the same code in a processing environment, has its memory and file resources | Can share the same set of open files, child processes |
| If the process is blocked, no other process can execute | There cannot be blockages                                         |
| Processes operate independently               | Threads can write over other threads' data                        |

---

## What is Concurrency?

- Threads run in parallel, allowing concurrently running code.
- Threads in the same process share the same address space.
- When shared between threads, simple data structures become prone to race conditions if they require more than one CPU instruction to update.
- Bugs caused by race conditions can be very difficult to reproduce and isolate.
- To prevent issues, threading APIs offer synchronization primitives such as mutexes and semaphores to lock data structures against concurrent access.

### What shared resource in a computer does the Operating system need to protect from concurrent access? 

- Memory
- Disk management 
- File I/O

---

### What is a Linux pthread _(POSIX Threads)_ ? 

- Linux refers to them as tasks rather than threads.
  - To use pthreads, you will need to include **pthread.h** in your program.
  - To create a thread, use the function `pthread_create`.
``` C
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
  - This function takes four arguments:
```
    
    1. The first pointer is to a variable that will hold the id of the newly created thread.
     
    2. points to attributes that we can use to tweak and tune some of the advanced features of pthreads.
    
    3. points to a function that we want to run
       
    4. pointer that we will give to our function.     
    
---

# Arguments for Using Threads

## First Argument
The main reason for having threads is that in many applications, multiple activities are going on at once. Some of these may block from time to time. By decomposing such an application into multiple sequential threads that run in quasi-parallel, the programming model becomes simpler. Instead of thinking about interrupts, timers, and context switches, we can think about parallel processes. Only now with threads we add a new element: the ability for the parallel entities to share an address space and all of its data among themselves. This ability is essential for certain applications, which is why having multiple processes (with their separate address spaces) will not work.

## Second Argument
A second argument for having threads is that since they are lighter weight than processes, they are easier (i.e., faster) to create and destroy than processes. In many systems, creating a thread goes 10–100 times faster than creating a process. When the number of threads needed changes dynamically and rapidly, this property is useful to have.

## Third Reason
A third reason for having threads is also a performance argument. Threads yield no performance gain when all of them are CPU bound, but when there is substantial computing and also substantial I/O, having threads allows these activities to overlap, thus speeding up the application.

## Fourth Reason
Finally, threads are useful on systems with multiple CPUs, where real parallelism is possible.

# Examples of Threads
- A server for a Website. Requests for pages come in and the requested page is sent back to the client. At most Websites, some pages are more commonly accessed than other pages. For example, Sony’s home page is accessed far more than a page deep in the tree containing the technical specifications of any particular camera. Web servers use this fact to improve performance by maintaining a collection of heavily used pages in main memory to eliminate the need to go to disk to get them.

# Research POSIX Thread Functions
## What is POSIX?
POSIX stands for Portable Operating System Interface; it is a family of standards specified by the IEEE for maintaining compatibility between operating systems. POSIX defines the application programming interface (API), along with command line shells and utility interfaces, for software compatibility with variants of Unix and other operating systems.

## What POSIX functions can be used to manage Threads?
POSIX thread (pthread) functions provide API for creating and managing threads. Key functions include `pthread_create` for creating threads, `pthread_join` for waiting for threads to finish, and `pthread_mutex_lock` for thread synchronization.


  
---

### **POSIX Threads**
| Thread call | Description | 
| ----------- | ----------- | 
| pthread_create | Create a new thread | 
| Pthread_exit | Terminate the calling thread | 
| Pthread_join | Wait for a specific thread to exit |
| Pthread_yield | Release the CPU to let another thread run | 
| Pthread_attr_init | Create and initialize a threads attribute structure | 
| Pthread_attr_destroy | Remove a threads attribute structure | 


---

### Race conditions 
### In class discussion 1/25

- ACTIVITY 2 Fork and producer nd consumer completed


### In class discussion 1/30

- producer and consumer walkthrough

|producer | consumer | 
|-------------|--------|
| writing / incrementing count   |   reading / decremeting count    | 
| while (!full) put data in buffer   |  sleeps and wait if buffer has no data       |
|signal consumer when full then sleep and wait | read data from buffer until all data is read | 
|  will start writing into buffer until ful    | sends signal to continue  |




- **circular buffer** 
   - count, read, and write. 
   - fork allows two processes to access shared memory
   
 - **signals**
   -   
### In class discussion 2/8/2024



---

