#include "request_queue.h"

#include <assert.h>

#include "common.h"

/**
 * @brief Create a request queue object and associates it with the given mutex
 * and condition variable.
 * 
 * @param p_mutex the mutex for accessing the request queue
 * @param p_cond_var the condition variable for notifying threads 
 * @return struct request_queue* 
 */
struct request_queue* create_request_queue(pthread_mutex_t* p_mutex,
                                           pthread_cond_t* p_cond_var) {
    struct request_queue* req_queue = malloc(sizeof(struct request_queue));
    if (!req_queue) {
        handle_error("create_request_queue:malloc");
    }

    req_queue->mutex = p_mutex;
    req_queue->cond_var = p_cond_var;
    req_queue->is_closed = false;
    req_queue->tail = NULL;
    req_queue->num_requests = 0;
    req_queue->head = NULL;
    return req_queue;
}

/**
 * @brief Adds a request to the tail of the linked list.
 * Notifies all worker threads that a request was added to the queue.
 * Increments the request queue's num_requests.
 * 
 * @param req_queue the request queue
 * @param request_num the request number that is assigned to the new request
 */
void add_request(struct request_queue* req_queue, int request_num) {
    // TODO dynamically allocate memory for a request object
    struct request* new_req = NULL;

    // TODO complete the code as described in the comments
    
}

/**
 * @brief Waits for a request to come into the queue, if no requests are in the queue.
 * Otherwise, it returns the oldest (head) request in the queue.
 * The function returns a request when it becomes available.
 * It returns NULL if no requests are available and the queue is closed.
 * 
 * @param req_queue a pointer to the request queue 
 * @return struct request* a pointer to the request object 
 */
struct request* wait_for_request(struct request_queue* req_queue) {
    struct request* req = NULL;
    // TODO complete this function

    return req;
}

/**
 * @brief Get the pending request count 
 * 
 * @param req_queue a pointer to the request queue
 * @return int the current pending request count
 */
int get_pending_request_count(struct request_queue* req_queue) {
    // Begin Critical Section
    LOCK_MTX(req_queue->mutex);

    int count = req_queue->num_requests;

    UNLOCK_MTX(req_queue->mutex);
    // End Critical Section
    return count;
}

void delete_request_queue(struct request_queue* req_queue) {
    close_request_queue(req_queue);
    free(req_queue);
}

/**
 * @brief Closes the request queue by setting the is_closed bool
 * attribute of the request queue to true.
 * Notifies all threads that the queue is closed.
 * 
 * @param req_queue a pointer to the request queue
 */
void close_request_queue(struct request_queue* req_queue) {
    // TODO complete this function
}

bool is_request_queue_closed(struct request_queue* req_queue) {
    // Begin Critical Section
    LOCK_MTX(req_queue->mutex);
    bool closed = req_queue->is_closed;
    UNLOCK_MTX(req_queue->mutex);
    // End Critical Section

    return closed;
}