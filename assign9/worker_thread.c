#include "worker_thread.h"

#include <string.h>

#include "common.h"
#include "request_queue.h"

#define UNUSED (void)
#define PRIME_COUNT 10000

static bool is_prime(int n);
static void process_request(struct request* request, int thread_id, int rf);

/*
 * Processes one request.
 */
static void process_request(struct request* request, int thread_id, int rf) {
    UNUSED thread_id;
    if (request) {
        fflush(stdout);
        // Find some primes to simulate doing real work
        for (int i = 1; i < rf; ++i) {
            is_prime(i);
        }
    }
}

static bool is_prime(int n) {
    if (n == 1) return false;
    bool prime = true;
    for (int i = 2; i <= n / 2; ++i) {
        if (n % i == 0) {
            prime = false;
            break;
        }
    }
    return prime;
}

/*
 * This function continuously runs/loops.
 * if there's a request on the queue, take it off the
 * the queue and call process_request().
 *
 * if no requests are pending then wait on the condition
 * variable until a request arrives.
 *
 * Exit the thread when the request queue is closed.
 */
void* do_work(void* worker_thread_params) {
    struct worker_thread_params* params =
        (struct worker_thread_params*)worker_thread_params;
    int r = random() % PRIME_COUNT;
    fprintf(stderr, "thread-%d starting [r=%d]\n", params->thread_id, r);

    int req_processed_count = 0;
    bool done = false;
    struct request* req = NULL;
    do {
        req = wait_for_request(params->req_queue);
        if (req) {
            process_request(req, params->thread_id, r);
#ifdef DEBUG
            fprintf(stderr, "thread-%d processed request number: [%u]\n",
                    params->thread_id, req->number);
#endif
            free(req);
            req_processed_count++;
            if (req_processed_count % 10 == 0) {
                printf("thread-%d processed %d requests.\n", params->thread_id, req_processed_count);
            }
        } else {
            done = true;
        }
    } while(!done);

    fprintf(stderr, "thread-%d exiting. Processed %d requests.\n", params->thread_id, req_processed_count);
    free(params);
    pthread_exit((void*)0);
}