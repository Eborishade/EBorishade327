#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <cmocka.h>
#include <assert.h>

#include "list_internal.h"

// prevents compiler warning about unused parameters
#define UNUSED(x) (void)(x)

// The real (not mocked) free function.
// Call this function if you do a malloc in a
// a unit test function.
void __real_free(void *ptr);

void __wrap_free(void *ptr);

/**
 * @brief Mock the free() function during unit testing.
 * You need to link with the following options for the 
 * __wrap_free() function to be called instead of the free()
 * function: -Wl,--wrap=free 
 * @param ptr The pointer to memory to be freed.
 */
void __wrap_free(void *ptr) {
    // This enables checking that the argument passed to the free
    // function is the argument you expected to be passed.
    check_expected_ptr(ptr);
}

// This struct used as the data to store in the linked list.
typedef struct {
    int x;
    int y;
} DATA;

// Linked list nodes and data used for testing.
// More nodes and data can be added if necessary.
LIST list;
NODE node0, node1, node2, node3;
NODE *const nodes[] = {&node0, &node1, &node2, &node3};
DATA data0, data1, data2, data3;
DATA *const elements[] = {&data0, &data1, &data2, &data3};

/**
 * @brief Resets the linked list test data.
 */
void reset_list() {
    list.head = NULL;
    list.tail = NULL;
    for (unsigned long i = 0; i < sizeof(nodes) / sizeof(nodes[0]); ++i) {
        nodes[i]->data = NULL;
        nodes[i]->next = NULL;
    }
}

/**
 * Setup the linked list test data. The node_count
 * is the number of nodes to add to the list. Each node
 * points to a data element.
 */
void setup_list(int node_count) {
    reset_list();
    if (node_count) {
        list.head = nodes[0];
        list.tail = nodes[0];
        nodes[0]->data = elements[0];
        nodes[0]->next = NULL;
        for (int i = 1; i < node_count; ++i) {
            nodes[i - 1]->next = nodes[i];
            nodes[i]->data = elements[i];
        }
        list.tail = nodes[node_count - 1];
    }
}

void test_list_create(void **state) {
    UNUSED(state);
    LIST *list = list_create();

    assert_non_null(list);
    assert_null(list->head);
    assert_null(list->tail);

    __real_free(list);
}


//APPEND tests

void test_list_append_when_list_is_empty(void **state) {
    UNUSED(state);
    // arrange
    reset_list();

    // act
    list_append(&list, elements[0]);

    // assert
    assert_non_null(list.head);
    assert_non_null(list.tail);
    assert_ptr_equal(list.head, list.tail);
    assert_ptr_equal(list.head->data, elements[0]);
    assert_null(list.head->next);
}

void test_list_append_when_list_has_one_node(void **state) {
    UNUSED(state);
    setup_list(1);
    DATA new_data;

    list_append(&list, &new_data);

    assert_ptr_equal(list.head, nodes[0]);
    assert_ptr_equal(list.head->data, elements[0]);
    assert_ptr_equal(list.head->next, list.tail);
    assert_ptr_equal(list.tail->data, &new_data);
    assert_null(list.tail->next);
}


void test_list_insert_at_when_list_is_empty(void **state) {
    UNUSED(state);
    reset_list();

    list_insert_at(&list, elements[0], 1);

    assert_non_null(list.head);
    assert_non_null(list.tail);
    assert_ptr_equal(list.head, list.tail);
    assert_ptr_equal(list.head->data, elements[0]);
    assert_null(list.head->next);
}


void test_list_insert_at_when_list_has_one_node(void **state) {
    UNUSED(state);
    setup_list(1);
    DATA new_data;

    list_insert_at(&list, &new_data, 1);

    assert_ptr_equal(list.head, nodes[0]);
    assert_ptr_equal(list.head->data, elements[0]);
    assert_ptr_equal(list.head->next, list.tail);
    assert_ptr_equal(list.tail->data, &new_data);
    assert_null(list.tail->next);
}

//SIZE test

void test_list_size_when_list_is_empty(void **state) {
    UNUSED(state);
    reset_list();

    int res = list_size(&list);

    assert(res == 0);
}

void test_list_size_when_list_is_not_empty(void **state) {
    UNUSED(state);
    int size = 3;
    setup_list(3);

    int res = list_size(&list);

    assert(res == size);
}


//IS_EMPTY test
void test_list_is_empty_when_list_is_empty(void **state) {
    UNUSED(state);
    setup_list(1);
    reset_list();

    bool res = list_is_empty(&list);

    assert_null(list.head);
    assert_null(list.tail);
    assert(res);
}

void test_list_is_empty_when_list_is_not_empty(void **state) {
    UNUSED(state);
    setup_list(4);

    bool res = list_is_empty(&list);

    assert_non_null(list.head);
    assert_non_null(list.tail);
    assert(res == false);
}


//REMOVE tests

void test_list_remove_when_list_has_one_node(void **state) {
    UNUSED(state);
    setup_list(1);

    expect_value(__wrap_free, ptr, nodes[0]);
    list_remove(&list, elements[0]);

    assert_null(list.head);
    assert_null(list.tail);
}


void test_list_remove_when_list_has_more_than_1_node(void **state) {
    UNUSED(state);
    setup_list(3);

    expect_value(__wrap_free, ptr, nodes[1]);
    list_remove(&list, elements[1]);

    assert_ptr_equal(list.head, nodes[0]);
    assert_ptr_equal(list.tail, nodes[2]);
}


void test_list_remove_at_when_list_has_one_node(void **state) {
    UNUSED(state);
    setup_list(1);

    expect_value(__wrap_free, ptr, nodes[0]);
    void *el_removed = list_remove_at(&list, 0);

    assert_ptr_equal(el_removed, elements[0]);
    assert_null(list.head);
    assert_null(list.tail);
}


void test_list_remove_at_when_list_has_more_than_1_node(void **state) {
    UNUSED(state);
    setup_list(3);

    expect_value(__wrap_free, ptr, nodes[1]);
    void *el_removed = list_remove_at(&list, 1);

    assert_ptr_equal(el_removed, elements[1]);
    assert_ptr_equal(list.head, nodes[0]);
    assert_ptr_equal(list.tail, nodes[2]);
}


// Destroy Test

void test_list_destroy(void **state) {
    UNUSED(state);
    setup_list(2);

    expect_value(__wrap_free, ptr, nodes[0]);
    expect_value(__wrap_free, ptr, nodes[1]);
    expect_value(__wrap_free, ptr, &list);

    list_destroy(&list);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_list_create),
        cmocka_unit_test(test_list_append_when_list_is_empty),
        cmocka_unit_test(test_list_append_when_list_has_one_node),
        cmocka_unit_test(test_list_insert_at_when_list_is_empty),
        cmocka_unit_test(test_list_insert_at_when_list_has_one_node),
        cmocka_unit_test(test_list_remove_when_list_has_one_node),
        cmocka_unit_test(test_list_remove_when_list_has_more_than_1_node),
        cmocka_unit_test(test_list_remove_at_when_list_has_one_node),
        cmocka_unit_test(test_list_remove_at_when_list_has_more_than_1_node),
        cmocka_unit_test(test_list_size_when_list_is_not_empty),
        cmocka_unit_test(test_list_size_when_list_is_empty),
        cmocka_unit_test(test_list_is_empty_when_list_is_empty),
        cmocka_unit_test(test_list_is_empty_when_list_is_not_empty),
        cmocka_unit_test(test_list_destroy)};
    return cmocka_run_group_tests(tests, NULL, NULL);
}