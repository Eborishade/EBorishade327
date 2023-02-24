#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <cmocka.h>
#include "list_internal.h"

struct point{
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

void test_list_append_list_is_empty(void **state){
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
}



int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_list_create),
        cmocka_unit_test(test_list_append_list_is_empty)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}