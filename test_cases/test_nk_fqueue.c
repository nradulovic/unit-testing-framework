/*
 * test_nk_fqueue.c
 *
 *  Created on: Apr 5, 2021
 *      Author: nenad
 */

#include "../nk_test.h"
#include "test_nk_fqueue.h"
#include "generic/composite/nk_fqueue.h"

#if defined(NK_ENABLED_FQUEUE)
static void
test__construction__initializer(void)
{
#define TEST_ITEM_NO                    32
#define TEST_ITEM_TYPE                  int
    /* Allocate external storage which is to be used by fqueue */
    TEST_ITEM_TYPE items_buffer[TEST_ITEM_NO] = { 0 };
    struct my_int_queue
        NK_FQUEUE__T(TEST_ITEM_TYPE)
    my_int_queue = NK_FQUEUE__INITIALIZER(items_buffer);

    NK_TEST__EXPECT_SIZE(sizeof(TEST_ITEM_TYPE));
    NK_TEST__ACTUAL_SIZE(NK_FQUEUE__ITEM_SIZE(&my_int_queue));
    NK_TEST__EXPECT_SIZE(TEST_ITEM_NO);
    NK_TEST__ACTUAL_SIZE(nk_fqueue__item_no(&my_int_queue));
#undef TEST_ITEM_TYPE
#undef TEST_ITEM_NO
}

static void
test__construction__initialize(void)
{
#define TEST_ITEM_NO                    32
#define TEST_ITEM_TYPE                  int
    /* Allocate external storage which is to be used by fqueue */
    TEST_ITEM_TYPE items_buffer[TEST_ITEM_NO] = { 0 };
    struct my_int_queue
        NK_FQUEUE__T(TEST_ITEM_TYPE)
    my_int_queue;

    NK_FQUEUE__INITIALIZE(&my_int_queue, TEST_ITEM_NO, items_buffer);
    NK_TEST__EXPECT_SIZE(sizeof(TEST_ITEM_TYPE));
    NK_TEST__ACTUAL_SIZE(NK_FQUEUE__ITEM_SIZE(&my_int_queue));
    NK_TEST__EXPECT_SIZE(TEST_ITEM_NO);
    NK_TEST__ACTUAL_SIZE(nk_fqueue__item_no(&my_int_queue));
    for (size_t i = 0u; i < nk_fqueue__item_no(&my_int_queue); i++) {
        NK_TEST__EXPECT_INT(0);
        NK_TEST__ACTUAL_INT(items_buffer[i]);
    }
#undef TEST_ITEM_TYPE
#undef TEST_ITEM_NO
}

static void
test__put(void)
{
#define TEST_ITEM_NO                    32
#define TEST_ITEM_TYPE                  int
#define TEST_ITEM_VALUE                 5
    /* Allocate external storage which is to be used by fqueue */
    TEST_ITEM_TYPE items_buffer[TEST_ITEM_NO] = { 0 };
    struct my_int_queue
        NK_FQUEUE__T(TEST_ITEM_TYPE)
    my_int_queue;

    NK_FQUEUE__INITIALIZE(&my_int_queue, TEST_ITEM_NO, items_buffer);
    NK_FQUEUE__PUT(&my_int_queue, TEST_ITEM_VALUE);
    int test_value = NK_FQUEUE__GET(&my_int_queue);
    NK_TEST__EXPECT_INT(TEST_ITEM_VALUE);
    NK_TEST__ACTUAL_INT(test_value);
#undef TEST_ITEM_VALUE
#undef TEST_ITEM_TYPE
#undef TEST_ITEM_NO
}

static void
test__put_get__multiple(void)
{

}

void
test_nk_fqueue(void)
{
    static const struct nk_testsuite__test tests[] = {
    NK_TEST__TEST(test__construction__initializer),
    NK_TEST__TEST(test__construction__initialize),
    NK_TEST__TEST(test__put),
    NK_TEST__TEST(test__put_get__multiple),
    NK_TEST__TEST_TERMINATE() };
    nk_test__run_fixture(tests, NULL, NULL, NK_TESTSUITE__FIXTURE_NAME(none));
}
#else /* !defined(NK_ENABLED_FQUEUE) */
void
void test_nk_fqueue(void)
{
}
#endif /* defined(NK_ENABLED_FQUEUE) */
