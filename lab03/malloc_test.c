#include <stdio.h>
#include <malloc.h>
#include "malloc.h"

int main (void) {
    printf("malloc_stats test driver\n");
    printf("Malloc Stats Prealloc::\n");

    malloc_stats();

    printf("\n########################################\n");


    char* ptr = alloc_bytes(512);
    printf("\nAllocated 512 bytes %p\n", ptr);
    malloc_stats();

    char* ptr = realloc_bytes(1024);
    printf("\nReallocated 1024 bytes %p\n", ptr);
    malloc_stats();
    free(ptr);



}
