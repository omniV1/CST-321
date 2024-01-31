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
#include <stbool.h>


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

// Signal Handler for WAKEUP signal
void wakeupHandler(int signum) {
    // Intentionally left empty. The presence of the handler is to catch the signal.
}

// Signal Handler for SLEEP signal
void sleepHandler(int signum) {
    // Intentionally left empty.
}
/////////////////////////////////////////////////////////////////////////////////////

// Function to put an item into the buffer
void put(int item) {

     //Delcare nSig to use with sigwait
    int nSig;

    // Loop checks if the buffer is full
    while (((buffer->end + 1) % MAX) == buffer->start) {
        // Set producer as asleep
        producerAsleep = true;

        // Inform the consumer that the producer is going to sleep
        kill(otherPid, SLEEP);

        // Sleep until a signal is received
        sigwait(&sigSet, &nSig);
    }

    // Set producer as awake
    producerAsleep = false;

    // Place item into the buffer
    buffer->buffer[buffer->end] = item;

    // Move end to the next position in the circular buffer
    buffer->end = (buffer->end + 1) % MAX;

    // Increment the count of items in the buffer
    buffer->count++;
}

// Function to get an item from the buffer
int get() {
  
     // Declare nSig to use with sigwait
     int nSig;

    // Loop checks if the buffer is empty
    while (buffer->start == buffer->end) {
        // Set consumer as asleep
        consumerAsleep = true;

        // Inform the producer that the consumer is going to sleep
        kill(otherPid, WAKEUP);

        // Sleep until a signal is received
        sigwait(&sigSet, &nSig);
    }

    // Set consumer as awake
    consumerAsleep = false;

    // Retrieve item from the buffer
    int item = buffer->buffer[buffer->start];

    // Move start to the next position in the circular buffer
    buffer->start = (buffer->start + 1) % MAX;

    // Decrement the count of items in the buffer
    buffer->count--;

    // Return the retrieved item
    return item;
}

// Function to put the process to sleep until a signal is received
void sleepUntilWoken() {
    int nSig;

    // Print message indicating the process is going to sleep
    printf("Sleeping...\n");

    // Wait for a signal to wake up the process
    sigwait(&sigSet, &nSig);

    // Print message indicating the process is awake
    printf("I'm Awake!\n");
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
    int count = 0;

    // Print a starting message for the consumer process
    printf("Running Consumer process...\n");

    // Start a loop to consume 20 items
    while (count < 20) {
        // Check if the buffer is empty
        if (buffer->count == 0) {
            // If buffer is empty, print a message indicating the consumer is sleeping
            printf("Buffer is empty. Putting consumer to sleep.\n");

            // Call sleepUntilWoken to block the consumer until the WAKEUP signal is caught
            sleepUntilWoken();
        }

        // Consume data from the buffer using the get function
        int item = get();

        // Print the consumed item
        printf("Consumer eaten: %d\n", item);

        // Increment the count of consumed items
        count++;
    }

    // Exit the process after consuming 20 items
    _exit(1);
}

// Producer process
void producer() {
    // Initialize an empty signal set for the producer
    sigemptyset(&sigSet);

    // Add SLEEP signal to the signal set
    sigaddset(&sigSet, SLEEP);

    // Block the SLEEP signal until it's explicitly waited on using sigwait
    sigprocmask(SIG_BLOCK, &sigSet, NULL);

    // Counter for the number of items produced
    int count = 0;

    // Print a starting message for the producer process
    printf("Running the producer process...\n");

    // Start a loop to produce 30 items
    for (count = 0; count < 30; count++) {
        // Check if the buffer is full
        if (buffer->count == MAX) {
            // If buffer is full, print a message indicating the producer is sleeping
            printf("Buffer is full. Putting producer to sleep.\n");

            // Call sleepUntilWoken to block the producer until the SLEEP signal is caught
            sleepUntilWoken();
        }

        // Produce data to the buffer using the put function
        put(count);

        // Print the produced item
        printf("Producer produced: %d\n", count);
    }

    // Exit the process after producing 30 items
    _exit(1);
}


//////////////////////////////////////////////////////////////////////////////
/**
 * Main application entry point to demonstrate forking off a child process that will run concurrently with this process.
 *
 * @return 1 if error or 0 if OK returned to code the caller.
 */
int main(int argc, char* argv[]) {
    pid_t pid;

    // Create shared memory for the Circular Buffer
    buffer = (struct CIRCULAR_BUFFER*)mmap(0, sizeof(struct CIRCULAR_BUFFER), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    // Check if shared memory allocation was successful
    if (buffer == MAP_FAILED) {
        printf("Shared memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Initialize circular buffer values
    buffer->count = 0;
    buffer->start = 0;
    buffer->end = 0;

    // Set up signal handling for WAKEUP and SLEEP signals
    struct sigaction sa;
    sa.sa_handler = wakeupHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(WAKEUP, &sa, NULL);

    sa.sa_handler = sleepHandler;
    sigaction(SLEEP, &sa, NULL);

    // Fork to create a child process
    pid = fork();

    // Check if fork was successful
    if (pid == -1) {
        printf("Can't fork, error %d\n", errno);
        exit(EXIT_FAILURE);
    }

    // Determine if the process is the child or the parent
    if (pid == 0) {
        // Child process - runs the producer logic
        otherPid = getppid();
        producer();
    } else {
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
