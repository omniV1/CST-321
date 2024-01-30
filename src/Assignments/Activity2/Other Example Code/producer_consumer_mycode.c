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

//global variables
// The Child PID if the parent else the Parent PID if the childProcess

pid_t otherPid;

// Constants
int MAX = 100;
int WAKEUP = SIGUSR1;
int SLEEP = SIGUSR2;

// The Child PID if the Parent else the Parent PID if the Child
pid_t otherPid;

// A Signal Set
sigset_t sigSet;

// Shared Circular Buffer
struct CIRCULAR_BUFFER
{
    int count;          // Number of items in the buffer
    int start;          // Next slot to read in the buffer (sometimes called the head)
    int end;            // Next slot to write in the buffer (sometimes called the tail)
    int buffer[100];
};
struct CIRCULAR_BUFFER *buffer = NULL;

//A signal set
sigset_t sigSet;
///////////////////////////////////////////
void consumer()
{
  //Set up a Signal set
  sigemptyset(&sigSet);
  sigaddset(&sigSet,WAKEUP);
  sigprocmask(SIG_BLOCK,&sigSet,NULL);

  //Put consumer asleep
  printf("Putting consumer to sleep forever\n");
  sleepUntilWoken(); 

  //run the consumer processes
  int count = 0;
  printf("Running Consumer process......\n");
  while(count < 20);
  {
    printf("Consumer%d\n",count);
    sleep(1);
    ++count;
  }
  _exit(1);
}

void producer()
{
  //run the producer processes
  int count = 0;
  printf("Running the producer process....\n");
  while(count < 30)
  {
    printf("Producer %d\n",count);
    sleep(1);
    if(count == 5)
    {
      printf("Waking up consumer....\n");
      kill(otherPid,WAKEUP);

    }
    ++count;
  }
  _exit(1);
}
//////////////////////////////
void sleepUntilWoken()
{
  int nSig;

  //put to sleep until notified to wake up
  printf("Sleeping.....\n");
  sigwait(&sigSet,&nSig);
  printf("Im Awake!\n");

}
/**
 * Main application entry point to demonstrate forking off a child process that will run concurrently with this process.
 *
 * @return 1 if error or 0 if OK returned to code the caller.
 */
int main(int argc, char* argv[])
{
    pid_t  pid;

    pid_t ppid = (int)getpid();

    // Create shared memory for the Circular Buffer to be shared between the Parent and Child  Processes
    buffer = (struct CIRCULAR_BUFFER*)mmap(0,sizeof(buffer), PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    buffer->count = 0;
    buffer->start = 0;
    buffer->end = 0;

    // Use fork()
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
