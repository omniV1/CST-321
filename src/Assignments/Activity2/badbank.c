#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_DEPOSITS 1000000

int balance = 0;

// Thread function to deposit money into the bank
void *deposit(void *arg) {
    int i, tmp;
    for (i = 0; i < MAX_DEPOSITS; i++) {
        tmp = balance;
        tmp = tmp + 1;
        balance = tmp;
    }
    return NULL;
}

int main() {
    pthread_t tid1, tid2;

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

    // Thread creation cleanup
    pthread_exit(NULL);
}
