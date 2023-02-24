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

void list_append(LIST *list, void *element){
     NODE *new_node = malloc(sizeof(NODE));
     new_node = element;
     
        if (!new_node){
            perror("list_append");
            exit(EXIT_FAILURE);
        }

    if (list->head == NULL && list->tail == NULL){ //list empty: head=tail=element
        list->head = *new_node;
        list->tail = list->head;
    }

    if (list>head != NULL){//list already has element: tail = element
        list->tail->next = *new_node;
        list->tail = *new_node;
    }
    

}