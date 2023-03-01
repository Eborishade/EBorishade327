/* Public facing header file */
#include <stdbool.h>

typedef struct node_type NODE;

typedef struct list_type LIST;

// Function declarations

// Create a list
LIST *list_create();

// destroy a list
void list_destroy(LIST *list);

void list_free(LIST *list, void (*free_data)(void *data));

// Append the element at the end of the list.
void list_append(LIST *list, void *element);

// Append the element at a particular location.
// If location is beyond the end of the list, append the item at the end of the list.
// Returns the location of the new element.
unsigned int list_insert_at(LIST *list, void *element, unsigned int location);

// Remove the element at location from the list
// Returns a pointer to the element removed, null if there is no element at that location
void *list_remove_at(LIST *list, unsigned int location);

// Remove the element from the list
void list_remove(LIST *list, void *element);

// Returns the list of element pointers as an array
void *list_to_array(LIST *list);

// Returns the number of elements in the list.
unsigned int list_size(LIST *list);

// Returns true if empty, false otherwise.
bool list_is_empty(LIST *list);