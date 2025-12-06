#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

#include "semaphore.h"

const int NUM_CHOPSTICKS = 5;
const int NUM_PHILOSOPHERS = 5;
const int CHOPSTICK_SEMAPHORE_SIZE = 1;

void philosopher_thread_exec() {
    int id;
    Semaphore *left;
    Semaphore *right;

    // TODO INITIALIZE

    while (true) {
        try(left, right, id);
        eat(id);
        exit(left, right, id);
        think(id);
    }
}

void try(Semaphore *left, Semaphore *right, int id) {
    /*
    Philosopher attempts to acquire chopsticks

    args:
    left: semaphore for left chopstick
    right: semaphore for right chopstick
    id: id of the attempting philosopher
    */
    
    // right chopstick
    printf("Philosopher % d wants RIGHT chopstick %d", id, right->id);
    semaphore_wait(right);
    printf("Philosopher % d picked RIGHT chopstick %d", id, right->id);

    nap(3000);

    // left chopstick
    printf("Philosopher % d wants RIGHT chopstick %d", id, right->id);
    semaphore_wait(left);
    printf("Philosopher % d picked RIGHT chopstick %d", id, right->id);

}

void exit(Semaphore *left, Semaphore *right, int id) {
    /*
    Philosopher releases chopsticks

    args:
    left: semaphore for left chopstick
    right: semaphore for right chopstick
    id: id of the releasing philosopher
    */
    semaphore_signal(right);
    semaphore_signal(left);
}

void eat(int id) {
    /*
    Prints to console that the philosopher with the passed id is eating and delay

    args
    id: the id of the eating philosopher
    */
    printf("Philosopher %d is eating!", id);
    nap(3000);
    printf("Philosopher %d is full!", id);
}


void think(int id) {
    /*
    Prints to console that the philosopher with the passed id is thinking

    args
    id: the id of the thinking philosopher
    */
    printf("Philosopher %d is thinking!", id);
}

void nap(int max_time_us) {
    usleep(rand() % max_time_us);
}


int main() {

    Semaphore *chopsticks[NUM_CHOPSTICKS];
    pthread_t philosopher_threads[NUM_PHILOSOPHERS];
    int suc;


    // create chopstick semaphores
    for (int i = 0; i < NUM_CHOPSTICKS; i++) {
        semaphore_create(CHOPSTICK_SEMAPHORE_SIZE, i);
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