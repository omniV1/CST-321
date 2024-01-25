#### Operating systems fundamentals Topic 1 notes: 


## What is an operating system? 

- Software that manages computer hardware and software resources and provides common services for computer programs. 

***COMMON FEATURES***

- Process management 
- interrupts
- Memory Management 
- File System
- Device Drivers
- Networking 
- Security
- I/O 

---

### What are the main functions of an operating system? 

- Manage resources such as hardware, application programs, I/O. 

***OS RUNS IN KERNEL MODE***

***COMMON APPS RUN IN USER MODE***

---


### What are some Unique Characteristics of OS on different platforms? 

- Desktop: Support Multi-programming and good support for a single user 

- Mobile: Google OS vs Apple OS hte hardware consists of multi-core CPU's, GPS, Cameras etc. 

- Cloud: Offers direct access to a virtual machine, which the user can use in any war he sees fir. thus the same cloud may run different operating systems, possibly on the same hardware. 


# TIMELINE OF OPERATING SYSTEMS 

### 1st Generation - Vacuum Tubes (1945-1955) 

- started becoming commercially available in the 1950's

- Vacuum tubes allowed for mechanical computation (switching on and off) at a rapid rate.

---

### 2nd Generation - Transistors and Batch Systems (1955 - 1965)

- Marked by the introduction of transistors 

- considered reliable compared to the vacuum tubed predicessor

- Junction transistors seemed to cure the prior issues in transistor computing. 

- Many claim to have built the "first transistorized computer" EI: ***IBM, Harwell,  Burroughs Corp, MIT, etc***

- IBM delivers a comercially available transistor calculator 

- Philco commercially producing and ships large-scale  all-transistor computers in 1958

- all-transistor computers become commerically available by multiple manufacturers between 1958 - 1964 

- the availability allowed schools and hobbyists to pick up computers for the first time without having the burden of constant disrepair. 

---

### 3rd Generation - ICs and Multiprogramming (1965 - Present)

- Marked the arrival of integrated circuts or IC or microchips. 

- made up of transistors, resistors, and capacitors. These are etched onto a small piece of a semiconductor material (typically silicon) .

- being smaller, faster, and more reliable lead to IC's in all common computers. 

- photolithography keeps the size and cost low. This process uses light to transfer a pattern onto the sillicon waffer, that pattern then gets the corresponding components installed through various means of meachine processing. The sizes the process can shrink down to a few nanometers in size so it is an extremely precise process. 

- The race from 1965 to 1980 onwards was purely based on whos patterns where more effecient and reliable while staying cost effective. 

#### Various integration scales

- SSI (small scale integration ) meaning the use of few transistors or a simple linear computers. 

- MSI (medium scale integration) meaning the use of hundreds of transistors using MOSFET scaling technology, it is a high density chip that only expanded according to Moore's law. 

- LSI (Large scale integration) driven by MOSFET scaling technology in the mid 1970's allowed tens of thousands of transistors per chip. Typically designed by teams of engineers and supported the first ever microprocessors. 
 
  - true LSI circuts, approaching 10,000 transistors, began to be manufactured around 1974. These allowed for computer main memories and second gen microprocessors.

- VLSI (very large scale integration) started in the 1980's and as Im sure we understand now the transisitor count exponentially increases. 

- ULSI, WSI, SOC, and 3D-IC

---
### What is the structure of an Operating System? 
***The six designs are: 

***Monolithic Systems*** :  By far the most common organization, in the monolithic approach the entire operating system runs as a single program in kernel mode.

***layered systems*** : organize the operating system as a hierarchy of layers, each one constructed upon the one below 

***MicroKernels***:The basic idea behind the microkernel design is to achieve high reliability by splitting the operating system up into small, well-defined modules, only one of which—the microkernel—runs in kernel mode and the rest run as relatively powerless ordinary user processes

***Client-server systems*** : slight variation of the microkernel idea is to distinguish two classes of processes, the servers, each of which provides some service, and the clients, which use these services. This model is known as the client-server model. Often the lowest layer is a microkernel, but that is not required. The essence is the presence of client processes and server processes.

***Virtual Machines***: users who want to be able to run two or more operating systems at the same time, say Windows and Linux, because some of their favorite application packages run on one and some run on the other.

***Exokernels***:  The exokernels job is to allocate resources to virtual machines and then check attempts to use them to make sure no machine is trying to use somebody else’s resources. Each user-level virtual machine can run its own operating system, except that each one is restricted to using only the resources it has asked for and been allocated.

---

### Layered structurer of an OS 

- layer 5: User programs 

- layer 4: buffering for input and output 

- layer 3: Process management

- layer 2: memory managment 

- layer 1: CPU sheduling 

- layer 0: hardware

---

### What is Virtualization? 
- allows the user to run multiple operating systems for their daily operations. 

    - examples: a web server on Linux, a mail server on Windows. 

- A VMM ***(Virtual Machine Monitor)*** creates the illusion of multiple (virtual machines) on the same physical hardware. 

    - hypervisor is an example of a VMM. It only does one thing: emulate multiple copies of the bare methal. It has fewer bugs because it has fewer lines of code than a whole OS. 

- Virtualization allows a single computer to host multiple virtual machines, each potentially runnig a different OS. 

- Programers can use VMMS to ensure their software works on other OS's than their host OS. 

### Type 1 && Type 2 hypervisor

- ***Type 1 hypervisor***: runs at the highest privilage and supports multiple copies of the actual hardware, called virtual machines and runs directly on the hardware. 

- ***Type 2 hypervisor***: is a progran that relies on its host OS to allocate and schedule resources, this reflects a regular Process. Type 2 still pretends to be a full computer with a CPU and various devices.

- Both types of hypervisor must execute the machines instruction set in a safe manner. 

   - For instance, an opertaing system runnnig at the top of hypervisor may change and even mess up its own page tables, but not those of others. 

- ***guest operating system*** : is what the operating system running on top of the hypervisor. 

- For a type 3 hypervisor, the operating system is running on the hardware called ***host operating system***. 

---
### what is a Linux Terminal? 

- The architecture in Linux does not require the graphical interface for system operation. In many Linux Distros the default user interface is the real terminal.

-  Examples of terminal functions: 
   - Extensive, system-wide configuration and administration. 
   - File and folder administration.
   - The ability to access, transfer and share data between machines. 

   - Extensive system monitoring. 

---
### What are some Linux Termianl tips? 
***Command History***
- Bash remembers a history of the commands you type into it. You can use the up and down arrow keys to scroll through the commands you've recently used, so you can pipe it to grep to search for commands you've recently used. 

***Tab Completion***
- type in the first 1 or 2 characters of a filename and then hit the tab key!

***Pipes***
- Pipes allow you to send the output of a command to another command. 
   - example, ls | grep word. 

***Output Redirection***
- The > character redirects a commands output to a file instead of another command. 
    - Example, ls >file1

***Copy/Paste***
- Highlight the text of the command you want. 
    - Press Ctrl + C to copy the text and Ctrl + V to paste.
---
### What is a Linux shell script? 

- A shell script is a computer program designed to be ru by the unix shell via the command-line interpreter (CLI). 

- The shell script is written as text file,  which contains all the commands you wish to execute, and executed from a command prompt in a Terminal session. 

- The various dialects of shell scripts are considered to be scripting languages. The scripting language even has support for script variables, conditional logic, loops, etc. 

---
### The Linux System 

- The Linux kernel is the very heart of a Linux system. 

- it controls the resources, memory, schedules processes and thier access to CPU and is respsonsible for commucation between software and hardwar components. 

- the kernel provides the lowest- level abstraction layer for the resources ike memory, CPU, and I/O devices. 

- applications that want to perform any function with these resources communicate with the kernel using system calls.

---

### what is kernel mode vs user mode? 

##### Kernel mode / supervisor mode
- reserved for the most trusted functions of the OS 
     - includes device drivers, and other low level operations that require direct interaction with the hardware. 
- If a process operating in kernel mode crashes, it can lead to a system failure 
    - (like blue screen of death in windows). 

- some operations can only be completed in kernel mode. 
    - virtual memory management, handling interupts, and managing I/O operations. 

##### User mode

- is a restricted processing mode designed for applications, environment subsystems, and integral subsystems. 
     - in user mode the code cannot directly access hardware or reference memory. Instead, it must use API's and system calls to request services from the OS kernel. 

- If a process crashes in user mode, the OS typically can recover by terminating the faulty application. 
   - this process keeps the system stable because user mode processes are isolated from each other and from the kernel. 

- The restrictions of user mode prevent user applications from directly interfering with one another. 
    - for example searching google on chrome will not interfer with you searching google on edge.

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

###Research POSIX Process Functions 
- ***What is POSIX?***

  - is a family of standards specified by the IEEE Computer Society for maintaining compatibility between operating systems. POSIX defines both the system and user-level application programming interfaces (APIs), along with command line shells and utility interfaces, for software compatibility (portability) with variants of Unix and other operating systems. POSIX is also a trademark of the IEEE. POSIX is intended to be used by both application and system developers.


- ***What POSIX functions can be used to manage a process?***
     
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


1. prctl(): Performs various operations on a process such as setting the name, altering kernel options, etc.

---

