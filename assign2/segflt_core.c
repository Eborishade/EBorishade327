/*
Goal: Write a C program named segflt_core.c that will crash and cause a 'segfault'.
 To cause the segfault, perform a memory access beyond what you have
 allocated via malloc API. Before running your program, verify the resource limit
 for core dump is non-zero by running ulimit -c. If the size is 0, set the core
 file size to unlimited using the command: ulimit -c unlimited
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h>
#include <sys/resource.h>


int main(int argc, char *argv[])
{

    struct rlimit resource_limit;
    resource_limit.rlim_cur = RLIMIT_CORE;
    resource_limit.rlim_max = RLIMIT_CORE;
    

    char *ptr = NULL;
    ptr = malloc(256 * sizeof(char));
    if (!ptr)
    {
        fprintf(stderr, "Malloc Failed: Not Alloc-ed. \n"); // fprintf->anywhere else
        exit(EXIT_FAILURE);
    }

    *(ptr + 100) = 'a'; //no seg fault
    *(ptr + 500) = 'b'; //no seg fault
    *(ptr + 5000000) = 'c'; //seg fault!!

    printf("Size of char is %ld byte(s) \n ", sizeof(char)); // printf->stdout ALWAYS
    free(ptr);
}