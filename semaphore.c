/*
Implements a counting Semaphore object
*/

#include <stdlib.h>
#include <pthread.h>

typedef struct {

    int count;
    pthread_mutex_t mutex; 
} Semaphore;


// TODO look into restricted pointers for private attrivutes


Semaphore *create_semaphore(int size) {
    /*
    Constructs a Semaphore object

    args:
    size - The number of processes allowed in the CS

    returns a pointer to the constructed Semaphore
    */

    Semaphore *semaphore = (Semaphore *) malloc(sizeof(Semaphore));

    semaphore->count = size;

    // TODO Check addressing, attributes
    int suc = pthread_mutex_init(&(semaphore->mutex), NULL);  // TODO HANDLE FAIL TO CREATE


    // TODO Instantiate queue

    return semaphore;
}

void destroy_semaphore(Semaphore *semaphore) {
    /*
    Releases a semaphore from memory
    */

    // TODO release queue

    int suc = pthread_mutex_destroy(&(semaphore->mutex));  // TODO HANDLE FAIL TO DESTROY

    free(semaphore);
}


int wait(Semaphore *semaphore) {


    int suc = pthread_mutex_lock(&(semaphore->mutex));   // TODO HANDLE FAIL TO LOCK

    if (semaphore->count <= 0) {
        // TODO Wait on S.queue (block the thread)
        pthread_cond_wait();
    }

    semaphore->count--;


    // TODO unlock semaphore

    return 0;
}

int signal(Semaphore *semaphore) {

    // TOOD LOCK THE SEMAPHORE

    semaphore->count++;

    // TOOD If queue not empty then remove a thread from queue and unblock it


    // TODO unlock semaphore

    return 0;
}

// Methods wait, signal