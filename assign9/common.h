#ifndef COMMON_H
#define COMMON_H

#include <errno.h>
#include <stdlib.h>

// man pthread_create
#define handle_error_en(en, msg) \
    do {                         \
        errno = en;              \
        perror(msg);             \
        exit(EXIT_FAILURE);      \
    } while (0)

#define handle_error(msg)   \
    do {                    \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

#define LOCK_MTX(mtx)                                \
    do {                                             \
        int ret = 0;                                 \
        if ((ret = pthread_mutex_lock(mtx)))         \
            handle_error_en(ret, "pthread_mutex_lock"); \
    } while (0)

#define UNLOCK_MTX(mtx)                                \
    do {                                               \
        int ret = 0;                                  \
        if ((ret = pthread_mutex_unlock(mtx)))        \
            handle_error_en(ret, "pthread_mutex_unlock"); \
    } while (0)

#endif