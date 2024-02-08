// Owen Lindsey
// CST-321
// This work was done in class

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// We want to keep track of a single car and who is driving it
#define MAX_CARS 1

int car = 0;
int carDriven = 1;
pthread_mutex_t mutex;

void *driving(void *a)
{
  int x, tmp;
  for(x=0;x < MAX_CARS; ++x)
  {
  //  *** start of critical region
  pthread_mutex_lock(&mutex);

  // Not thread safe
  // Copy the balance to a local variable, add $1 to the balance. Saves the balance back in the global variables
  tmp = car;
  tmp = tmp + carDriven;
  car = tmp;
  // ** end of critical region of our code
  pthread_mutex_unlock(&mutex);

  }
  return NULL;
}


// Main entry point will belong under here
