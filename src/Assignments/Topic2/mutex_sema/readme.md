##### Owen Lindsey
##### Understanding mutexes and semaphores
##### Date: 2/11/2024
##### CST-321

# Detailed Description of the Scenario
In our simplified scenario, a group of neighborhood kids runs a lemonade stand. To ensure the smooth operation of their stand, they face two main challenges:

1. Shared Refrigerator Access: Only one kid can use the refrigerator at any given time to either restock lemonade pitchers or get more lemons. This situation requires a mechanism to prevent multiple kids from trying to access the refrigerator simultaneously, leading to chaos or accidents.

2. Limited Serving Cups: The lemonade stand has a limited number of cups available for serving customers. To manage this limitation and serve customers efficiently, the kids need a system that allows only a certain number of them to serve lemonade at the same time.

# Justification for the Use of Mutexes and Semaphores

- Mutex for Refrigerator Access: A mutex is ideal for managing access to the refrigerator. It ensures that when one kid is using the refrigerator, others must wait their turn, thereby preventing interference and accidents.

- Counting Semaphore for Serving Cups: A counting semaphore perfectly fits the scenario of limiting the number of kids serving lemonade concurrently. It starts with a count equal to the number of available cups. Each kid serving lemonade decrements this count, and when there are no cups left, other kids must wait until a cup becomes available again.

| Synchronization Mechanism | Pros   | Cons   |
|------------|--------------|------------------|
| **Mutexes**               | Simple and effective for ensuring exclusive access to a resource. Prevents data corruption and ensures safety. | Can lead to deadlocks if not implemented carefully. Limited to binary states, making it unsuitable for counting resources. |
| **Semaphores**            | Flexible in managing access to a pool of resources. Can allow multiple threads (or, in our analogy, kids) to access a resource up to a specified limit. | More complex to understand and implement correctly. Improper use can lead to complicated synchronization issues. |

# Comparison of Working and Non-synchronized Code Segments

| Aspect               | Working Segment                                                    | Non-Working Segment                                               | Notes                                                                                                             |
|----------------------|--------------------------------------------------------------------|-------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------------------|
| **Refrigerator Access** | Usage of mutex to ensure exclusive access: `pthread_mutex_lock(&fridgeMutex);` ... `pthread_mutex_unlock(&fridgeMutex);` | Direct checks and modifications without synchronization: `if (!refrigeratorOpen) { refrigeratorOpen = 1; ... }` | Synchronization with a mutex prevents multiple threads from accessing the refrigerator simultaneously, eliminating race conditions. |
| **Serving Lemonade**    | Semaphore management for cups: `sem_wait(&cupsSemaphore);` ... `sem_post(&cupsSemaphore);`    | Direct manipulation of `availableCups` without synchronization. | The semaphore ensures a controlled serving process, allowing only as many kids to serve as there are cups available, preventing resource exhaustion. |
| **Thread Safety**       | Mutex and semaphore usage ensure thread safety in resource access and modification. | Lack of synchronization exposes shared resources to concurrent access issues. | Synchronization mechanisms like mutexes and semaphores are essential for thread safety in concurrent programming. |
| **Resource Management** | The same approach of correctly freeing memory: `free(arg);`          | Memory management remains correct but requires synchronization to ensure safety. | Proper memory management is crucial, but synchronization ensures that resources are accessed and modified safely and correctly. |


### Why Synchronization is Better

- Reliability: Synchronization mechanisms ensure that the program operates correctly under all conditions by preventing race conditions and data corruption.

- Consistency: By controlling access to shared resources, synchronization guarantees that every thread sees a consistent view of the data.

- Efficiency: Proper synchronization can lead to more efficient resource utilization, avoiding unnecessary waits or conflicts.

- Maintainability: While adding complexity, synchronization makes the program's behavior more predictable, which simplifies maintenance and debugging.


#### Unsynchronized version key code parts:
```c
// Direct checks and modifications of shared resources without synchronization/ // 
if (!refrigeratorOpen) {
    refrigeratorOpen = 1; // Attempt to mark the refrigerator as in use
    // Access the refrigerator
    refrigeratorOpen = 0; // Mark the refrigerator as free
}

if (availableCups > 0) {
    availableCups -= 1; // Decrement the number of available cups
    // Serve lemonade
    availableCups += 1; // Increment the number of available cups back
}

```
#### Potential Failures in Non-synchronized Code:

- Refrigerator Access Conflicts: Two or more threads may simultaneously set refrigeratorOpen to 1, leading to a scenario where the refrigerator is thought to be in use by multiple kids at once, causing confusion and potential 'spills' or 'loss' of lemonade.

- Cups Count Mismatch: Without synchronization, the availableCups variable could be decremented by one thread and simultaneously checked by another, leading to a situation where more lemonade is served than there are cups available, resulting in a negative count of cups.
--- 
#### Synchronized Version Key Parts:
```c
/////////////////// Mutex //////////////////////
pthread_mutex_t fridgeMutex = PTHREAD_MUTEX_INITIALIZER;

// Using a mutex to ensure exclusive access to the refrigerator
pthread_mutex_lock(&fridgeMutex);
// Access the refrigerator
pthread_mutex_unlock(&fridgeMutex);

//////////////// Semaphore /////////////////
sem_t cupsSemaphore;

// Initialization of the semaphore with the total number of available cups
sem_init(&cupsSemaphore, 0, TOTAL_CUPS);

// Using a semaphore to manage serving lemonade based on available cups
sem_wait(&cupsSemaphore);
// Serve lemonade
sem_post(&cupsSemaphore);

```
#### What It Fixes:

- Exclusive Access: The mutex ensures that only one thread (kid) can access the refrigerator at a time. This fixes the race condition where multiple threads could change the refrigeratorOpen flag simultaneously, leading to inconsistent states or "spills" as multiple kids try to access the refrigerator at once.

- Resource Protection: By locking the mutex before accessing the refrigerator and unlocking it afterward, it guarantees that the shared resource is protected from concurrent access, ensuring that all refrigerator operations are performed safely and correctly.

- Controlled Serving Process: The semaphore manages the number of available cups, ensuring that no more kids serve lemonade than there are cups available. This corrects the issue where the availableCups count could become negative due to unsynchronized access, as it now requires a kid to wait for a semaphore signal before serving, representing the acquisition of a cup.

- Resource Availability: By signaling (incrementing) the semaphore after serving, it informs other threads that a cup has become available. This prevents the scenario where kids would attempt to serve lemonade without any cups available, leading to a situation where customers are left unserved.
