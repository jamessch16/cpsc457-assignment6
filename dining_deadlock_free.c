#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#include "semaphore.h"

const int NUM_CHOPSTICKS = 5;
const int NUM_PHILOSOPHERS = 5;
const int CHOPSTICK_SEMAPHORE_SIZE = 1;

void philosopher_thread_exec() {

}

void try() {

}

void exit() {

}

void eat() {

}

void think() {

}

void nap(int time) {

}

int main() {

    Semaphore *chopsticks[NUM_CHOPSTICKS];
    pthread_t philosopher_threads[NUM_PHILOSOPHERS];
    int suc;


    // create chopstick semaphores
    for (int i = 0; i < NUM_CHOPSTICKS; i++) {
        semaphore_create(CHOPSTICK_SEMAPHORE_SIZE);
    }

    // create new threads for each philosopher
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        suc = pthread_create(&philosopher_threads[i], NULL, philosopher_thread_exec, NULL);
        if (suc == false) {
            i--;
        }
    }

    // wait on philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosopher_threads[i]);        
    }

    // clean up resources
    for (int i = 0; i < NUM_CHOPSTICKS; i++) {
        semaphore_destroy(chopsticks[i]);
    }

    return 0;
}