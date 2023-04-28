#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <pthread.h>
#include <stdio.h>

#include "common.h"
#include "request_queue.h"
#include "worker_thread_pool.h"

static void nap_random();

int main(int argc, char* argv[]) {
    /* 
    use handle_error_en() found in common.h to handle pthread errors
    Example:
        int ret = 0;                                 
        if ( (ret = pthread_mutex_lock(mtx)) ){        
            handle_error_en(ret, "pthread_mutex_lock"); 
        }
    */

    // *** begin constructors ***
    static pthread_mutex_t req_mutex = PTHREAD_MUTEX_INITIALIZER;
    static pthread_cond_t req_cond; 
    static pthread_condattr_t condattr;
    int ret = 0;
    int thread_pool_size = 0;
    int request_count = 0;
    if (argc < 3) {
        printf("Usage: %s <thread_pool_size> <request_count>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    thread_pool_size = atoi(argv[1]);
    request_count = atoi(argv[2]);

    // seed random number to vary results between program executions
    srand(time(0));
    srandom(time(0));

    // TODO initialize the condattr
    if ((ret = pthread_condattr_init(&condattr)))
        handle_error_en(ret, "pthread_condattr_init");

    // TODO initialize the req_cond
    if ((ret = pthread_cond_init(&req_cond, &condattr)))
        handle_error_en(ret, "pthread_cond_init");

    // TODO destroy the condattr
    if ((ret = pthread_condattr_destroy(&condattr)))
        handle_error_en(ret, "pthread_condattr_destroy");

    struct request_queue* req_queue =
        create_request_queue(&req_mutex, &req_cond);

    struct worker_thread_pool* thread_pool =
        create_worker_thread_pool(req_queue);


    // *** end constructors ***


    for (int i = 1; i <= thread_pool_size; ++i) {
        //printf("Spawning worker thread-%d\n", i);
        add_worker_thread(thread_pool);
        //printf("Successfully spawned worker thread-%d :: standby...\n", i);
    }

    int number = 1;
    printf("Generating %d requests...\n", request_count);
    while (number <= request_count) {
        add_request(req_queue, number++);
        nap_random();
    }

    //destructors
    close_request_queue(req_queue);
    delete_worker_thread_pool(thread_pool);
    delete_request_queue(req_queue);

    // TODO destroy the req_mutex
    if ((ret = pthread_mutex_destroy(&req_mutex)))
        handle_error_en(ret, "pthread_mutex_destroy");

    // TODO destroy the req_cond
    if ((ret = pthread_cond_destroy(&req_cond)))
        handle_error_en(ret, "pthread_cond_destroy");

    pthread_exit((void*)0);
    exit(EXIT_SUCCESS);
}

static void nap_random() {
    struct timespec sleep_time;
    sleep_time.tv_sec = 0;
    // Generate a value between 0 and 1 second
    // 1,000,000,000 ns = 1000 milliseconds
    sleep_time.tv_nsec = rand() % (1000000000L / 10L);
#ifdef DEBUG_MAIN
    // 1,000,000 ns = 1 ms
    fprintf(stderr, "main: sleeping for %ld nanoseconds (%ld milliseconds).\n",
            sleep_time.tv_nsec, sleep_time.tv_nsec / 1000000L);
#endif
    nanosleep(&sleep_time, NULL);
}
