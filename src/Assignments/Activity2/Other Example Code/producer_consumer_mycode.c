// Owen Lindsey
// This was done in class
// Producer and consumer
// CST-321

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include  <signal.h>
#include <sys/mman.h>
#include <errno.h>
#include <err.h>
#include <stdbool.h>


//global variables
// The Child PID if the parent else the Parent PID if the childProcess
pid_t otherPid;

// Constants
int MAX = 100;
int WAKEUP = SIGUSR1;
int SLEEP = SIGUSR2;

// Flags to track if producer/consumer is asleep
volatile sig_atomic_t producerAsleep = false;
volatile sig_atomic_t consumerAsleep = false;

// A Signal Set
sigset_t sigSet;
 
// Shared Circular Buffer
struct CIRCULAR_BUFFER
{
// Number of items in the buffer
    int count;
// Next slot to read in the buffer (sometimes called the head)
    int start;
// Next slot to write in the buffer (sometimes called the tail)
    int end;
// The buffer array
    int buffer[100];
};
struct CIRCULAR_BUFFER *buffer = NULL;

// This method will put the current Process to sleep until it is awoken by the WAKEUP signal
void sleepAndWait() 
{
    // Define nSig 
    int nSig;
     // orepare to catch the wake up signal
    sigemptyset(&sigSet);
    sigaddset(&sigSet, WAKEUP);

    // Wait for the WAKEUP signal to be delivered
    printf("Sleeping...\n"); 
    sigwait(&sigSet, &sig);
    printf("Im awake!\n");
}

// This method will signal the Other Process to WAKEUP
void wakeupOther() {
    // Send the WAKEUP signal to the other process
    kill(otherPid, WAKEUP);
}
/////////////////////////////////////////////////////////////////////////////////////

// Gets a value from the shared buffer
int getValue(struct CIRCULAR_BUFFER* buffer) {
    // Critical section to get a value from the buffer
    int value = buffer->buffer[buffer->start];
    buffer->start = (buffer->start + 1) % MAX;
    buffer->count--;
    return value;
}

// Puts a value in the shared buffer
void putValue(struct CIRCULAR_BUFFER* buffer, int value) {
    // Critical section to put a value in the buffer
    buffer->buffer[buffer->end] = value;
    buffer->end = (buffer->end + 1) % MAX;
    buffer->count++;
}

////////////////////////////////////////////////////////////////////////////////////

// Consumer process
void consumer() {
    // Initialize an empty signal set
    sigemptyset(&sigSet);

    // Add WAKEUP signal to the signal set
    sigaddset(&sigSet, WAKEUP);

    // Block the WAKEUP signal until it's explicitly waited on using sigwait
    sigprocmask(SIG_BLOCK, &sigSet, NULL);

    // Counter for the number of items consumed
    int consumedCount = 0;

   // Give an expected count based on the amount of items the producer will add to the circular buffer 
    int expectedCount = 30; 

    // Print a starting message for the consumer process
    printf("Running Consumer process...\n");

    // adding sleep delay so producer process runs before consumer 
      sleep(1);
       
     // Start a loop to consume 20 items
    while (consumedCount < expectedCount) {
        // Check if the buffer is empty
        if (buffer->count == 0) {
            // Buffer is empty, wait for the producer to add items
            sleepAndWait();
        }  
        else
        {
            int value = getValue(buffer);
            printf("Consumer consumed: %d\n", value);

            if (buffer->count == MAX - 1) {
                wakeupOther();
            }
            consumedCount++;
        }
    }
    _exit(1);
}

// Producer process
void producer() {
    // Initialize an empty signal set
    sigemptyset(&sigSet);

    // Add SLEEP signal to the signal set
    sigaddset(&sigSet, SLEEP);

    // Block the SLEEP signal until it's explicitly waited on using sigwait
    sigprocmask(SIG_BLOCK, &sigSet, NULL);

    // Print a starting message for the producer process
    printf("Running the producer process...\n");

    // Counter for the number of items produced
    int producedCount = 0;

    // Start a loop to produce 30 items
    while (producedCount < 30) {
        // Check if the buffer is full
        if (buffer->count == MAX) {
            // If buffer is full, print a message indicating the producer is sleeping
            sleepAndWait();
        }
        else 
        {
            putValue(buffer, producedCount);
            printf("Producer produced: %d\n", producedCount);
            producedCount++;
        }
    }
    _exit(1);
}


//////////////////////////////////////////////////////////////////////////////
/**
 * Main application entry point to demonstrate forking off a child process that will run concurrently with this process.
 *
 * @return 1 if error or 0 if OK returned to code the caller.
 */
int main(int argc, char* argv[]) 
{
    pid_t pid;

    // Create shared memory for the Circular Buffer
    buffer = (struct CIRCULAR_BUFFER*)mmap(0, sizeof(struct CIRCULAR_BUFFER), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    // Check if shared memory allocation was successful
    if (buffer == MAP_FAILED) 
    {
        printf("Shared memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Initialize circular buffer values
    buffer->count = 0;
    buffer->start = 0;
    buffer->end = 0;

    // Fork to create a child process
    pid = fork();

    // Check if fork was successful
    if (pid == -1) 
    {
        printf("Can't fork, error %d\n", errno);
        exit(EXIT_FAILURE);
    }

    // Determine if the process is the child or the parent
    if (pid == 0) 
    {
        // Child process - runs the producer logic
        otherPid = getppid();
        producer();
    }
    else 
    {
        // Parent process - runs the consumer logic
        otherPid = pid;
        consumer();
    }

    // Cleanup shared memory (only reached if both processes end, which won't happen with _exit in producer/consumer)
    if (munmap(buffer, sizeof(struct CIRCULAR_BUFFER)) == -1) {
        printf("Error un-mapping shared memory\n");
        exit(EXIT_FAILURE);
    }

    // Return OK
    return 0;
}
