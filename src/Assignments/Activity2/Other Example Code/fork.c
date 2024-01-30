#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

/**
 * Logic to run to simulare a Parent Process
 **/
void childProcess()
{
   	// Child process: Simple example where we count up to 10 and sleep for a second between each count
    for (int x=0;x < 10;++x)
    {
        printf("Child Process: %d\n", x);
         sleep(1);
    }
    
    // Exit the Child Process (use _exit() and NOT exit()
    _exit(0);
}

/**
 * Logic to run to simulare a Parent Process
 **/
void parentProcess()
{
	// Parent process: Simple example where we count up to 10 and sleep for 2 seconds between each count
    for (int y=0;y < 10;++y)
    {
    	printf("Parent Process: %d\n", y);
        sleep(2);
    }
    
    // Exit the Child Process (use _exit() and NOT exit()
    _exit(0);
}

/**
 * Main application entry point to demonstrate forking off a child process that will run concurrently with this process.
 *
 * @return 1 if error or 0 if OK returned to code the caller.
 */
int main(int argc, char* argv[])
{
   	pid_t  pid;

	// Use fork()
	// Note: The output from both the child and the parent process will be written to standard out since they both run at the same time
   	pid = fork();
   	if (pid == -1)
   	{   
      	// Error: If fork() returns -1 then an error happened (for example, number of processes reached the limit).
      	fprintf(stderr, "can't fork, error %d\n", errno);
      	exit(EXIT_FAILURE);
   	}
	// OK: If fork() returns 0 then the child process is running
   	if (pid == 0)
   	{	
   		// Run Child Process logic
   		childProcess(); 
   	}
   	else
   	{
   		// Run Parent Process logic
   		parentProcess(); 
   	}
   
   // Return OK
   return 0;
}