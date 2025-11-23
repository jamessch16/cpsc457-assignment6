#include <stdlib.h>
#include "queue_cond_t.h"


// queue constructor
queue_cond_t *queue_cond_t_create() {
    queue_cond_t *queue = (queue_cond_t *) malloc(sizeof(queue_cond_t));

    // TODO initialize values
}

void queue_cond_t_destroy(queue_cond_t *queue) {
    
    // TODO FREE OBJECT ATTRIBUTESHERE

    // TODO HANDLE FAILURE

    free(queue);
}


// queue methods
int queue_cond_t_put(queue_cond_t *queue, pthread_cond_t cond) {

    // TODO Handle cases size = 0, size = 1, size = n

}

pthread_cond_t queue_cond_t_pop(queue_cond_t *queue) {

}

int queue_cond_t_size(queue_cond_t *queue) {
    return queue->size;
}


// node constructor
node_cond_t *node_cond_t_create(pthread_cond_t cond, node_cond_t *next) {
    /*
    Constructs a node containing a pthread_cond_t value

    args:
    cond - a pthread_cond_t value to be stored in the node
    next - a pointer to the next node in the chain

    returns:
    a pointer to the constructed node
    */
    node_cond_t *node = (node_cond_t *) malloc(sizeof(node_cond_t));

    node->data = cond;
    node->next = next;

    return node;
}

void node_cond_t_destroy(node_cond_t *node) {
    /*
    Destructs the node object passed

    args:
    node - A pointer to the node to be destructed
    */
    free(node);
}