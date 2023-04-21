#include "worker_thread_pool.h"

#include <assert.h>

#include "common.h"

static int next_thread_id = 0;
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
    //pthread create, returns pthread id.

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
}
