#ifndef LIST_INTERNAL_H
#define LIST_INTERNAL_H
#include "list.h"
struct node_type {
    void *data;
    NODE *next;
};

struct list_type {
    NODE *head;
    NODE *tail;
};
#endif
