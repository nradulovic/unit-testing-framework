/*
 * test_nk_array.cpp
 *
 *  Created on: Feb 21, 2021
 *      Author: nenad
 */

#include "../nk_test.h"
#include "test_nk_array.h"
#include "generic/nk_array.h"

#if defined(NK_ENABLED_ARRAY)
static void
test__construction__initializer(void)
{
#define TEST_ITEM_NO            32
#define TEST_ITEM_TYPE          char
    /* Allocate external storage which is to be used by array */
    TEST_ITEM_TYPE items_buffer[TEST_ITEM_NO] = { 0 };
    /* Create and initialize CUT array type: structure my_char_array */
    struct my_char_array
        NK_ARRAY__T(TEST_ITEM_TYPE)
    my_array = NK_ARRAY__INITIALIZER(items_buffer);

    NK_TEST__EXPECT_SIZE(sizeof(TEST_ITEM_TYPE));
    NK_TEST__ACTUAL_SIZE(nk_array__item_size(&my_array));
    NK_TEST__EXPECT_SIZE(TEST_ITEM_NO);
    NK_TEST__ACTUAL_SIZE(nk_array__item_no(&my_array));
#undef TEST_ITEM_NO
#undef TEST_ITEM_TYPE
}

static void
test__construction__initialize(void)
{
#define TEST_ITEM_NO            32
#define TEST_ITEM_TYPE          int
    /* Allocate external storage which is to be used by array */
    TEST_ITEM_TYPE items_buffer[TEST_ITEM_NO];
    /* Create CUT array type: structure my_char_array */
    struct my_char_array
        NK_ARRAY__T(TEST_ITEM_TYPE)
    my_array;
    /* Initialize the array */
    NK_ARRAY__INITIALIZE(&my_array, TEST_ITEM_NO, items_buffer);
    NK_TEST__EXPECT_SIZE(sizeof(TEST_ITEM_TYPE));
    NK_TEST__ACTUAL_SIZE(nk_array__item_size(&my_array));
    NK_TEST__EXPECT_SIZE(TEST_ITEM_NO);
    NK_TEST__ACTUAL_SIZE(nk_array__item_no(&my_array));
    for (size_t i = 0u; i < sizeof(items_buffer) / sizeof(items_buffer[0]); i++) {
        NK_TEST__EXPECT_INT(0);
        NK_TEST__ACTUAL_INT(items_buffer[i]);
    }
#undef TEST_ITEM_NO
#undef TEST_ITEM_TYPE
}

static void
test__ref__set(void)
{
#define TEST_ITEM_NO            128
#define TEST_ITEM_TYPE          int
    /* Allocate external storage which is to be used by array */
    TEST_ITEM_TYPE items_buffer[TEST_ITEM_NO];
    /* Create our CUT array type: structure my_char_array */
    struct my_char_array
        NK_ARRAY__T(TEST_ITEM_TYPE)
    my_array;
    /* Initialize the array */
    NK_ARRAY__INITIALIZE(&my_array, TEST_ITEM_NO, items_buffer);
    /* Fill in the array with numbers */
    for (size_t i = 0u; i < nk_array__item_no(&my_array); i++) {
        *nk_array__ref(&my_array, i) = (int) i;
    }
    for (size_t i = 0u; i < nk_array__item_no(&my_array); i++) {
        NK_TEST__EXPECT_INT((int ) i);
        NK_TEST__ACTUAL_INT(items_buffer[i]);
    }
#undef TEST_ITEM_NO
#undef TEST_ITEM_TYPE
}

static void
test__ref__get(void)
{
#define TEST_ITEM_NO            128
#define TEST_ITEM_TYPE          int
    /* Allocate external storage which is to be used by array */
    TEST_ITEM_TYPE items_buffer[TEST_ITEM_NO];
    /* Create our CUT array type: structure my_char_array */
    struct my_char_array
        NK_ARRAY__T(TEST_ITEM_TYPE)
    my_array;
    /* Initialize the array */
    NK_ARRAY__INITIALIZE(&my_array, TEST_ITEM_NO, items_buffer);
    /* Fill in the array with numbers */
    for (size_t i = 0u; i < nk_array__item_no(&my_array); i++) {
        *nk_array__ref(&my_array, i) = (int) i;
    }
    for (size_t i = 0u; i < nk_array__item_no(&my_array); i++) {
        NK_TEST__EXPECT_INT((int ) i);
        NK_TEST__ACTUAL_INT(*nk_array__ref(&my_array, i));
    }
#undef TEST_ITEM_NO
#undef TEST_ITEM_TYPE
}

static void
test__ref__const_get(void)
{
#define TEST_ITEM_NO            8
#define TEST_ITEM_TYPE          int
    /* Allocate external storage which is to be used by array */
    const TEST_ITEM_TYPE items_buffer[TEST_ITEM_NO] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    /* Create our CUT array type: structure my_char_array */
    const struct my_char_array
        NK_ARRAY__T(const TEST_ITEM_TYPE)
    my_array = NK_ARRAY__INITIALIZER(items_buffer);
    /* Fill in the array with numbers */
    for (size_t i = 0u; i < nk_array__item_no(&my_array); i++) {
        NK_TEST__EXPECT_INT((int ) i);
        NK_TEST__ACTUAL_INT(*nk_array__ref(&my_array, i));
    }
#undef TEST_ITEM_NO
#undef TEST_ITEM_TYPE
}

static void
test_array_bucket__construction__initializer(void)
{
#define TEST_ITEM_NO            16
#define TEST_ITEM_TYPE          int
    /* Create our CUT array type: structure my_int_array */
    struct my_int_array
        NK_ARRAY__BUCKET_T(TEST_ITEM_TYPE, TEST_ITEM_NO)
    my_array = NK_ARRAY__BUCKET_INITIALIZER(&my_array);

    NK_TEST__EXPECT_SIZE(sizeof(TEST_ITEM_TYPE));
    NK_TEST__ACTUAL_SIZE(nk_array__item_size(NK_ARRAY(&my_array)));
    NK_TEST__EXPECT_SIZE(TEST_ITEM_NO);
    NK_TEST__ACTUAL_SIZE(nk_array__item_no(NK_ARRAY(&my_array)));
#undef TEST_ITEM_NO
#undef TEST_ITEM_TYPE
}

static void
test_array_bucket__construction__initialize(void)
{
#define TEST_ITEM_NO            16
#define TEST_ITEM_TYPE          char *
    struct my_ptr_array
        NK_ARRAY__BUCKET_T(TEST_ITEM_TYPE, TEST_ITEM_NO)
    my_array;
    NK_ARRAY__BUCKET_INITIALIZE(&my_array);
    NK_TEST__EXPECT_SIZE(sizeof(TEST_ITEM_TYPE));
    NK_TEST__ACTUAL_SIZE(nk_array__item_size(NK_ARRAY(&my_array)));
    NK_TEST__EXPECT_SIZE(TEST_ITEM_NO);
    NK_TEST__ACTUAL_SIZE(nk_array__item_no(NK_ARRAY(&my_array)));
#undef TEST_ITEM_NO
#undef TEST_ITEM_TYPE
}

static void
test_array_bucket__ref__set_get(void)
{
#define TEST_ITEM_NO            128
#define TEST_ITEM_TYPE          int
    /* Create our CUT array type: structure my_char_array */
    struct my_char_array
        NK_ARRAY__BUCKET_T(TEST_ITEM_TYPE, TEST_ITEM_NO)
    my_array;
    /* Initialize the array */
    NK_ARRAY__BUCKET_INITIALIZE(&my_array);
    /* Fill in the array with numbers */
    for (size_t i = 0u; i < nk_array__item_no(NK_ARRAY(&my_array)); i++) {
        *nk_array__ref(NK_ARRAY(&my_array), i) = (int) i;
    }
    for (size_t i = 0u; i < nk_array__item_no(NK_ARRAY(&my_array)); i++) {
        NK_TEST__EXPECT_INT((int ) i);
        NK_TEST__ACTUAL_INT(*nk_array__ref(NK_ARRAY(&my_array), i));
    }
#undef TEST_ITEM_NO
#undef TEST_ITEM_TYPE
}

static void
test_array_bucket__ref__const_get(void)
{
#define TEST_ITEM_NO            8
#define TEST_ITEM_TYPE          int
    /* Create our CUT array type: structure my_char_array */
    const struct my_char_array
        NK_ARRAY__BUCKET_T(const TEST_ITEM_TYPE, 8)
    my_array =
    NK_ARRAY__BUCKET_INITIALIZER_WITH(&my_array, 0, 1, 2, 3, 4, 5, 6, 7);
    /* Fill in the array with numbers */
    for (size_t i = 0u; i < nk_array__item_no(NK_ARRAY(&my_array)); i++) {
        NK_TEST__EXPECT_INT((int ) i);
        NK_TEST__ACTUAL_INT(*nk_array__ref(NK_ARRAY(&my_array), i));
    }
#undef TEST_ITEM_NO
#undef TEST_ITEM_TYPE
}

void
test_nk_array(void)
{
    static const struct nk_testsuite__test tests[] = {
    NK_TEST__TEST(test__construction__initializer),
    NK_TEST__TEST(test__construction__initialize),
    NK_TEST__TEST(test__ref__set),
    NK_TEST__TEST(test__ref__get),
    NK_TEST__TEST(test__ref__const_get),
    NK_TEST__TEST(test_array_bucket__construction__initializer),
    NK_TEST__TEST(test_array_bucket__construction__initialize),
    NK_TEST__TEST(test_array_bucket__ref__set_get),
    NK_TEST__TEST(test_array_bucket__ref__const_get),
    NK_TEST__TEST_TERMINATE() };
    nk_test__run_fixture(tests, NULL, NULL, NK_TESTSUITE__FIXTURE_NAME(none));
}
#else /* !defined(NK_ENABLED_ARRAY) */
void
test_nk_array(void)
{
}
#endif /* defined(NK_ENABLED_ARRAY) */
