#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

pthread_t thd1 = NULL;
pthread_t thd2 = NULL;
int MAX = 100;
struct Context
{
	int theProduct;
	int count;
	int lower;
	int upper;
	int buffer[100];
	bool consumerNotify;
	bool producerNotify;
}cntx;

void *consumerThd(void *arg)
{
	// Run the Consumer Thread
	struct Context* cx = (struct Context *) arg;
    printf("Running Consumer Thread.....\n");
    while(1)
    {
    	if(cx->count == 0)
    	{
    		while(cx->consumerNotify == false)
    		{ 	
 printf("CONSUMER SLEEP %d\n", cx->count); 	
   				sleep(1);
    		}
    		cx->consumerNotify = false;
    	}
 printf("CONSUMER AWAKE\n"); 	
	   	int value = cx->buffer[cx->lower];
    	printf("This is the value from the consumer %d\n", value);	
	   	++cx->lower;
	   	if(cx->lower == MAX)
	   		cx->lower = 0;
    	cx->count = cx->count - 1;
    	if(cx->count == MAX - 1)
    	{
    		if(cx->producerNotify == false)
    			cx->producerNotify = true;
    	}
    }
}

/**
 * Logic to run to the Consumer Process
 **/
void consumer(struct Context* context)
{
	// Run the Consumer Process
    printf("Running Consumer Process.....\n");
    while(1)
    {
	    if(thd2 == NULL)
    	{
    		if(pthread_create(&thd2, NULL, consumerThd, context))
    		{
        		printf("\n ERROR creating Consumer Thread");
        		exit(1);
    		}
    	}
    	else
    	{
    		sleep(1);
    	}
    }
}

void *producerThd(void *arg)
{
	// Run the Producer Thread
	struct Context* cx = (struct Context *) arg;
    printf("Running Producer Thread.....\n");
    while(1)
    {
    	if(cx->count == MAX)
    	{
			printf("PRODUCER MAXED %d\n", cx->count); 	
    		while(cx->producerNotify == false)
    		{
				printf("PRODUCER SLEEP\n"); 	
    			sleep(1);
    		}
    		cx->producerNotify = false;
    	}
    	cx->buffer[cx->upper] = ++(cx->theProduct);
     	printf("Producer stored %d\n", cx->buffer[cx->upper]);	
	   	++cx->upper;
	   	if(cx->upper == MAX)
	   		cx->upper = 0;
    	cx->count = cntx->count + 1;
    	if(cx->count == 1)
    	{
    		if(cx->consumerNotify == false)
    		{
   				cx->consumerNotify = true;
    		}
    	}	
    }
}

/**
 * Logic to run to the Producer Process
 **/
void producer(struct Context* context)
{
	// Run the Producer Process
    printf("Running Producer Process.....\n");
    while(1)
    {
    	if(thd1 == NULL)
    	{
    		if(pthread_create(&thd1, NULL, producerThd, context))
    		{
        		printf("\n ERROR creating Producer Thread");
        		exit(1);
    		}
    	}
    	else
    	{
	    	sleep(1);
    	}
    }
}

/**
 * Main application entry point to demonstrate forking off a child process that will run concurrently with this process.
 *
 * @return 1 if error or 0 if OK returned to code the caller.
 */
int main(int argc, char* argv[])
{
   	pid_t  pid;
	cntx.count = 0;
	cntx.lower = 0;
	cntx.upper = 0;
	cntx.consumerNotify = false;
	cntx.producerNotify = false;

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
   		// Run Producer Process logic
   		producer(&cntx); 
   	}
   	else
   	{
   		// Run Consumer Process logic
   		consumer(&cntx); 
   	}
   
   // Return OK
   return 0;
}