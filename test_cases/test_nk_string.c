/*
 * test_nk_string.c
 *
 *  Created on: Apr 10, 2021
 *      Author: nenad
 */

#include "../nk_test.h"
#include "test_nk_string.h"
#include "generic/nk_string.h"

#if defined(NK_ENABLED_STRING)

static void
test__construction__initializer_0(void)
{
#define TEST_STRING_SIZE 16
    char string_buffer[TEST_STRING_SIZE] = { 0 };

    struct nk_string my_string = NK_STRING__INITIALIZER(string_buffer, 0u);
    NK_TEST__EXPECT_SIZE(0u);
    NK_TEST__ACTUAL_SIZE(my_string.length);
    NK_TEST__EXPECT_SIZE(TEST_STRING_SIZE);
    NK_TEST__ACTUAL_SIZE(my_string.item_no);
#undef TEST_STRING_SIZE
}

static void
test__construction__initializer_4(void)
{
#define TEST_STRING_SIZE 16
    char string_buffer[TEST_STRING_SIZE] = "nesa";

    struct nk_string my_string = NK_STRING__INITIALIZER(string_buffer, 4u);
    NK_TEST__EXPECT_SIZE(TEST_STRING_SIZE);
    NK_TEST__ACTUAL_SIZE(my_string.item_no);
    NK_TEST__EXPECT_SIZE(4u);
    NK_TEST__ACTUAL_SIZE(my_string.length);
    NK_TEST__EXPECT_INT('n');
    NK_TEST__ACTUAL_INT(my_string.items[0]);
    NK_TEST__EXPECT_INT('e');
    NK_TEST__ACTUAL_INT(my_string.items[1]);
    NK_TEST__EXPECT_INT('s');
    NK_TEST__ACTUAL_INT(my_string.items[2]);
    NK_TEST__EXPECT_INT('a');
    NK_TEST__ACTUAL_INT(my_string.items[3]);
#undef TEST_STRING_SIZE
}

static void
test__construction__initializer_empty(void)
{
#define TEST_STRING_SIZE 16
#define TEST_STRING "some string"
    char string_buffer[TEST_STRING_SIZE] = { TEST_STRING };
    struct nk_string my_string = NK_STRING__INITIALIZER_EMPTY(string_buffer);

    NK_TEST__EXPECT_SIZE(0u);
    NK_TEST__ACTUAL_SIZE(my_string.length);
    NK_TEST__EXPECT_SIZE(TEST_STRING_SIZE);
    NK_TEST__ACTUAL_SIZE(my_string.item_no);
#undef TEST_STRING
#undef TEST_STRING_SIZE
}

static void
test__construction__initialize_0(void)
{
#define TEST_STRING_SIZE 16
    char string_buffer[TEST_STRING_SIZE] = { 0 };

    struct nk_string my_string;

    nk_string__initialize(&my_string, string_buffer, sizeof(string_buffer), 0u);
    NK_TEST__EXPECT_SIZE(0u);
    NK_TEST__ACTUAL_SIZE(my_string.length);
    NK_TEST__EXPECT_SIZE(TEST_STRING_SIZE);
    NK_TEST__ACTUAL_SIZE(my_string.item_no);
#undef TEST_STRING_SIZE
}

static void
test__construction__initialize_4(void)
{
#define TEST_STRING_SIZE 16
    char string_buffer[TEST_STRING_SIZE] = "nesa";

    struct nk_string my_string;

    nk_string__initialize(&my_string, string_buffer, sizeof(string_buffer), 4u);
    NK_TEST__EXPECT_SIZE(4u);
    NK_TEST__ACTUAL_SIZE(my_string.length);
    NK_TEST__EXPECT_SIZE(TEST_STRING_SIZE);
    NK_TEST__ACTUAL_SIZE(my_string.item_no);
    NK_TEST__EXPECT_INT('n');
    NK_TEST__ACTUAL_INT(my_string.items[0]);
    NK_TEST__EXPECT_INT('e');
    NK_TEST__ACTUAL_INT(my_string.items[1]);
    NK_TEST__EXPECT_INT('s');
    NK_TEST__ACTUAL_INT(my_string.items[2]);
    NK_TEST__EXPECT_INT('a');
    NK_TEST__ACTUAL_INT(my_string.items[3]);
#undef TEST_STRING_SIZE
}

static void
test__construction__initialize_empty(void)
{
#define TEST_STRING_SIZE 16
    char string_buffer[TEST_STRING_SIZE] = { 0 };

    struct nk_string my_string;

    nk_string__initialize_empty(&my_string, string_buffer, sizeof(string_buffer));
    NK_TEST__EXPECT_SIZE(0u);
    NK_TEST__ACTUAL_SIZE(my_string.length);
    NK_TEST__EXPECT_SIZE(TEST_STRING_SIZE);
    NK_TEST__ACTUAL_SIZE(my_string.item_no);
#undef TEST_STRING_SIZE
}

static void
test__bucket_construction__initializer_0(void)
{
#define TEST_STRING_SIZE 20
    struct my_string_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string =
    NK_STRING__BUCKET_INITIALIZER(&my_string, "");
    NK_TEST__EXPECT_SIZE(0u);
    NK_TEST__ACTUAL_SIZE(my_string.array.length);
    NK_TEST__EXPECT_SIZE(TEST_STRING_SIZE);
    NK_TEST__ACTUAL_SIZE(my_string.array.item_no);
#undef TEST_STRING_SIZE
}

static void
test__bucket_construction__initializer_4(void)
{
#define TEST_STRING_SIZE 20
    struct my_string_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string =
    NK_STRING__BUCKET_INITIALIZER(&my_string, "nesa");
    NK_TEST__EXPECT_SIZE(4u);
    NK_TEST__ACTUAL_SIZE(my_string.array.length);
    NK_TEST__EXPECT_SIZE(TEST_STRING_SIZE);
    NK_TEST__ACTUAL_SIZE(my_string.array.item_no);
    NK_TEST__EXPECT_INT('n');
    NK_TEST__ACTUAL_INT(my_string.array.items[0]);
    NK_TEST__EXPECT_INT('e');
    NK_TEST__ACTUAL_INT(my_string.array.items[1]);
    NK_TEST__EXPECT_INT('s');
    NK_TEST__ACTUAL_INT(my_string.array.items[2]);
    NK_TEST__EXPECT_INT('a');
    NK_TEST__ACTUAL_INT(my_string.array.items[3]);
#undef TEST_STRING_SIZE
}

static void
test__bucket_construction__initializer_empty(void)
{
#define TEST_STRING_SIZE 20
    struct my_string_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string =
    NK_STRING__BUCKET_INITIALIZER_EMPTY(&my_string);
    NK_TEST__EXPECT_SIZE(0u);
    NK_TEST__ACTUAL_SIZE(my_string.array.length);
    NK_TEST__EXPECT_SIZE(TEST_STRING_SIZE);
    NK_TEST__ACTUAL_SIZE(my_string.array.item_no);
#undef TEST_STRING_SIZE
}

static void
test__bucket_construction__initialize_0(void)
{
#define TEST_STRING_SIZE 20
    struct my_string_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string;
    NK_STRING__BUCKET_INITIALIZE(&my_string, NULL, 0u);
    NK_TEST__EXPECT_SIZE(0u);
    NK_TEST__ACTUAL_SIZE(my_string.array.length);
    NK_TEST__EXPECT_SIZE(TEST_STRING_SIZE);
    NK_TEST__ACTUAL_SIZE(my_string.array.item_no);
#undef TEST_STRING_SIZE
}

static void
test__bucket_construction__initialize_4(void)
{
#define TEST_STRING_SIZE 20
    char static_buffer[] = "nesa";
    struct my_string_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string;
    NK_STRING__BUCKET_INITIALIZE(&my_string, static_buffer, 4u);
    NK_TEST__EXPECT_SIZE(4u);
    NK_TEST__ACTUAL_SIZE(my_string.array.length);
    NK_TEST__EXPECT_SIZE(TEST_STRING_SIZE);
    NK_TEST__ACTUAL_SIZE(my_string.array.item_no);
    NK_TEST__EXPECT_INT('n');
    NK_TEST__ACTUAL_INT(my_string.array.items[0]);
    NK_TEST__EXPECT_INT('e');
    NK_TEST__ACTUAL_INT(my_string.array.items[1]);
    NK_TEST__EXPECT_INT('s');
    NK_TEST__ACTUAL_INT(my_string.array.items[2]);
    NK_TEST__EXPECT_INT('a');
    NK_TEST__ACTUAL_INT(my_string.array.items[3]);
#undef TEST_STRING_SIZE
}

static void
test__bucket_construction__initialize_empty(void)
{
#define TEST_STRING_SIZE 20
    struct my_string_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string;
    NK_STRING__BUCKET_INITIALIZE_EMPTY(&my_string);
    NK_TEST__EXPECT_SIZE(0u);
    NK_TEST__ACTUAL_SIZE(my_string.array.length);
    NK_TEST__EXPECT_SIZE(TEST_STRING_SIZE);
    NK_TEST__ACTUAL_SIZE(my_string.array.item_no);
#undef TEST_STRING_SIZE
}

static void
test__bucket_construction__initialize_with(void)
{
#define TEST_STRING_SIZE 20
    char c_string_buffer[] = "Hello";
    struct my_string_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string;
    NK_STRING__BUCKET_INITIALIZE_WITH(&my_string, c_string_buffer);
    NK_TEST__EXPECT_SIZE(5u);
    NK_TEST__ACTUAL_SIZE(my_string.array.length);
    NK_TEST__EXPECT_SIZE(TEST_STRING_SIZE);
    NK_TEST__ACTUAL_SIZE(my_string.array.item_no);
#undef TEST_STRING_SIZE
}

static void
test__is_equal__true__same_size(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER(&my_string1, "Hello");
    struct my_string2_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string2 =
    NK_STRING__BUCKET_INITIALIZER(&my_string2, "Hello");
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(nk_string__is_equal(&my_string1.array, &my_string2.array));
#undef TEST_STRING_SIZE
}

static void
test__is_equal__true__different_size(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER(&my_string1, "Hello");
    struct my_string2_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE / 2u)
    my_string2 =
    NK_STRING__BUCKET_INITIALIZER(&my_string2, "Hello");
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(nk_string__is_equal(&my_string1.array, &my_string2.array));
#undef TEST_STRING_SIZE
}

static void
test__is_equal__false__same_size(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER(&my_string1, "Hello");
    struct my_string2_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string2 =
    NK_STRING__BUCKET_INITIALIZER(&my_string2, "Zdrav");
    NK_TEST__EXPECT_BOOL(false);
    NK_TEST__ACTUAL_BOOL(nk_string__is_equal(&my_string1.array, &my_string2.array));
#undef TEST_STRING_SIZE
}

static void
test__is_equal__false__different_size(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER(&my_string1, "Hello");
    struct my_string2_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string2 =
    NK_STRING__BUCKET_INITIALIZER(&my_string2, "Zdravo!");
    NK_TEST__EXPECT_BOOL(false);
    NK_TEST__ACTUAL_BOOL(nk_string__is_equal(&my_string1.array, &my_string2.array));
#undef TEST_STRING_SIZE
}

static void
test__view(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER(&my_string1, "Hello");
    struct my_string2_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string2 =
    NK_STRING__BUCKET_INITIALIZER(&my_string2, "ell");

    struct nk_string string_view = nk_string__view(&my_string1.array, 1, 4);
    NK_TEST__EXPECT_SIZE(3);
    NK_TEST__ACTUAL_SIZE(nk_string__length(&string_view));
    NK_TEST__EXPECT_SIZE(3);
    NK_TEST__ACTUAL_SIZE(nk_string__size(&string_view));
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(nk_string__is_equal(&string_view, &my_string2.array));
#undef TEST_STRING_SIZE
}

static void
test__contains__true(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER(&my_string1, "Hello, World!");
    struct my_string2_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string2 =
    NK_STRING__BUCKET_INITIALIZER(&my_string2, "World");

    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(nk_string__contains(&my_string1.array, &my_string2.array));
#undef TEST_STRING_SIZE
}

static void
test__contains__false__smaller_length(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER(&my_string1, "Hello, World!");
    struct my_string2_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string2 =
    NK_STRING__BUCKET_INITIALIZER(&my_string2, "world");

    NK_TEST__EXPECT_BOOL(false);
    NK_TEST__ACTUAL_BOOL(nk_string__contains(&my_string1.array, &my_string2.array));
#undef TEST_STRING_SIZE
}

static void
test__contains__false__bigger_length(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER(&my_string1, "Hello, World!");
    struct my_string2_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string2 =
    NK_STRING__BUCKET_INITIALIZER(&my_string2, "Hello my friend");

    NK_TEST__EXPECT_BOOL(false);
    NK_TEST__ACTUAL_BOOL(nk_string__contains(&my_string1.array, &my_string2.array));
#undef TEST_STRING_SIZE
}

static void
test__startswith__true(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER(&my_string1, "Hello, World!");
    struct my_string2_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string2 =
    NK_STRING__BUCKET_INITIALIZER(&my_string2, "Hello, ");

    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(nk_string__startswith(&my_string1.array, &my_string2.array));
#undef TEST_STRING_SIZE
}

static void
test__startswith__false__smaller_length(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER(&my_string1, "Hello, World!");
    struct my_string2_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string2 =
    NK_STRING__BUCKET_INITIALIZER(&my_string2, "Hello ");

    NK_TEST__EXPECT_BOOL(false);
    NK_TEST__ACTUAL_BOOL(nk_string__startswith(&my_string1.array, &my_string2.array));
#undef TEST_STRING_SIZE
}

static void
test__startswith__false__bigger_length(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER(&my_string1, "Hello, World!");
    struct my_string2_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string2 =
    NK_STRING__BUCKET_INITIALIZER(&my_string2, "Hello, World! oOo");

    NK_TEST__EXPECT_BOOL(false);
    NK_TEST__ACTUAL_BOOL(nk_string__startswith(&my_string1.array, &my_string2.array));
#undef TEST_STRING_SIZE
}

static void
test__endswith__true(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER(&my_string1, "Hello, World!");
    struct my_string2_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string2 =
    NK_STRING__BUCKET_INITIALIZER(&my_string2, ", World!");

    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(nk_string__endswith(&my_string1.array, &my_string2.array));
#undef TEST_STRING_SIZE
}

static void
test__endswith__false__smaller_length(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER(&my_string1, "Hello, World!");
    struct my_string2_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string2 =
    NK_STRING__BUCKET_INITIALIZER(&my_string2, ", World");

    NK_TEST__EXPECT_BOOL(false);
    NK_TEST__ACTUAL_BOOL(nk_string__endswith(&my_string1.array, &my_string2.array));
#undef TEST_STRING_SIZE
}

static void
test__endswith__false__bigger_length(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER(&my_string1, "Hello, World!");
    struct my_string2_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string2 =
    NK_STRING__BUCKET_INITIALIZER(&my_string2, "Ooo Hello, World!");

    NK_TEST__EXPECT_BOOL(false);
    NK_TEST__ACTUAL_BOOL(nk_string__endswith(&my_string1.array, &my_string2.array));
#undef TEST_STRING_SIZE
}

static void
test__rstrip(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER(&my_string1, "Hello, World!");
    struct my_string2_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string2 =
    NK_STRING__BUCKET_INITIALIZER(&my_string2, ", World!");
    struct my_string3_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string3 =
    NK_STRING__BUCKET_INITIALIZER(&my_string3, "Hello");

    nk_string__rstrip(&my_string1.array, &my_string2.array);
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(nk_string__is_equal(&my_string1.array, &my_string3.array));
#undef TEST_STRING_SIZE
}

static void
test__lstrip(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER(&my_string1, "Hello, World!");
    struct my_string2_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string2 =
    NK_STRING__BUCKET_INITIALIZER(&my_string2, "Hello, ");
    struct my_string3_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string3 =
    NK_STRING__BUCKET_INITIALIZER(&my_string3, "World!");

    nk_string__lstrip(&my_string1.array, &my_string2.array);
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(nk_string__is_equal(&my_string1.array, &my_string3.array));
#undef TEST_STRING_SIZE
}

static void
test__lower(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER(&my_string1, "Hello, World!");
    struct my_string2_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string2 =
    NK_STRING__BUCKET_INITIALIZER(&my_string2, "hello, world!");

    nk_string__lower(&my_string1.array);
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(nk_string__is_equal(&my_string1.array, &my_string2.array));
#undef TEST_STRING_SIZE
}

static void
test__upper(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER(&my_string1, "Hello, World!");
    struct my_string2_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string2 =
    NK_STRING__BUCKET_INITIALIZER(&my_string2, "HELLO, WORLD!");

    nk_string__upper(&my_string1.array);
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(nk_string__is_equal(&my_string1.array, &my_string2.array));
#undef TEST_STRING_SIZE
}

static void
test__clear_all(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER(&my_string1, "Hello, World!");

    nk_string__clear_all(&my_string1.array);
    NK_TEST__EXPECT_SIZE(0u);
    NK_TEST__ACTUAL_SIZE(my_string1.array.length);
#undef TEST_STRING_SIZE
}

static void
test__append(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER(&my_string1, "Hello");
    struct my_string1_type my_string2 =
    NK_STRING__BUCKET_INITIALIZER(&my_string2, ", World!");
    struct my_string1_type my_string3 =
    NK_STRING__BUCKET_INITIALIZER(&my_string3, "Hello, World!");

    nk_string__append(&my_string1.array, &my_string2.array);
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(nk_string__is_equal(&my_string1.array, &my_string3.array));
#undef TEST_STRING_SIZE
}

static void
test__copy(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER(&my_string1, "Hello");
    struct my_string1_type my_string2 =
    NK_STRING__BUCKET_INITIALIZER(&my_string2, ", World!");
    struct my_string1_type my_string3 =
    NK_STRING__BUCKET_INITIALIZER(&my_string3, ", World!");

    nk_string__copy(&my_string1.array, &my_string2.array);
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(nk_string__is_equal(&my_string1.array, &my_string3.array));
#undef TEST_STRING_SIZE
}

void
test_nk_string(void)
{
    static const struct nk_testsuite__test tests[] = {
    NK_TEST__TEST(test__construction__initializer_0),
    NK_TEST__TEST(test__construction__initializer_4),
    NK_TEST__TEST(test__construction__initializer_empty),
    NK_TEST__TEST(test__construction__initialize_0),
    NK_TEST__TEST(test__construction__initialize_4),
    NK_TEST__TEST(test__construction__initialize_empty),
    NK_TEST__TEST(test__bucket_construction__initializer_0),
    NK_TEST__TEST(test__bucket_construction__initializer_4),
    NK_TEST__TEST(test__bucket_construction__initializer_empty),
    NK_TEST__TEST(test__bucket_construction__initialize_0),
    NK_TEST__TEST(test__bucket_construction__initialize_4),
    NK_TEST__TEST(test__bucket_construction__initialize_empty),
    NK_TEST__TEST(test__bucket_construction__initialize_with),
    NK_TEST__TEST(test__is_equal__true__same_size),
    NK_TEST__TEST(test__is_equal__true__different_size),
    NK_TEST__TEST(test__is_equal__false__same_size),
    NK_TEST__TEST(test__is_equal__false__different_size),
    NK_TEST__TEST(test__view),
    NK_TEST__TEST(test__contains__true),
    NK_TEST__TEST(test__contains__false__smaller_length),
    NK_TEST__TEST(test__contains__false__bigger_length),
    NK_TEST__TEST(test__startswith__true),
    NK_TEST__TEST(test__startswith__false__smaller_length),
    NK_TEST__TEST(test__startswith__false__bigger_length),
    NK_TEST__TEST(test__endswith__true),
    NK_TEST__TEST(test__endswith__false__smaller_length),
    NK_TEST__TEST(test__endswith__false__bigger_length),
    NK_TEST__TEST(test__rstrip),
    NK_TEST__TEST(test__lstrip),
    NK_TEST__TEST(test__lower),
    NK_TEST__TEST(test__upper),
    NK_TEST__TEST(test__clear_all),
    NK_TEST__TEST(test__append),
    NK_TEST__TEST(test__copy),
    NK_TEST__TEST_TERMINATE() };
    nk_test__run_fixture(tests, NULL, NULL, NK_TESTSUITE__FIXTURE_NAME(none));
}
#else /* !defined(NK_ENABLED_STRING) */
void
test_nk_string(void)
{
}
#endif /* defined(NK_ENABLED_STRING) */
