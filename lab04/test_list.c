#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <cmocka.h>

#include "list_internal.h"

struct point {
    int x;
    int y;
};

void test_list_create(void **state) {
    LIST *list = list_create();

    assert_non_null(list);
    assert_null(list->head);
    assert_null(list->tail);

    free(list);
}

void test_list_append_when_list_is_empty(void **state) {
    // AAA arrange, act, assert
    //arrange
    LIST list;
    list.head = NULL;
    list.tail = NULL;
    struct point element;

    //act
    list_append(&list, &element);

    //assert
    assert_non_null(list.head);
    assert_non_null(list.tail);
    assert_ptr_equal(list.head, list.tail);
    assert_ptr_equal(list.head->data, &element);
    assert_null(list.head->next);
}

void test_list_append_when_list_has_one_node(void **state) {
    // arrange
    LIST list;
    NODE node;
    struct point element;
    list.head = &node;
    list.tail = &node;
    node.data = &element;
    node.next = NULL;
    struct point element2;
    
    // act
    list_append(&list, &element2);

    // assert
    assert_ptr_equal(list.head, &node);
    assert_ptr_equal(list.head->data, &element);
    assert_ptr_equal(list.head->next, list.tail);
    assert_ptr_equal(list.tail->data, &element2);
    assert_null(list.tail->next);
}


int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_list_create),
        cmocka_unit_test(test_list_append_when_list_is_empty),
        cmocka_unit_test(test_list_append_when_list_has_one_node)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}