### Topic 2 notes: 
---

### What is a Process? 

- a process is just an instance of an executing program, including the current values of the program counter, registers, and variables. 

- the real CPU swithces back and forth from process called multiprogramming. 

- if there are two cores in a CPU or two single core CPUs each of them can only run one process at a time. 

- a single processor may be shared among several processes, with some scheduling alogrithim being accustomeed to determine when to stop work on one process and service a different one. 

- in contrast, a program is something that may be stored on disk, not doing anything. 

- ***multitasking is managed by the linux kernel via the Process Scheduler***

- ***Stack*** The process Stack contains the temporary data such as method/function parameters, return address and local variables. 

- ***Heap*** this is dynamically allocated memory to a process duting its run time. 

- ***Text*** This includes the current activity represented by the value of the processors registers. 

- ***Data*** This section contains the global and static variables. 
---
### What are the states of a Process

- ***Running*** actuallying using the CPU in that instant

- ***Ready*** runnable; temporarily stopped to let another process run

- ***Blocked*** unable to run until some external event happens. 

- ***Process Scheduler*** controls the states of a Process.

---

### What is a Process environment

- The Process's enviornment is inherited from its parent and is composed of two null-terminated vectors: 

    1. the argument vector lists the command-line arguments used to invoke the running program; conventrionally starts w the name of the program itself

    1. The environment vector is a list of "Name=Value" pairs that associates named environment variables with arbitrary textual values. 

- passing environment variables mechanism provides a customization of the operating system that can be set on a per-process basis as opposed to being configured for the system as a whole. 

---

### How do I terminate a Process

- Typical conditions which terminate a process

1. Normal exit (Voluntary)

1. Error exit (Voluntary)

1. Fatal error (involuntary)

1. Killed by another process (involuntary)

    - in Linux you can kill a stubborn process with the kill shell command kill pid(kill processor id)
   - or in the case the process is not terminated use a more drastic option kill -9 pid

---

### Research POSIX Process Functions 
- ***What is POSIX?***

  - is a family of standards specified by the IEEE Computer Society for maintaining compatibility between operating systems. POSIX defines both the system and user-level application programming interfaces (APIs), along with command line shells and utility interfaces, for software compatibility (portability) with variants of Unix and other operating systems. POSIX is also a trademark of the IEEE. POSIX is intended to be used by both application and system developers.


- **What POSIX functions can be used to manage a process?**
     
 1. fork(): Creates a new process. The new process is a copy of the calling process.

1. exec() Family: Replaces the current process image with a new process image. It includes various functions like execl(), execp(), execle(), execv(), execve(), execvp().

1. wait() and waitpid(): These functions are used to wait for state changes in a child of the calling process, and capture the exit status.

1. _exit() or exit_group(): Terminates the current process. _exit() is used for a single-threaded process, while exit_group() is used to exit all threads in a process.

1. abort(): Sends the SIGABRT signal to the current process to cause an abnormal process termination.

1. kill(): Sends a signal to a process or a group of processes. Usually used to terminate processes.

1. getpid(): Returns the process ID of the calling process.

1. getppid(): Returns the parent process ID of the calling process.

1. getpgid() and setpgid(): These functions get and set the process group ID of a process respectively.

1. setsid(): Creates a new session and sets the process group ID.

1. nice(): Changes the nice value of a process, affecting its scheduling priority.

1. setpriority() and getpriority(): Get or set the nice value of a process, process group, or user.

1. clone(): Creates a new process, in a manner similar to fork(). It's used to implement threads.

1. setuid(), setgid(), seteuid(), setegid(): Set the user/group identity of the process.

1. sigaction(), sigprocmask(), pause(), alarm(), sleep(): Functions for handling signals.

1. sched_setscheduler(), sched_getscheduler(), sched_setparam(), sched_getparam(): Functions for setting and getting the scheduling policy and parameters of a process.

1. exit(): Ends the process, with cleanup and flushing of I/O buffers.

1. atexit(): Registers a function to be called at normal process termination, either via exit() or return from the program's main().

1. raise(): Sends a signal to the current process.

---

## Why inter-process communication? 
- processes do not have access to memory between one another.
  
- To communicate across processes : shared memory buffer, file, pipe, and a **signal**.
  
- This is known as inter process communication.

---
### What is a thread

- essentially the flow of execution through the process code.

- **lightweight process**.

- allows parallelism to enhance application performance.

- Each thread belonfs to one process and not thread can exist outside of a process.

  ### differences between process and threads.

  | Process | Thread |
  |-------- | ------ |
  |Heavy weight | Light weight |
  | switching requires interaction w OS | does not need to interact w OS for switching |
  | executes same code in processing enviornment however has its own memory and file resources| can share same set of open files, child processes.|
  | if process is blocked then no other process can execute | there cannot be blockages |
  | processes operate indepently | threads can write over other threads data |

  ---
  ## What is Concurrency?

- Threads run in parallel (allowing concurrently running code)

- Threads in the same process share the same address space.

- When shared between threads simple data structures become prone to race conditions if they require more than one CPU instruction to update:

      - Two threads may end up attempting to update the data structure at the same time and find it unexpectdly changing.

      - Bugs caused by race conditions can be vey difficult to reproduce and isolate

- To prevent issues issues thrading API'd offer syncronization primitives such as mutexes and semapgores to lock data structers afainst concurrent access.

### What shared resource in a computer does the Operating system need to protect from concurrent access? 

- Memory

- Disk managment 

- File I/O

---
### What is a linux pthread? 

- Linux refers to them as tasks rather than threads.

  - To use pthreads you will need to include **pthread.h** in your program.

  - To compile use -pthread(or -lpthread) option. This option tells the compiler that your program requires threading support.
 
  - To create a thread use the function pthread_create.

``` C
{
int pthread_create(pthread_t*thread,const pthread_attr_t *attr,void*(*start_routine)(void *),void *arg);
}
```
  - This function takes four arguments:
    
    1. The first pointer is to a variable that will hold the id of the newly created thread.
     
    2. points to attributes that we can use to tweak and tune some of the advanced features of pthreads.
    
    3. points to a function that we want to run
       
    4. pointer that we will give to our function.     
    
---

### Why do I need threads? 

- Being able to run multiple activites within an app at a single time is important.

- Some of these may block from time to time. By decomposing such an application into multiple sequential threads that run in quasi-parallel, the programming model becomes simpler.

- we can think simpler as we do not need to focus on interupts, timers, switches etc.

- parallelism



  
---

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
  
