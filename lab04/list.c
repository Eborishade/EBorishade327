#include "list_internal.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

LIST *list_create(){
    LIST *new_list = malloc(sizeof(LIST));
    if (!new_list) {
        perror("list_create");
        exit(EXIT_FAILURE);
    }
    new_list->head = NULL;
    new_list->tail = NULL;
    
    return new_list;
}

void list_append(LIST *list, void *element) {
    if (list->head == NULL && list->tail == NULL) {
        NODE *new_node = malloc(sizeof(NODE));
        if (!new_node) {
            perror("list_append");
            exit(EXIT_FAILURE);
        }
        new_node->data = element;
        new_node->next = NULL; 
        list->head = new_node;
        list->tail = new_node;
    }

    
}