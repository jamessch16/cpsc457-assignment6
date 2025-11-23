/*
Implements a counting Semaphore object
*/

#include <stdlib.h>
#include <pthread.h>

#include "semaphore.h"
#include "queue_cond_t.h"


Semaphore *semaphore_create(int size) {
    /*
    Constructs a Semaphore object

    args:
    size - The number of processes allowed in the CS

    returns a pointer to the constructed Semaphore
    */

    Semaphore *semaphore = (Semaphore *) malloc(sizeof(Semaphore));
    pthread_mutex_t *mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));

    semaphore->count = size;

    // TODO Check addressing, attributes
    int suc = pthread_mutex_init(mutex, NULL);  // TODO HANDLE FAIL TO CREATE

    semaphore->mutex = mutex;

    // TODO Instantiate queue

    return semaphore;
}

void semaphore_destroy(Semaphore *semaphore) {
    /*
    Releases a semaphore from memory
    */

    // TODO release queue
    
    int suc = pthread_mutex_destroy(semaphore->mutex);  // TODO HANDLE FAIL TO DESTROY
    
    free(semaphore->mutex);
    free(semaphore);
}


int semaphore_wait(Semaphore *semaphore) {

    int suc;

    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;     // TODO initialize value

    // Acquire semaphore lock
    do {
        suc = pthread_mutex_lock(semaphore->mutex);      // TODO find better method than busy loop
    } while (suc != 0);

    while (semaphore->count <= 0) {   // TODO this may be just if block

        // TOOD enque thread here

        // TODO Wait on S.queue (block the thread)
        pthread_cond_wait(NULL, semaphore->mutex);        // TODO IMPORTANT Condition variable, wakes thread up when variable is set to 1
                                                          // Implement through signal variable in Queue linked list??? That we add the process to???
    }

    semaphore->count--;


    // TODO unlock semaphore

    return 0;
}

int semaphore_signal(Semaphore *semaphore) {

    int suc;

    // Acquire semaphore lock
    do {
        suc = pthread_mutex_lock(semaphore->mutex);      // TODO find better method than busy loop
    } while (suc != 0);

    semaphore->count++;

    // TOOD If queue not empty then remove a thread from queue and unblock it


    // TODO unlock semaphore

    return 0;
}