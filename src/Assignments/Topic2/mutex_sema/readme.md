##### Owen Lindsey
##### Understanding mutexes and semaphores
##### Date: 2/11/2024
##### CST-321
##### Screencast explanation : 

# Detailed Description of the Scenario Mutex

in this scenario, we explore how a group of neighborhood kids operates a lemonade stand with a twist: they must coordinate using a single refrigerator to chill their lemonade. The challenge is ensuring orderly access to avoid mix-ups and ensure fairness.

1. **Shared Refrigerator Access**: Only one kid can use the refrigerator at any given time to either restock lemonade pitchers or get more lemons. This situation requires a mechanism to prevent multiple kids from trying to access the refrigerator simultaneously, leading to chaos or accidents.

# Justification for the Use of Mutexes 

- **Mutex for Refrigerator Access**: A mutex is ideal for managing access to the refrigerator. It ensures that when one kid is using the refrigerator, others must wait their turn, thereby preventing interference and accidents.

| Synchronization Mechanism | Pros                                                        | Cons                                                         |
|---------------------------|-------------------------------------------------------------|--------------------------------------------------------------|
| **Mutexes**               | Ensures exclusive access to resources, preventing data corruption and ensuring safety. | Can lead to deadlocks if not carefully managed. Limited to binary (on/off) states. |

  
# Screenshots and explanations of console output

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
  ## Non-synchronized:

  ![no sync](https://github.com/omniV1/CST-321/blob/main/src/Assignments/Topic2/mutex_sema/screenshots/lemonade_zero_sync.png)

- ### Console Output Explanation

The output from the unsynchronized version of the lemonade stand program (`lemonade_zero_sync`) shows attempts by multiple kids (threads) to access the refrigerator and serve lemonade. Messages like "Kid 3 couldn't use the refrigerator because it's already in use" and "Kid 4 couldn't serve lemonade because there are no cups available" indicate race conditions. These arise from simultaneous access attempts to shared resources—refrigerator and cups—without synchronization, leading to access conflicts and resource shortages.



#### Potential Failures in Non-synchronized Code:

- **Refrigerator Access Conflicts**: Two or more threads may simultaneously set refrigeratorOpen to 1, leading to a scenario where the refrigerator is thought to be in use by multiple kids at once, causing confusion and potential 'spills' or 'loss' of lemonade.

- **Cups Count Mismatch**: Without synchronization, the availableCups variable could be decremented by one thread and simultaneously checked by another, leading to a situation where more lemonade is served than there are cups available, resulting in a negative count of cups.
--- 
# Synchronized W mutex Version Key Parts:

```c
// Function to simulate accessing the refrigerator and pouring lemonade
void* serveLemonade(void* arg) {
    int kidId = *(int*)arg;
    for (int i = 0; i < USES; i++) {
        pthread_mutex_lock(&fridgeMutex); // Acquire the mutex lock to use the fridge and pour lemonade
        if (lemonadeQuantity > 0) {
            printf("Kid %d is using the refrigerator.\n", kidId);
            sleep(1); // Simulate time to use the refrigerator
            lemonadeQuantity--; // Pour a cup of lemonade
            printf("Kid %d is done with the refrigerator. Lemonade left: %d\n", kidId, lemonadeQuantity);
        } else {
            printf("Kid %d found no lemonade left to pour.\n", kidId);
        }
        pthread_mutex_unlock(&fridgeMutex); // Release the mutex lock
    }
    free(arg); // Free the allocated memory
    return NULL;
}
```


### Synchronized with a mutex console output: 

![sync](https://github.com/omniV1/CST-321/blob/main/src/Assignments/Topic2/mutex_sema/screenshots/lemonade_mutex_sync.png) 

- the console output shows each kid accessing the refrigerator one at a time, and serving lemonade only when cups are available. This would be achieved by locking access to the refrigerator with a mutex. 


--- 

# Detailed Description of the Scenario Semaphore

- An airline operates with a limited fleet of airplanes, and pilots need to be assigned to available planes for their scheduled flights. Given the limited number of airplanes, the airline needs a system to ensure that only a designated number of pilots can access an airplane at any given time. 

# Justification for the Use of Semaphores
Semaphores are ideal for managing access to a pool of resources, like the airline's fleet of airplanes. They ensure that a specific number of pilots can be assigned airplanes at any given time, optimizing resource utilization while preventing overallocation.

| Synchronization Mechanism | Pros                                                          | Cons                                                      |
|---------------------------|---------------------------------------------------------------|-----------------------------------------------------------|
| **Semaphores**            | Flexible in managing access to a pool of resources. Can allow multiple threads (or, in our analogy, pilots) to access a resource up to a specified limit, ensuring efficient utilization of resources like airplanes. | More complex to understand and implement correctly. Improper use can lead to complicated synchronization issues, such as starvation, where some pilots might wait indefinitely if not managed properly. |


# Screenshots and explanations of console output


- unsynchronized code for airplane senario:
  
  ```c

  ```
![zero sync airplane](https://github.com/omniV1/CST-321/blob/main/src/Assignments/Topic2/mutex_sema/screenshots/airplane_zero_sync.png) 

### Key Issues with Non-Working Semaphore Scenario

- **Race Conditions**: Unsynchronized access to `airplanesAvailable` allows multiple pilots to decrement/increment this counter simultaneously, leading to more pilots being assigned than airplanes available.
- **Inconsistent Airplane Counts**: The output might show unrealistic airplane availability, such as assigning more pilots than there are airplanes, or even negative counts.
- **Conflicting Messages**: Pilots receiving conflicting information about airplane availability due to concurrent access issues.
- **Unrealistic Management**: Instantaneous replenishment of airplanes after usage is unrealistic, ignoring necessary logistics and maintenance times.


--- 
# Resources 

- Barnes, R. (2020). Mutex vs Semaphore. tutorialspoint: https://www.tutorialspoint.com/mutex-vs-semaphore

- Frasier, B. (2015). Mutex Synchronization in Linux with Pthreads. Youtube: https://www.youtube.com/watch?v=GXXE42bkqQk 

- Kadam, P. (2024). Multithreading in c . geeksforgeeks: https://www.geeksforgeeks.org/multithreading-in-c/

- Reha, M. (2024). Activity 2 Assignment guide: hhttps://halo.gcu.edu/resource/5d85b77c-19f5-4266-ac1c-ceb57a98052a

- Reha, M. (2024). Topic 2 Powerpoint guide: https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582473076






