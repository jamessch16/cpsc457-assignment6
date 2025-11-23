#include <stdlib.h>
#include <pthread.h>
#include "queue_pthread_cond_t.h"

typedef struct {
    pthread_mutex_t *mutex;
    int count;
    queue_cond_t queue;
} Semaphore;


Semaphore *semaphore_create(int size);
void semaphore_destroy(Semaphore *semaphore);
int semaphore_wait(Semaphore *semaphore);
int semaphore_signal(Semaphore *semaphore);