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
    semaphore->queue = queue_cond_t_create();   // TODO Rework creation create queue at passed address, return success code
    semaphore->count = 0;

    return semaphore;
}

void semaphore_destroy(Semaphore *semaphore) {
    /*
    Releases a semaphore from memory
    */

    
    int suc;
    
    suc = pthread_mutex_destroy(semaphore->mutex);  // TODO HANDLE FAIL TO DESTROY

    suc = queue_cond_t_destroy(semaphore->queue);
    

    free(semaphore->mutex);     // TODO Might fail if pthread_mutex_destroy frees memory for us
    free(semaphore);
}


int semaphore_wait(Semaphore *semaphore) {

    int suc;

    // Acquire semaphore lock
    do {
        suc = pthread_mutex_lock(semaphore->mutex);             // TODO find better method than busy loop
    } while (suc != 0);

    while (semaphore->count <= 0) {                             // TODO this may be just if block


        // pthread_cond_t *cond = PTHREAD_COND_INITIALIZER;     // TODO initialize value

        // initialize condition variable
        pthread_cond_t *cond = malloc(sizeof(pthread_cond_t));
        suc = pthread_cond_init(cond, NULL);                    // TODO Set attributes

        // TODO continue if failed
        
        // put thread in queue and block until signaled
        suc = queue_cond_t_put(semaphore->queue, cond);         // TODO MALLOC the cond_t
        suc = pthread_cond_wait(cond, semaphore->mutex);        // TODO IMPORTANT Condition variable, wakes thread up when variable is set to 1

        // clean up condition variable
        suc = pthread_cond_destroy(cond);                       // TODO having both of these statements may be redundant.
        free(cond);
    }

    // decrement the semaphore and enter the CS
    semaphore->count--;


    do {
        suc = pthread_mutex_unlock(semaphore->mutex);           // TODO find better method than busy loop
    } while (suc != 0);

    return 0;
}

int semaphore_signal(Semaphore *semaphore) {

    int suc;

    // Acquire semaphore lock
    do {
        suc = pthread_mutex_lock(semaphore->mutex);      // TODO find better method than busy loop
    } while (suc != 0);

    semaphore->count++;

    // If queue not empty then remove a thread from queue and unblock it
    if (semaphore->queue->size > 0) {
        pthread_cond_t *cond = queue_cond_t_pop(semaphore->queue);
        suc = pthread_cond_signal(cond);

        // TODO release from memory? Or let the other thread do that
    }


    do {
        suc = pthread_mutex_unlock(semaphore->mutex);      // TODO find better method than busy loop
    } while (suc != 0);

    return 0;
}