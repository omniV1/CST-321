#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include  <signal.h>
#include <sys/mman.h>
#include <err.h>
#include <errno.h>

// The Child PID if the Parent else the Parent PID if the Child
pid_t otherPid;

/****************************************************************************************************/

void  signalProducer(int signum)
{
    printf("Caught Producer Signal: %d\n",signum);
}

void  signalConsumer(int signum)
{
    printf("Caught Consumer Signal: %d\n",signum);
}

/****************************************************************************************************/

/**
 * Logic to run to the Consumer Process
 **/
void consumer()
{
    // Run the Consumer Process
    int count = 0;
    printf("Running Consumer Process.....\n");
    while(count < 20)
    {
        printf("Consumer %d\n", count);
        sleep(1);
        if(count == 2 || count == 10)
        {
            printf("Sending Producer a Signal....\n");
            kill(otherPid, SIGUSR1);
        }
        ++count;
    }
    _exit(1);
}

/**
 * Logic to run to the Producer Process
 **/
void producer()
{
    // Run the Producer Process
    int count = 0;
    printf("Running Producer Process.....\n");
    while(count < 30)
    {
        printf("Producer %d\n", count);
        sleep(1);
        if(count == 5 || count == 15)
        {
            printf("Sending Consumer a Signal....\n");
            kill(otherPid, SIGUSR2);
        }
        ++count;
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
    pid_t  pid;

    // Register some Signal Handlers
    signal(SIGUSR1, signalProducer);
    signal(SIGUSR2, signalConsumer);

    // Use fork()
    // Note: The output from both the child and the parent process will be written to standard out since they both run at the same time
    pid = fork();
    if (pid == -1)
    {
        // Error: If fork() returns -1 then an error happened (for example, number of processes reached the limit).
        printf("Can't fork, error %d\n", errno);
        exit(EXIT_FAILURE);
    }
    // OK: If fork() returns non zero then the parent process is running else child process is running
    if (pid == 0)
    {
        // Run Producer Process logic as a Child Process
        otherPid = getppid();
        producer();
    }
    else
    {
        // Run Consumer Process logic as a Parent Process
        otherPid = pid;
        consumer();
    }

    // Return OK
    return 0;
}