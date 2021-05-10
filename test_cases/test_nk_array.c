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
test__construction__initializer_0(void)
{
#define TEST_ITEM_NO            32
#define TEST_ITEM_TYPE          char
    /* Allocate external storage which is to be used by array */
    TEST_ITEM_TYPE items_buffer[TEST_ITEM_NO] = { 0 };
    /* Create and initialize CUT array type: structure my_char_array */
    struct my_char_array
        NK_ARRAY__T(TEST_ITEM_TYPE)
    my_array = NK_ARRAY__INITIALIZER(items_buffer, 0u);

    NK_TEST__EXPECT_SIZE(sizeof(TEST_ITEM_TYPE));
    NK_TEST__ACTUAL_SIZE(NK_ARRAY__ITEM_SIZE(&my_array));
    NK_TEST__EXPECT_SIZE(TEST_ITEM_NO);
    NK_TEST__ACTUAL_SIZE(my_array.item_no);
    NK_TEST__EXPECT_SIZE(0u);
    NK_TEST__ACTUAL_SIZE(my_array.length);
#undef TEST_ITEM_NO
#undef TEST_ITEM_TYPE
}

static void
test__construction__initializer_4(void)
{
#define TEST_ITEM_NO            24
#define TEST_ITEM_TYPE          unsigned int
    /* Allocate external storage which is to be used by array */
    TEST_ITEM_TYPE items_buffer[TEST_ITEM_NO] = { 0, 1, 2, 3 };
    /* Create and initialize CUT array type: structure my_char_array */
    struct my_char_array
        NK_ARRAY__T(TEST_ITEM_TYPE)
    my_array = NK_ARRAY__INITIALIZER(items_buffer, 4);

    NK_TEST__EXPECT_SIZE(sizeof(TEST_ITEM_TYPE));
    NK_TEST__ACTUAL_SIZE(NK_ARRAY__ITEM_SIZE(&my_array));
    NK_TEST__EXPECT_SIZE(TEST_ITEM_NO);
    NK_TEST__ACTUAL_SIZE(my_array.item_no);
    NK_TEST__EXPECT_SIZE(4u);
    NK_TEST__ACTUAL_SIZE(my_array.length);
    for (size_t i = 0u; i < my_array.length; i++) {
        NK_TEST__EXPECT_UINT((unsigned int) i);
        NK_TEST__ACTUAL_UINT(my_array.items[i]);
    }
#undef TEST_ITEM_NO
#undef TEST_ITEM_TYPE
}

static void
test__construction__initializer_empty(void)
{
#define TEST_ITEM_NO            24
#define TEST_ITEM_TYPE          unsigned int
    /* Allocate external storage which is to be used by array */
    TEST_ITEM_TYPE items_buffer[TEST_ITEM_NO] = { 0, 1, 2, 3 };
    /* Create and initialize CUT array type: structure my_char_array */
    struct my_char_array
        NK_ARRAY__T(TEST_ITEM_TYPE)
    my_array = NK_ARRAY__INITIALIZER_EMPTY(items_buffer);

    NK_TEST__EXPECT_SIZE(sizeof(TEST_ITEM_TYPE));
    NK_TEST__ACTUAL_SIZE(NK_ARRAY__ITEM_SIZE(&my_array));
    NK_TEST__EXPECT_SIZE(TEST_ITEM_NO);
    NK_TEST__ACTUAL_SIZE(my_array.item_no);
    NK_TEST__EXPECT_SIZE(0u);
    NK_TEST__ACTUAL_SIZE(my_array.length);
#undef TEST_ITEM_NO
#undef TEST_ITEM_TYPE
}

static void
test__construction__initialize_0(void)
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
    NK_ARRAY__INITIALIZE(&my_array, TEST_ITEM_NO, items_buffer, 0u);
    NK_TEST__EXPECT_SIZE(sizeof(TEST_ITEM_TYPE));
    NK_TEST__ACTUAL_SIZE(NK_ARRAY__ITEM_SIZE(&my_array));
    NK_TEST__EXPECT_SIZE(TEST_ITEM_NO);
    NK_TEST__ACTUAL_SIZE(my_array.item_no);
    NK_TEST__EXPECT_SIZE(0u);
    NK_TEST__ACTUAL_SIZE(my_array.length);
#undef TEST_ITEM_NO
#undef TEST_ITEM_TYPE
}

static void
test__construction__initialize_4(void)
{
#define TEST_ITEM_NO            32
#define TEST_ITEM_TYPE          int
    /* Allocate external storage which is to be used by array */
    TEST_ITEM_TYPE items_buffer[TEST_ITEM_NO] = {0, 1, 2, 3};
    /* Create CUT array type: structure my_char_array */
    struct my_char_array
        NK_ARRAY__T(TEST_ITEM_TYPE)
    my_array;
    /* Initialize the array */
    NK_ARRAY__INITIALIZE(&my_array, TEST_ITEM_NO, items_buffer, 4u);
    NK_TEST__EXPECT_SIZE(sizeof(TEST_ITEM_TYPE));
    NK_TEST__ACTUAL_SIZE(NK_ARRAY__ITEM_SIZE(&my_array));
    NK_TEST__EXPECT_SIZE(TEST_ITEM_NO);
    NK_TEST__ACTUAL_SIZE(my_array.item_no);
    NK_TEST__EXPECT_SIZE(4u);
    NK_TEST__ACTUAL_SIZE(my_array.length);
    for (size_t i = 0u; i < my_array.length; i++) {
        NK_TEST__EXPECT_INT((int) i);
        NK_TEST__ACTUAL_INT(my_array.items[i]);
    }
#undef TEST_ITEM_NO
#undef TEST_ITEM_TYPE
}


static void
test__construction__initialize_empty(void)
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
    NK_ARRAY__INITIALIZE_EMPTY(&my_array, NK_BITS__ARRAY_SIZE(items_buffer), items_buffer);
    NK_TEST__EXPECT_SIZE(sizeof(TEST_ITEM_TYPE));
    NK_TEST__ACTUAL_SIZE(NK_ARRAY__ITEM_SIZE(&my_array));
    NK_TEST__EXPECT_SIZE(TEST_ITEM_NO);
    NK_TEST__ACTUAL_SIZE(my_array.item_no);
    NK_TEST__EXPECT_SIZE(0u);
    NK_TEST__ACTUAL_SIZE(my_array.length);
#undef TEST_ITEM_NO
#undef TEST_ITEM_TYPE
}

static void
test__construction__initialize_with(void)
{
#define TEST_ITEM_NO            32
#define TEST_ITEM_TYPE          int
    /* Allocate external storage which is to be used by array */
    TEST_ITEM_TYPE items_buffer[TEST_ITEM_NO] = {0, 1, 2, 3};
    /* Create CUT array type: structure my_char_array */
    struct my_char_array
        NK_ARRAY__T(TEST_ITEM_TYPE)
    my_array;
    /* Initialize the array */
    NK_ARRAY__INITIALIZE_WITH(&my_array, items_buffer, 4u);
    NK_TEST__EXPECT_SIZE(sizeof(TEST_ITEM_TYPE));
    NK_TEST__ACTUAL_SIZE(NK_ARRAY__ITEM_SIZE(&my_array));
    NK_TEST__EXPECT_SIZE(TEST_ITEM_NO);
    NK_TEST__ACTUAL_SIZE(my_array.item_no);
    NK_TEST__EXPECT_SIZE(4u);
    NK_TEST__ACTUAL_SIZE(my_array.length);
    for (size_t i = 0u; i < my_array.length; i++) {
        NK_TEST__EXPECT_INT((int) i);
        NK_TEST__ACTUAL_INT(my_array.items[i]);
    }
#undef TEST_ITEM_NO
#undef TEST_ITEM_TYPE
}

static void
test__construction__initialize_empty_with(void)
{
#define TEST_ITEM_NO            32
#define TEST_ITEM_TYPE          int
    /* Allocate external storage which is to be used by array */
    TEST_ITEM_TYPE items_buffer[TEST_ITEM_NO] = {0, 1, 2, 3};
    /* Create CUT array type: structure my_char_array */
    struct my_char_array
        NK_ARRAY__T(TEST_ITEM_TYPE)
    my_array;
    /* Initialize the array */
    NK_ARRAY__INITIALIZE_EMPTY_WITH(&my_array, items_buffer);
    NK_TEST__EXPECT_SIZE(sizeof(TEST_ITEM_TYPE));
    NK_TEST__ACTUAL_SIZE(NK_ARRAY__ITEM_SIZE(&my_array));
    NK_TEST__EXPECT_SIZE(TEST_ITEM_NO);
    NK_TEST__ACTUAL_SIZE(my_array.item_no);
    NK_TEST__EXPECT_SIZE(0u);
    NK_TEST__ACTUAL_SIZE(my_array.length);
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
    NK_ARRAY__INITIALIZE_EMPTY(&my_array, TEST_ITEM_NO, items_buffer);
    /* Fill in the array with numbers */
    for (size_t i = 0u; i < my_array.item_no; i++) {
        my_array.items[i] = (int)i;
        my_array.length++;
    }
    NK_TEST__EXPECT_SIZE(my_array.item_no);
    NK_TEST__ACTUAL_SIZE(my_array.length);

    for (size_t i = 0u; i < my_array.length; i++) {
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
    NK_ARRAY__INITIALIZE_EMPTY(&my_array, TEST_ITEM_NO, items_buffer);
    /* Fill in the array with numbers */
    for (size_t i = 0u; i < my_array.item_no; i++) {
        my_array.items[i] = (int) i;
    }
    my_array.length += my_array.item_no;
    for (size_t i = 0u; i < my_array.length; i++) {
        NK_TEST__EXPECT_INT((int ) i);
        NK_TEST__ACTUAL_INT(my_array.items[i]);
    }
#undef TEST_ITEM_NO
#undef TEST_ITEM_TYPE
}

static void
test__clear(void)
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
    NK_ARRAY__INITIALIZE_EMPTY(&my_array, TEST_ITEM_NO, items_buffer);
    /* Fill in the array with numbers */
    for (size_t i = 0u; i < my_array.item_no; i++) {
        my_array.items[i] = (int) i;
        my_array.length += 1;
    }
    my_array.length = 0u;
    NK_TEST__EXPECT_SIZE(TEST_ITEM_NO);
    NK_TEST__EXPECT_SIZE(my_array.item_no);
    NK_TEST__EXPECT_SIZE(0u);
    NK_TEST__EXPECT_SIZE(my_array.length);
#undef TEST_ITEM_NO
#undef TEST_ITEM_TYPE
}

static void
test__bucket__construction__initializer_0(void)
{
#define TEST_ITEM_NO            16
#define TEST_ITEM_TYPE          int
    /* Create our CUT array type: structure my_int_array */
    struct my_int_array
        NK_ARRAY__BUCKET_T(TEST_ITEM_TYPE, TEST_ITEM_NO)
    my_array = NK_ARRAY__BUCKET_INITIALIZER(&my_array, 0u, { 0 });

    NK_TEST__EXPECT_SIZE(sizeof(TEST_ITEM_TYPE));
    NK_TEST__ACTUAL_SIZE(NK_ARRAY__ITEM_SIZE(&my_array.array));
    NK_TEST__EXPECT_SIZE(TEST_ITEM_NO);
    NK_TEST__ACTUAL_SIZE(my_array.array.item_no);
    NK_TEST__EXPECT_SIZE(0u);
    NK_TEST__ACTUAL_SIZE(my_array.array.length);
    for (size_t i = 0u; i < my_array.array.length; i++) {
        NK_TEST__EXPECT_INT((int ) i);
        NK_TEST__ACTUAL_INT(my_array.array.items[i]);
    }
#undef TEST_ITEM_NO
#undef TEST_ITEM_TYPE
}

static void
test__bucket__construction__initializer_4(void)
{
#define TEST_ITEM_NO            16
#define TEST_ITEM_TYPE          int
    /* Create our CUT array type: structure my_int_array */
    struct my_int_array
        NK_ARRAY__BUCKET_T(TEST_ITEM_TYPE, TEST_ITEM_NO)
    my_array = NK_ARRAY__BUCKET_INITIALIZER(&my_array, 4u, { 0, 1, 2, 3 });

    NK_TEST__EXPECT_SIZE(sizeof(TEST_ITEM_TYPE));
    NK_TEST__ACTUAL_SIZE(NK_ARRAY__ITEM_SIZE(&my_array.array));
    NK_TEST__EXPECT_SIZE(TEST_ITEM_NO);
    NK_TEST__ACTUAL_SIZE(my_array.array.item_no);
    NK_TEST__EXPECT_SIZE(4u);
    NK_TEST__ACTUAL_SIZE(my_array.array.length);
#undef TEST_ITEM_NO
#undef TEST_ITEM_TYPE
}

static void
test__bucket__construction__initializer_empty(void)
{
#define TEST_ITEM_NO            16
#define TEST_ITEM_TYPE          int
    /* Create our CUT array type: structure my_int_array */
    struct my_int_array
        NK_ARRAY__BUCKET_T(TEST_ITEM_TYPE, TEST_ITEM_NO)
    my_array = NK_ARRAY__BUCKET_INITIALIZER_EMPTY(&my_array);

    NK_TEST__EXPECT_SIZE(sizeof(TEST_ITEM_TYPE));
    NK_TEST__ACTUAL_SIZE(NK_ARRAY__ITEM_SIZE(&my_array.array));
    NK_TEST__EXPECT_SIZE(TEST_ITEM_NO);
    NK_TEST__ACTUAL_SIZE(my_array.array.item_no);
    NK_TEST__EXPECT_SIZE(0u);
    NK_TEST__ACTUAL_SIZE(my_array.array.length);
#undef TEST_ITEM_NO
#undef TEST_ITEM_TYPE
}

static void
test__bucket__construction__initialize_0(void)
{
#define TEST_ITEM_NO            16
#define TEST_ITEM_TYPE          char
    TEST_ITEM_TYPE a_buffer[TEST_ITEM_NO];
    struct my_ptr_array
        NK_ARRAY__BUCKET_T(TEST_ITEM_TYPE, TEST_ITEM_NO)
    my_array;

    NK_ARRAY__BUCKET_INITIALIZE(&my_array, a_buffer, 0u);

    NK_TEST__EXPECT_SIZE(sizeof(TEST_ITEM_TYPE));
    NK_TEST__ACTUAL_SIZE(NK_ARRAY__ITEM_SIZE(&my_array.array));
    NK_TEST__EXPECT_SIZE(TEST_ITEM_NO);
    NK_TEST__ACTUAL_SIZE(my_array.array.item_no);
    NK_TEST__EXPECT_SIZE(0u);
    NK_TEST__ACTUAL_SIZE(my_array.array.length);
#undef TEST_ITEM_NO
#undef TEST_ITEM_TYPE
}

static void
test__bucket__construction__initialize_4(void)
{
#define TEST_ITEM_NO            16
#define TEST_ITEM_TYPE          char
    TEST_ITEM_TYPE a_buffer[] = {0, 1, 2, 3};
    struct my_ptr_array
        NK_ARRAY__BUCKET_T(TEST_ITEM_TYPE, TEST_ITEM_NO)
    my_array;

    NK_ARRAY__BUCKET_INITIALIZE(&my_array, a_buffer, NK_BITS__ARRAY_SIZE(a_buffer));

    NK_TEST__EXPECT_SIZE(sizeof(TEST_ITEM_TYPE));
    NK_TEST__ACTUAL_SIZE(NK_ARRAY__ITEM_SIZE(&my_array.array));
    NK_TEST__EXPECT_SIZE(TEST_ITEM_NO);
    NK_TEST__ACTUAL_SIZE(my_array.array.item_no);
    NK_TEST__EXPECT_SIZE(4u);
    NK_TEST__ACTUAL_SIZE(my_array.array.length);
    for (size_t i = 0u; i < my_array.array.length; i++) {
        NK_TEST__EXPECT_INT((int ) i);
        NK_TEST__ACTUAL_INT(my_array.array.items[i]);
    }
#undef TEST_ITEM_NO
#undef TEST_ITEM_TYPE
}

static void
test__bucket__construction__initialize_empty(void)
{
#define TEST_ITEM_NO            8
#define TEST_ITEM_TYPE          char
    struct my_ptr_array
        NK_ARRAY__BUCKET_T(TEST_ITEM_TYPE, TEST_ITEM_NO)
    my_array;

    NK_ARRAY__BUCKET_INITIALIZE_EMPTY(&my_array);

    NK_TEST__EXPECT_SIZE(sizeof(TEST_ITEM_TYPE));
    NK_TEST__ACTUAL_SIZE(NK_ARRAY__ITEM_SIZE(&my_array.array));
    NK_TEST__EXPECT_SIZE(TEST_ITEM_NO);
    NK_TEST__ACTUAL_SIZE(my_array.array.item_no);
    NK_TEST__EXPECT_SIZE(0u);
    NK_TEST__ACTUAL_SIZE(my_array.array.length);
#undef TEST_ITEM_NO
#undef TEST_ITEM_TYPE
}

static void
test__bucket__construction__initialize_with(void)
{
#define TEST_ITEM_NO            18
#define TEST_ITEM_TYPE          char
    TEST_ITEM_TYPE c_array[] = {0, 1, 2, 3, 4, 5, 6, 7};
    struct my_ptr_array
        NK_ARRAY__BUCKET_T(TEST_ITEM_TYPE, TEST_ITEM_NO)
    my_array;

    NK_ARRAY__BUCKET_INITIALIZE_WITH(&my_array, c_array);

    NK_TEST__EXPECT_SIZE(sizeof(TEST_ITEM_TYPE));
    NK_TEST__ACTUAL_SIZE(NK_ARRAY__ITEM_SIZE(&my_array.array));
    NK_TEST__EXPECT_SIZE(TEST_ITEM_NO);
    NK_TEST__ACTUAL_SIZE(my_array.array.item_no);
    NK_TEST__EXPECT_SIZE(8u);
    NK_TEST__ACTUAL_SIZE(my_array.array.length);
    for (size_t i = 0u; i < my_array.array.length; i++) {
        NK_TEST__EXPECT_INT((int) i);
        NK_TEST__ACTUAL_INT(my_array.array.items[i]);
    }
#undef TEST_ITEM_NO
#undef TEST_ITEM_TYPE
}

static void
test__bucket__ref__set_get(void)
{
#define TEST_ITEM_NO            128
#define TEST_ITEM_TYPE          int
    /* Create our CUT array type: structure my_char_array */
    struct my_char_array
        NK_ARRAY__BUCKET_T(TEST_ITEM_TYPE, TEST_ITEM_NO)
    my_bucket;
    /* Initialize the array */
    NK_ARRAY__BUCKET_INITIALIZE_EMPTY(&my_bucket);
    /* Fill in the array with numbers */
    for (size_t i = 0u; i < my_bucket.array.item_no; i++) {
        my_bucket.array.items[i] = (int) i;
        my_bucket.array.length++;
    }
    for (size_t i = 0u; i < my_bucket.array.length; i++) {
        NK_TEST__EXPECT_INT((int ) i);
        NK_TEST__ACTUAL_INT(my_bucket.array.items[i]);
    }
#undef TEST_ITEM_NO
#undef TEST_ITEM_TYPE
}

void
test_nk_array(void)
{
    static const struct nk_testsuite__test tests[] = {
    NK_TEST__TEST(test__construction__initializer_0),
    NK_TEST__TEST(test__construction__initializer_4),
    NK_TEST__TEST(test__construction__initializer_empty),
    NK_TEST__TEST(test__construction__initialize_0),
    NK_TEST__TEST(test__construction__initialize_4),
    NK_TEST__TEST(test__construction__initialize_empty),
    NK_TEST__TEST(test__construction__initialize_with),
    NK_TEST__TEST(test__construction__initialize_empty_with),
    NK_TEST__TEST(test__ref__set),
    NK_TEST__TEST(test__ref__get),
    NK_TEST__TEST(test__clear),
    NK_TEST__TEST(test__bucket__construction__initializer_0),
    NK_TEST__TEST(test__bucket__construction__initializer_4),
    NK_TEST__TEST(test__bucket__construction__initializer_empty),
    NK_TEST__TEST(test__bucket__construction__initialize_0),
    NK_TEST__TEST(test__bucket__construction__initialize_4),
    NK_TEST__TEST(test__bucket__construction__initialize_empty),
    NK_TEST__TEST(test__bucket__construction__initialize_with),
    NK_TEST__TEST(test__bucket__ref__set_get),
    NK_TEST__TEST_TERMINATE() };
    nk_test__run_fixture(tests, NULL, NULL, NK_TESTSUITE__FIXTURE_NAME(none));
}
#else /* !defined(NK_ENABLED_ARRAY) */
void
test_nk_array(void)
{
}
#endif /* defined(NK_ENABLED_ARRAY) */
