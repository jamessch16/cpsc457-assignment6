/*
Code for a queue for processes
*/

#include <pthread.h>

typedef struct {
    pthread_cond_t data;
    node_pthread_cond_t next;
} node_pthread_cond_t;

typedef struct {
    node_pthread_cond_t head;
    node_pthread_cond_t tail;
    int size;
} queue_pthread_cond_t;

