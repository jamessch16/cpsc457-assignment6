#include <stdlib.h>
#include <pthread.h>
#include "queue_cond_t.h"

typedef struct {
    pthread_mutex_t *mutex;
    queue_cond_t *queue;
    int count;
    int id;  // optional id 
} Semaphore;


Semaphore *semaphore_create(int size, int id);
void semaphore_destroy(Semaphore *semaphore);
int semaphore_wait(Semaphore *semaphore);
int semaphore_signal(Semaphore *semaphore);