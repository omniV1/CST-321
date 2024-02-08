// Owen Lindsey
// CST-321
// This work was done in class

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
//////////////////////////////////////////////////////
// this code does not run as intended!!!!!!!!!!!!!!!
//////////////////////////////////////////////////////

// declare global variables
// mimicking depositing money in a bank

#define MAX_DEPOSITS 1000000

int balance = 0;
int depositAmount = 1;
pthread_mutex_t mutex;


void *deposit(void *a)
{
  int x, tmp;
  for(x=0;x < MAX_DEPOSITS; ++x)
  {
  //  *** start of critical region
  pthread_mutex_lock(&mutex);

  // Not thread safe
  // Copy the balance to a local variable, add $1 to the balance. Saves the balance back in the global variables
  tmp = balance;
  tmp = tmp + depositAmount;
  balance = tmp;
  // ** end of critical region of our code
  pthread_mutex_unlock(&mutex);

  }
  return NULL;
}

int main()
{
  pthread_t tid1, tid2;


  pthread_mutex_init(&mutex, 0);

  //Create two threads
  //thread 1
  if(pthread_create(&tid1,NULL,deposit,NULL))
  {
    printf("\n Error creating deposit thread 1 ");
    exit(1);
  }
  // thread 2
  if(pthread_create(&tid2,NULL,deposit, NULL))
  {
    printf("\n Error creating deposit thread 2");
    exit(1);

  }

  //wait for users to finish depositing funds in bank
  if(pthread_join(tid1, NULL))
  {
    printf("\n Error joining deposit thread 1");
    exit(1);
  }

  if(pthread_join(tid2, NULL))
  {
    printf("\n Error joining deposit thread 2");
    exit(1);

  }
  //check balance
  if(balance < 2 * MAX_DEPOSITS)
  {
    printf("\n Bad balance: bank balance is $%d and should be $%d\n", balance, 2 * MAX_DEPOSITS);
  }
    else
  {

    printf("\n Good Balance: bank balance is $%d\n", balance);
  }
  //thread and mutex creation clean up
  pthread_mutex_destroy(&mutex);
  pthread_exit(NULL);
}
