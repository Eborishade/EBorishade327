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
    NODE *new_node = malloc(sizeof(NODE));
    if (!new_node) {
        perror("list_append");
        exit(EXIT_FAILURE);
    }
    new_node->data = element;

    //if list is null
    if (list->head == list->tail && list->head == NULL) {
        new_node->next = NULL; 

        list->head = new_node;
        list->tail = new_node;
    }
    //if list has one or more element(s)
    else {
        list->tail->next = new_node; 
        list->tail = new_node;
    }
}


// Append the element at a particular location.
// If location is beyond the end of the list, append the item at the end of the list.
// Returns the location of the new element.
unsigned int list_insert_at(LIST *list, void *element, unsigned int location){
    NODE *prev = NULL;
    NODE *current = list->head;
    unsigned int i = 0;

    //find location
    while (current != NULL && i < location) {
        prev = current;
        current = current->next;
        i++;
    }

    //create new node
    NODE *new_node = malloc(sizeof(NODE));
    if (!new_node) {
        perror("list_insert_at");
        exit(EXIT_FAILURE);
    }
    new_node->data = element;
    new_node->next = current;

    //INSERT

    //if empty
    if (prev == NULL) {
        list->head = new_node;
    } else {
        prev->next = new_node;
    }

    //if last element
    if (current == NULL) {
        list->tail = new_node;
    }

    return i;
}


// Remove the element from the list
void list_remove(LIST *list, void *element){
    NODE *prev = NULL;
    NODE *current = list->head;

    //search using data
    while (current != NULL && current->data != element) {
        prev = current;
        current = current->next;
    }

    //if found:
    if (current != NULL) {

        //if head
        if (prev == NULL) {
            list->head = current->next;
        } else {
            prev->next = current->next;
        }

        //if tail
        if (current->next == NULL) {
            list->tail = prev;
        }

        //finally, remove
        free(current);

    } //else do nothing
}


// Remove the element at location from the list
// Returns a pointer to the element removed, null if there is no element at that location
void *list_remove_at(LIST *list, unsigned int location){
    //for [location] node = next. if NULL break, do nothing?
    NODE *prev = NULL;
    NODE *current = list->head;
    unsigned int i = 0;

    //find location
    while (current != NULL && i < location) {
        prev = current;
        current = current->next;
        i++;
    }

    //if not found
    if (current == NULL) {
        return NULL;
    }

    //UNLINK

    //if removing first element
    if (prev == NULL) {
        list->head = current->next;
    } else {
        prev->next = current->next;
    }

    //if removing last element
    if (current->next == NULL) {
        list->tail = prev;
    }

    //get data & return
    void *data = current->data;
    free(current);

    return data;
}


// Returns the list of element pointers as an array
void *list_to_array(LIST *list){
    int size = list_size(list);
    void **arr = malloc(sizeof(void*) * size);
    if(!arr){
        perror("list_to_array");
        exit(EXIT_FAILURE);
    }

    NODE *node = list->head;
    int i = 0;
    while (node != NULL) {
        arr[i] = node->data;
        i++;
        node = node->next;
    }

    return arr;
}


// Returns the number of elements in the list.
unsigned int list_size(LIST *list){
    unsigned int i = 0;
    NODE *node = list->head; 
    while(node != NULL){
        i++;
        node = node->next;
    }

    return i;
}


// Returns true if empty, false otherwise.
bool list_is_empty(LIST *list){
    if (list->head == NULL && list->tail == NULL) {
        return true;
    }
    return false;
}


// destroy a list: CANNOT be called with list_free
// Deletes all nodes, then list iself. Will create memory leak if data is initialized within nodes.
void list_destroy(LIST *list){
    NODE *prev; 
    NODE *node = list->head; 

    while(node != NULL){
        prev = node;
        node = node->next;
        free(prev);
    }
    
    free(list);
}


// free list: CANNOT be called after list_destroy
// Param: List, and a function to free a node's internal data
// Deletes all data from nodes using provided function, then deletes node itself, then list
void list_free(LIST *list, void (*free_data)(void *data)){
    NODE *prev = list->head; 
    NODE *node = list->head; 

    while(node != NULL){
        prev = node;
        node = node->next;
        free_data(prev->data); 
        free(prev);
    }
    
    free(list); 
}
