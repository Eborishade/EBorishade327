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
    static pthread_mutex_t req_mutex = PTHREAD_MUTEX_INITIALIZER;
    static pthread_cond_t req_cond;
    static pthread_condattr_t condattr;

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

    // TODO initialize the req_cond

    // TODO destroy the condattr

    struct request_queue* req_queue =
        create_request_queue(&req_mutex, &req_cond);

    struct worker_thread_pool* thread_pool =
        create_worker_thread_pool(req_queue);

    for (int i = 0; i < thread_pool_size; ++i) {
        add_worker_thread(thread_pool);
    }

    int number = 1;
    printf("Generating %d requests...\n", request_count);
    while (number <= request_count) {
        add_request(req_queue, number++);
        nap_random();
    }

    close_request_queue(req_queue);
    delete_worker_thread_pool(thread_pool);
    delete_request_queue(req_queue);

    // TODO destroy the req_mutex

    // TODO destroy the req_cond

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
