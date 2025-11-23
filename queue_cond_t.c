#include <stdlib.h>
#include <stdio.H>
#include "queue_cond_t.h"


// queue constructor
queue_cond_t *queue_cond_t_create() {
    /*
    Constructs an empty queue of pthread_cond_t values

    returns
    a pointer to the constructed queue
    */
    queue_cond_t *queue = (queue_cond_t *) malloc(sizeof(queue_cond_t));

    queue->head = NULL;
    queue->tail = NULL;
    queue->size = NULL;

    return queue;
}

int queue_cond_t_destroy(queue_cond_t *queue) {
    /*
    Destructs the queue object passed

    args:
    queue - A pointer to the queue to be destructed
    */
    


    // TODO HANDLE FAILURE



    node_cond_t *current = queue->head;
    node_cond_t *next;

    while (current != NULL) {
        
        // TODO PASS NEXT TO NEXT

        // TODO TODO


        free(current);
    }

    free(queue);
}


// queue methods
int queue_cond_t_put(queue_cond_t *queue, pthread_cond_t *cond) {
    /*
    Adds a new pthread_cond_t reference at the head of the queue

    Note: The stored reference is assumed to have been given an allocated section in memory already.
        Allocation must be performed by the calling process

    args:
    queue: the queue the reference is being put in
    *cond: reference to the condition variable being put in the queue

    returns:
    0 if successful
    1 if failed
    */


    // TODO TODO HANDLE FAIL TO CREATE NODE


    node_cond_t *new_node;

    if (queue->head == NULL) {
        // queue is empty
        new_node = node_cond_t_create(cond, NULL, NULL);

        queue->head = new_node;
        queue->tail = new_node;
        queue->size++;
    }

    else if (queue->tail == NULL) {
        // should never happen
        fprintf(stderr, "ERROR: Queue has head but no tail");
        return 1;
    }

    else {
        // put new node to head of non-empty queue
        new_node = node_cond_t_create(cond, queue->head, NULL);

        queue->head->back = new_node;

        queue->head = new_node;
        queue->size++;
    }

    return 0;
}

pthread_cond_t *queue_cond_t_pop(queue_cond_t *queue) {
    /*
    Removes a pthread_cond_t refernce from the end of the queue and returns it

    Note: we do not free any memory allocated to the stored pthread_cond_t value. It must
        be freed by the calling or enquing procedure after it has finished its use.

    args:
    queue: the queue the reference is being retrieved from

    returns:
    the reference that was removed from the queue
    */

    pthread_cond_t *return_value;
    int suc;

    if (queue->tail == NULL) {
        // empty queue. should not happen
        fprintf(stderr, "ERROR: Attempt to pop empty queue");
        return 1;
    }

    else if (queue->tail == queue->head) {
        // one memeber in queue
        return_value = queue->tail->data;

        // TODO handle failure
        suc = node_cond_t_destroy(queue->tail);

        queue->head = NULL;
        queue->tail = NULL;
        queue->size--;
    }

    else {
        // more than one in queue
        node_cond_t *to_pop = queue->tail;

        return_value = to_pop->data;

        to_pop->back->next = NULL;     // Second last in queue sets forward reference to NULL
        queue->tail = to_pop->back;

        // TODO handle failure
        suc = node_cond_t_destroy(to_pop);

        queue->size--;
    }

    return return_value;
}

int queue_cond_t_size(queue_cond_t *queue) {
    return queue->size;
}


// node constructor
node_cond_t *node_cond_t_create(pthread_cond_t *cond, node_cond_t *next, node_cond_t *back) {
    /*
    Constructs a node containing a pthread_cond_t value

    Note: The stored reference is assumed to have been given an allocated section in memory already.
        Allocation must be performed by the calling process

    args:
    cond - a pthread_cond_t value to be stored in the node
    next - a pointer to the next node in the chain
    back - a pointer to the last node in the chain

    returns:
    a pointer to the constructed node
    */
    node_cond_t *node = (node_cond_t *) malloc(sizeof(node_cond_t));

    node->data = cond;
    node->next = next;
    node->back = back;

    return node;
}

int node_cond_t_destroy(node_cond_t *node) {
    /*
    Destructs the node object passed

    Note: we do not free any memory allocated to the stored pthread_cond_t value. It must
        be freed by the procedure that enqued the value.

    args:
    node - A pointer to the node to be destructed
    */
    free(node);


    // TODO HANDLE FAILURE



}