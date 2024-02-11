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
#### Synchronized W mutex Version Key Parts:
```c

```


## Synchronized: 

![sync](https://github.com/omniV1/CST-321/blob/main/src/Assignments/Topic2/mutex_sema/screenshots/lemonade_mutex_sync.png) 

- the console output shows each kid accessing the refrigerator one at a time, and serving lemonade only when cups are available. This would be achieved by locking access to the refrigerator with a mutex. 


--- 
# Resources 

- Barnes, R. (2020). Mutex vs Semaphore. tutorialspoint: https://www.tutorialspoint.com/mutex-vs-semaphore

- Frasier, B. (2015). Mutex Synchronization in Linux with Pthreads. Youtube: https://www.youtube.com/watch?v=GXXE42bkqQk 

- Kadam, P. (2024). Multithreading in c . geeksforgeeks: https://www.geeksforgeeks.org/multithreading-in-c/

- Reha, M. (2024). Activity 2 Assignment guide: hhttps://halo.gcu.edu/resource/5d85b77c-19f5-4266-ac1c-ceb57a98052a

- Reha, M. (2024). Topic 2 Powerpoint guide: https://padlet.com/mark_reha/cst-321-hbq3dgqav9oah80v/wish/1582473076






