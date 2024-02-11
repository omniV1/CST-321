#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <err.h>
#include <errno.h>

// Buffer, flags, and control variables
int MAX = 100;
struct Context
{
    int value;
    int count;
    int lower;
    int upper;
    int buffer[100];
    bool consumerWakeup;
    bool producerWakeup;
};

/****************************************************************************************************/

void sleepConsumer(Context* cx)
{
    // Put Consumer to sleep until notified to wake up
    while(cx->consumerWakeup == false)
    {
        printf("CONSUMER SLEEP\n");
        sleep(1);
    }
    cx->consumerWakeup = false;
    printf("CONSUMER AWAKE\n");
}

void wakeupConsumer(Context* cx)
{
    // Wakeup Consumer if it is sleeping
    if(cx->consumerWakeup == false)
        cx->consumerWakeup = true;
}

void getValue(Context* cx)
{
    // Get a value from the Buffer and adjust where to read from next
    int value = cx->buffer[cx->lower];
    printf("Consumer read value of %d\n", value);
    ++cx->lower;
    if(cx->lower == MAX)
        cx->lower = 0;
    --cx->count;
}

void sleepProducer(Context* cx)
{
    // Put Producer to sleep until notified to wake up
    while(cx->producerWakeup == false)
    {
        printf("PRODUCER SLEEP\n");
        sleep(1);
    }
    cx->producerWakeup = false;
    printf("PRODUCER AWAKE\n");
}

void wakeupProducer(Context* cx)
{
    // Wakeup Producer if it is sleeping
    if(cx->producerWakeup == false)
        cx->producerWakeup = true;
}

void putValue(Context* cx)
{
    // Write to next available position in the Buffer and adjust where to write next
    cx->buffer[cx->upper] = ++(cx->value);
    printf("Producer stored value of %d\n", cx->buffer[cx->upper]);
    ++cx->upper;
    if(cx->upper == MAX)
        cx->upper = 0;
    ++cx->count;
}

/****************************************************************************************************/

/**
 * Logic to run to the Consumer Process
 **/
void consumer(Context* cx)
{
    // Run the Consumer Process
    int count = 0;
    printf("Running Consumer Process.....\n");
    while(count < 200)
    {
        // If Buffer is empty then put the Consumer to sleep forever until it is awakened by Producer
        if(cx->count == 0)
        {
            sleepConsumer(cx);
        }

        // Get a value from the Buffer and adjust where to read from next
        getValue(cx);
        ++count;

        // If Buffer is full then wakeup Producer
        if(cx->count == MAX - 1)
        {
            wakeupProducer(cx);
        }
    }
    _exit(1);
}

/**
 * Logic to run to the Producer Process
 **/
void producer(Context* cx)
{
    // Run the Producer Process
    int count = 0;
    printf("Running Producer Process.....\n");
    while(count < 200)
    {
        // If Buffer is full then put the Producer to sleep forever until it is awakened by Consumer
        if(cx->count == MAX)
        {
            printf("PRODUCER MAXED\n");
            sleepProducer(cx);
        }

        // Write to next available position in the Buffer and adjust where to write next
        putValue(cx);
        ++count;

        // If Buffer was empty and now has values then wakeup the Consumer
        if(cx->count == 1)
            wakeupConsumer(cx);
    }
    _exit(1);
}

/**
 * Main application entry point to demonstrate forking off a child process that will run concurrently with this process.
 *
 * @return 1 if error or 0 if OK returned to code the caller.
 */
int main(int argc, char* argv[])
{
    // Create shared memory for our our Processes to access the buffer, flags, and control variables
    Context *cntx = (Context*)mmap(0,sizeof(Context),PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
    cntx->count = 0;
    cntx->lower = 0;
    cntx->upper = 0;
    cntx->consumerWakeup = false;
    cntx->producerWakeup = false;
    pid_t  pid;

    // Use fork()
    // Note: The output from both the child and the parent process will be written to standard out since they both run at the same time
    pid = fork();
    if (pid == -1)
    {
        // Error: If fork() returns -1 then an error happened (for example, number of processes reached the limit).
        printf("Can't fork, error %d\n", errno);
        exit(EXIT_FAILURE);
    }
    // OK: If fork() returns 1 then the parent process is running else child process is running
    if (pid != 0)
    {
        // Run Consumer Process logic
        consumer(cntx);
    }
    else
    {
        // Run Producer Process logic
        producer(cntx);
    }

    // Return OK
    return 0;
}