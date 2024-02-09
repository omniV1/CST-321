#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_DEPOSITS 1000000
pthread_mutex_t mutex;
int depositAmount = 1;
int balance = 0;

// Thread function to deposit money into the bank
void *deposit(void *a) {
    int x, tmp;
    for (x = 0; x < MAX_DEPOSITS; x++) {
      // *** start of critical region ***
      pthread_mutex_lock(&mutex);

      // Not Thread Safe
      // Copy the balance to a local variable, add $1 to the balance and
      // save the balance in a global variable
        tmp = balance;
        tmp = tmp + depositAmount;
        balance = tmp;

        // *** End of Critical Region ***
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t tid1, tid2;

    // create a mutex to be used in a critical region of our code
    pthread_mutex_init(&mutex, 0);

    // Create 2 threads (users) to deposit funds into bank
    if (pthread_create(&tid1, NULL, deposit, NULL)) {
        printf("\n ERROR creating deposit thread 1");
        exit(1);
    }
    if (pthread_create(&tid2, NULL, deposit, NULL)) {
        printf("\n ERROR creating deposit thread 2");
        exit(1);
    }

    // Wait for threads (users) to finish depositing funds into bank
    if (pthread_join(tid1, NULL)) {
        printf("\n ERROR joining deposit thread 1");
        exit(1);
    }
    if (pthread_join(tid2, NULL)) {
        printf("\n ERROR joining deposit thread 2");
        exit(1);
    }

    // Check balance
    if (balance != 2 * MAX_DEPOSITS) {
        printf("\n BAD Balance: bank balance is %d and should be %d\n", balance, 2 * MAX_DEPOSITS);
    } else {
        printf("\n GOOD Balance: bank balance is %d\n", balance);
    }


    // Thread creation cleanupand mutex clean up
    pthread_mutex_destroy(&mutex);
    pthread_exit(NULL);
}
