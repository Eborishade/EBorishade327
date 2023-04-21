#ifndef REQUEST_QUEUE_H
#define REQUEST_QUEUE_H

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>

/* Linked list request node */
struct request {
    int number;
    struct request* next;
};

/* structure for a request queue */
struct request_queue {
    struct request* head;  // request linked list (head)
    struct request* tail;  // last request in list (tail)
    int num_requests;              // number of requests in the queue
    bool is_closed;  // true when queue no more requests will be generated
    pthread_mutex_t* mutex;    // queue's mutex
    pthread_cond_t* cond_var;  // queue's condition variable
};

extern struct request_queue* create_request_queue(pthread_mutex_t* mutex,
                                                  pthread_cond_t* cond_var);

extern void add_request(struct request_queue* req_queue, int request_num);

extern struct request* wait_for_request(struct request_queue* req_queue);

extern int get_pending_request_count(struct request_queue* req_queue);

extern void delete_request_queue(struct request_queue* req_queue);

extern void close_request_queue(struct request_queue* req_queue);

extern bool is_request_queue_closed(struct request_queue* req_queue);

#endif
