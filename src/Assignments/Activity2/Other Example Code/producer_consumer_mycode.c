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
void sleepAndWait(const char* processName) 
{
    int sig;
    printf("%s is going to sleep...\n", processName); 
 
    // Wait for the WAKEUP signal to be delivered
    sigwait(&sigSet, &sig);
 
    printf("%s is awake!\n", processName); 
}

// Function to put the process to sleep until a signal is received
void sleepUntilWoken(const char* processName) 
{
    int nSig;

    printf("%s is going to sleep...\n", processName); 

    // Wait for a signal to wake up the process
    sigwait(&sigSet, &nSig);
 
    printf("%s is awake!\n", processName);
}
/////////////////////////////////////////////////////////////////////////////////////

// Gets a value from the shared buffer
int getValue(struct CIRCULAR_BUFFER* buffer) 
{
    // Critical section to get a value from the buffer
    int value = buffer->buffer[buffer->start];
    buffer->start = (buffer->start + 1) % MAX;
    buffer->count--;
    return value;
}

// Puts a value in the shared buffer
void putValue(struct CIRCULAR_BUFFER* buffer, int value) 
{
    // Critical section to put a value in the buffer
    buffer->buffer[buffer->end] = value;
    buffer->end = (buffer->end + 1) % MAX;
    buffer->count++;
}

////////////////////////////////////////////////////////////////////////////////////

// Consumer process
void consumer() 
{
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

    sleep(2);
   

    // Start a loop to consume items
   while (consumedCount < expectedCount) 
   {
    if (buffer->count == 0) {
        // Buffer is empty, wait for the producer to add items
        sleepUntilWoken("Consumer");
    } else {
        int value = getValue(buffer);
        printf("Consumer ate: %d\n", value);

        if (buffer->count == MAX - 1) 
        {
            // If the buffer was full, wake up the producer
            sleepAndWait("Producer");
        }
        consumedCount++;
    }
}

    _exit(1);
}


// Producer process
void producer() 
{
    // Initialize an empty signal set
    sigemptyset(&sigSet);

    // Add SLEEP signal to the signal set
    sigaddset(&sigSet, SLEEP);

    // Block the SLEEP signal until it's explicitly waited on using sigwait
    sigprocmask(SIG_BLOCK, &sigSet, NULL);

    // Print a starting message for the producer process
    printf("Running the Producer process...\n");

    // Counter for the number of items produced
    int producedCount = 0;

    // Start a loop to produce 30 items
   while (producedCount < 30) 
   {
    if (buffer->count == MAX)
    {
        // If buffer is full, print a message indicating the producer is sleeping
        sleepUntilWoken("Producer");
    } 
    else 
    {
        putValue(buffer, producedCount);
     
        printf("Producer created: %d\n", producedCount);
     
        producedCount++;

        if (buffer->count == 1) 
        {
            // If the buffer was empty and items have been produced, wake up the consumer
            sleepAndWait("Consumer");
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
