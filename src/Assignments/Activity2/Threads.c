// Owen Lindsey
// CST-321
// This work was done in class

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void *thread1(void*a)
{
  int x;
  for(x = 0; x < 10; ++x)
  {
    //Print a message to the console and sleep for awhile
    printf("This is Thread 1.....%d\n", x);
    sleep(1);

  }
  return NULL;
}

// initializes a thread function named thread2
void *thread2(void*a)
{
  int x;
  for(x = 0; x < 10; ++x)
  {
    //Print a message to the console and sleep for awhile
    printf("This is Thread 2.....%d\n", x);
    sleep(2);

  }
  return NULL;
}

int main()
{
  pthread_t tid1, tid2;

  //Create two threads
  //thread 1
  if(pthread_create(&tid1,NULL,thread1,NULL))
  {
    printf("\n Error creating thread 1");
    exit(1);
  }
  // thread 2
  if(pthread_create(&tid2,NULL, thread2, NULL))
  {
    printf("\n Error creating thread 2");
    exit(1);

  }

  //wait for threads to finish
  if(pthread_join(tid1, NULL))
  {
    printf("\n Error joining thread 1");
    exit(1);
  }

  if(pthread_join(tid2, NULL))
  {
    printf("\n Error joining thread 2");
    exit(1);

  }
  //Thread creation cleanup
  pthread_exit(NULL); 

}
