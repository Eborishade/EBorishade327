#include "worker_thread_pool.h"

#include <assert.h>

#include "common.h"

static int next_thread_id = 0;
/* 
use handle_error_en() found in common.h to handle pthread errors
Example:
    int ret = 0;                                 
    if ( (ret = pthread_mutex_lock(mtx)) ){        
        handle_error_en(ret, "pthread_mutex_lock"); 
    }
*/
static pthread_t start_worker_thread(struct worker_thread_params* params);



struct worker_thread_pool* create_worker_thread_pool(
    struct request_queue* req_queue) {
    struct worker_thread_pool* thread_pool =
        malloc(sizeof(struct worker_thread_pool));
    if (!thread_pool) {
        handle_error("create_worker_thread_pool:malloc");
    }

    thread_pool->req_queue = req_queue;
    thread_pool->thread_list = NULL;
    thread_pool->last_thread = NULL;
    thread_pool->last_thread_id = 0;
    thread_pool->num_threads = 0;
    return thread_pool;
}

void add_worker_thread(struct worker_thread_pool* pool) {
    struct worker_thread_params* params =
        malloc(sizeof(struct worker_thread_params));
    if (!params) {
        handle_error("add_worker_thread:malloc:params");
    }
    struct worker_thread* worker = malloc(sizeof(struct worker_thread));
    if (!worker) {
        handle_error("add_worker_thread:malloc:worker");
    }
    struct worker_thread* new_next = pool->thread_list;
    worker->next = new_next;

    worker->thread_id = ++next_thread_id;
    pool->thread_list = worker;
    pool->num_threads += 1;
    pool->last_thread_id = worker->thread_id;

    params->req_queue = pool->req_queue;
    params->thread_id = worker->thread_id;
    worker->thread = start_worker_thread(params);
}

/**
 * @brief Create a worker thread that is joinable.
 * 
 * @param params the argument passed to the created thread. 
 * @return pthread_t 
 */
static pthread_t start_worker_thread(struct worker_thread_params* params) {
    pthread_t pthread_id = 0;
    // TODO complete this function

    int ret = 0;

    //init attr
    pthread_attr_t attr;
    if ((ret = pthread_attr_init(&attr))) {
        handle_error_en(ret, "pthread_attr_init");
    }
    //set detach state of attr to JOINABLE
    if (( ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE) )) {
        handle_error_en(ret, "pthread_attr_setdetachstate");
    }

    //passpthread_id, attr ,do_work function, and params
    if (( ret = pthread_create(&pthread_id, &attr, do_work, params) )) {
        handle_error_en(ret, "pthread_create");
    }

    // Destroy the thread attributes object
    if ((ret = pthread_attr_destroy(&attr))) {
        handle_error_en(ret, "pthread_attr_destroy");
    }

    return pthread_id;
}

/**
 * @brief Waits for each worker thread to complete. Each worker thread is freed.
 * When all threads complete the pool is freed.
 * 
 * @param pool the thread pool 
 */
void delete_worker_thread_pool(struct worker_thread_pool* pool) {
    if (!pool->thread_list) {
        return;
    }
    // TODO complete this function

    /*
    iterate over each worker, the pool->thread is head ptr for pool
    call pthread_join for every worker in thread pool
    after join returns free and move to next
    while worker!=null
    join
    next = worker->next
    free
    worker = next

    */

    struct worker_thread* worker = pool->thread_list;
    struct worker_thread* next;
    int ret = 0; 

    while (worker != NULL){
        if ((ret = pthread_join(worker->thread, NULL))) {
            handle_error_en(ret, "delete_worker_thread_pool:pthread_join");
        }
        
        next = worker->next;
        free(worker);
        worker = next;
    }
       
}
