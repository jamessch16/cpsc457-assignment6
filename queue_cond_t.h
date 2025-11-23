/*
Code for a queue for processes
*/

#include <pthread.h>

typedef struct {
    pthread_cond_t data;
    node_cond_t *next;
} node_cond_t;

typedef struct {
    node_cond_t head;
    node_cond_t tail;
    int size;
} queue_cond_t;

// queue methods
queue_cond_t *queue_cond_t_create();
void queue_cond_t_destroy(queue_cond_t *queue);

int queue_cond_t_put(queue_cond_t *queue, pthread_cond_t cond);
pthread_cond_t queue_cond_t_pop(queue_cond_t *queue);
int queue_cond_t_size(queue_cond_t *queue);


// node methods
node_cond_t *node_cond_t_create(pthread_cond_t cond, node_cond_t *next);
void node_cond_t_destroy(node_cond_t *node);