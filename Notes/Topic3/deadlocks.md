# Introduction to Deadlocks

### What is a Deadlock

- **deadlocks** occur when **two competing actions wait** for the others to finish, which causes a blockage.

- Common issue in:
    - muti-processing systems
    - parallel computing


-  where **software locks** are used to handle shared resources and implement **process synchronization**.

- A dead lock occurs when a process or thread enters a **waiting** state because a **requested system** resource is held by another **waiting process**, which in turn is waiting for another resource held by another waiting process.

- If a process is unable to change its state indefinitely because the resources **requested** by it are being used by another **waiting** process then the system is said to be in a _deadlock_.

### A deadlock illistrated

1.  Four processes (blue lines) compete for one resource (grey circle), following a right-before-left policy

2. A deadlock occurs when all processes lock the resource simultaneously (black lines).

3. The deadlock can be resolved by breaking the symmetry. 

**Think of how we use stop lights and signs to avoid collisions while driving**

![deadlock](/home/owen/CST-321/Notes/Topic3/screenshots/deadlock.gif)

### How can I recover from a deadlock

1. **Preemption**
2. **Rollback**
3. **Killing processes**


###  Recovery Through Preemption
- recovering this way is typically impossible or extremely time intensive.

- Choosing the process to suspend depends largely on which ones have resources that can be taken back easily.

### Recovery through Rollback
 - To do the recovery, a process that owns a needed resource is rolled back to a point in time before it acquired that resource by starting at one of its earlier checkpoints.

 - **Warning:** All the work done since the checkpoint is lost (e.g., output printed since the checkpoint must be discarded, since it will be printed again).

- the process is reset to an earlier moment when it did not have the resource, which is now assigned to one of the deadlocked processes.

- If the restarted process tries to acquire the resource again, it will have to wait until it becomes available  

### Recovery through killing processes

- The crudest but simplest way to break a deadlock is to kill one or more processes.

- One possibility is to kill a process in the cycle. With a little luck, the other processes will be able to continue.

- If this does not help, it can be repeated until the cycle is broken.

- Alternatively, a process not in the cycle can be chosen as the victim in order to release its resources.

- In this approach, the process to be killed is carefully chosen because it is holding resources that some process in the cycle needs.

- For example, one process might hold a printer and want a plotter, with another process holding a plotter and wanting a printer.

**These two are deadlocked.**

- A third process may hold another identical printer and another identical plotter and be happily running. Killing the third process will release these resources and break the deadlock involving the first two.
