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
test__construction__initializer(void)
{
#define TEST_STRING_SIZE 16
    char string_buffer[TEST_STRING_SIZE] = { 0 };

    struct nk_string my_string = NK_STRING__INITIALIZER(string_buffer);
    NK_TEST__EXPECT_SIZE(0);
    NK_TEST__ACTUAL_SIZE(nk_string__length(&my_string));
    NK_TEST__EXPECT_SIZE(TEST_STRING_SIZE);
    NK_TEST__ACTUAL_SIZE(nk_string__size(&my_string));
#undef TEST_STRING_SIZE
}

static void
test__construction__initialize(void)
{
#define TEST_STRING_SIZE 16
    char string_buffer[TEST_STRING_SIZE] = { 0 };

    struct nk_string my_string;

    NK_STRING__INITIALIZE(&my_string, string_buffer);
    NK_TEST__EXPECT_SIZE(0);
    NK_TEST__ACTUAL_SIZE(nk_string__length(&my_string));
    NK_TEST__EXPECT_SIZE(TEST_STRING_SIZE);
    NK_TEST__ACTUAL_SIZE(nk_string__size(&my_string));
    for (size_t i = 0u; i < nk_string__size(&my_string); i++) {
        NK_TEST__EXPECT_INT(0);
        NK_TEST__ACTUAL_INT(nk_string__char(&my_string, i));
    }
#undef TEST_STRING_SIZE
}

static void
test__bucket_construction__initializer(void)
{
#define TEST_STRING_SIZE 20
    struct my_string_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string =
    NK_STRING__BUCKET_INITIALIZER(&my_string);
    NK_TEST__EXPECT_SIZE(0);
    NK_TEST__ACTUAL_SIZE(nk_string__length(&my_string.string));
    NK_TEST__EXPECT_SIZE(TEST_STRING_SIZE);
    NK_TEST__ACTUAL_SIZE(nk_string__size(&my_string.string));
    for (size_t i = 0u; i < nk_string__size(&my_string.string); i++) {
        NK_TEST__EXPECT_INT(0);
        NK_TEST__ACTUAL_INT(nk_string__char(&my_string.string, i));
    }
#undef TEST_STRING_SIZE
}

static void
test__bucket_construction__initializer_from(void)
{
#define TEST_STRING_SIZE 20
    struct my_string_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string =
    NK_STRING__BUCKET_INITIALIZER_FROM(&my_string, "Hello");
    NK_TEST__EXPECT_SIZE(5);
    NK_TEST__ACTUAL_SIZE(nk_string__length(&my_string.string));
    NK_TEST__EXPECT_SIZE(TEST_STRING_SIZE);
    NK_TEST__ACTUAL_SIZE(nk_string__size(&my_string.string));
    NK_TEST__EXPECT_INT('H');
    NK_TEST__ACTUAL_INT(nk_string__char(&my_string.string, 0));
    NK_TEST__EXPECT_INT('e');
    NK_TEST__ACTUAL_INT(nk_string__char(&my_string.string, 1));
    NK_TEST__EXPECT_INT('l');
    NK_TEST__ACTUAL_INT(nk_string__char(&my_string.string, 2));
    NK_TEST__EXPECT_INT('l');
    NK_TEST__ACTUAL_INT(nk_string__char(&my_string.string, 3));
    NK_TEST__EXPECT_INT('o');
    NK_TEST__ACTUAL_INT(nk_string__char(&my_string.string, 4));
#undef TEST_STRING_SIZE
}

static void
test__is_equal__true__same_size(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER_FROM(&my_string1, "Hello");
    struct my_string2_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string2 =
    NK_STRING__BUCKET_INITIALIZER_FROM(&my_string2, "Hello");
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(nk_string__is_equal(&my_string1.string, &my_string2.string));
#undef TEST_STRING_SIZE
}

static void
test__is_equal__true__different_size(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER_FROM(&my_string1, "Hello");
    struct my_string2_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE / 2u)
    my_string2 =
    NK_STRING__BUCKET_INITIALIZER_FROM(&my_string2, "Hello");
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(nk_string__is_equal(&my_string1.string, &my_string2.string));
#undef TEST_STRING_SIZE
}

static void
test__is_equal__false__same_size(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER_FROM(&my_string1, "Hello");
    struct my_string2_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string2 =
    NK_STRING__BUCKET_INITIALIZER_FROM(&my_string2, "Zdrav");
    NK_TEST__EXPECT_BOOL(false);
    NK_TEST__ACTUAL_BOOL(nk_string__is_equal(&my_string1.string, &my_string2.string));
#undef TEST_STRING_SIZE
}

static void
test__is_equal__false__different_size(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER_FROM(&my_string1, "Hello");
    struct my_string2_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string2 =
    NK_STRING__BUCKET_INITIALIZER_FROM(&my_string2, "Zdravo!");
    NK_TEST__EXPECT_BOOL(false);
    NK_TEST__ACTUAL_BOOL(nk_string__is_equal(&my_string1.string, &my_string2.string));
#undef TEST_STRING_SIZE
}

static void
test__view(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER_FROM(&my_string1, "Hello");
    struct my_string2_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string2 =
    NK_STRING__BUCKET_INITIALIZER_FROM(&my_string2, "ell");

    struct nk_string string_view = nk_string__view(&my_string1.string, 1, 4);
    NK_TEST__EXPECT_SIZE(3);
    NK_TEST__ACTUAL_SIZE(nk_string__length(&string_view));
    NK_TEST__EXPECT_SIZE(3);
    NK_TEST__ACTUAL_SIZE(nk_string__size(&string_view));
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(nk_string__is_equal(&string_view, &my_string2.string));
#undef TEST_STRING_SIZE
}

static void
test__contains__true(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER_FROM(&my_string1, "Hello, World!");
    struct my_string2_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string2 =
    NK_STRING__BUCKET_INITIALIZER_FROM(&my_string2, "World");

    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(nk_string__contains(&my_string1.string, &my_string2.string));
#undef TEST_STRING_SIZE
}

static void
test__contains__false__smaller_length(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER_FROM(&my_string1, "Hello, World!");
    struct my_string2_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string2 =
    NK_STRING__BUCKET_INITIALIZER_FROM(&my_string2, "world");

    NK_TEST__EXPECT_BOOL(false);
    NK_TEST__ACTUAL_BOOL(nk_string__contains(&my_string1.string, &my_string2.string));
#undef TEST_STRING_SIZE
}

static void
test__contains__false__bigger_length(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER_FROM(&my_string1, "Hello, World!");
    struct my_string2_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string2 =
    NK_STRING__BUCKET_INITIALIZER_FROM(&my_string2, "Hello my friend");

    NK_TEST__EXPECT_BOOL(false);
    NK_TEST__ACTUAL_BOOL(nk_string__contains(&my_string1.string, &my_string2.string));
#undef TEST_STRING_SIZE
}

static void
test__endswith__true(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER_FROM(&my_string1, "Hello, World!");
    struct my_string2_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string2 =
    NK_STRING__BUCKET_INITIALIZER_FROM(&my_string2, ", World!");

    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(nk_string__endswith(&my_string1.string, &my_string2.string));
#undef TEST_STRING_SIZE
}

static void
test__endswith__false__smaller_length(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER_FROM(&my_string1, "Hello, World!");
    struct my_string2_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string2 =
    NK_STRING__BUCKET_INITIALIZER_FROM(&my_string2, ", World");

    NK_TEST__EXPECT_BOOL(false);
    NK_TEST__ACTUAL_BOOL(nk_string__endswith(&my_string1.string, &my_string2.string));
#undef TEST_STRING_SIZE
}

static void
test__endswith__false__bigger_length(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER_FROM(&my_string1, "Hello, World!");
    struct my_string2_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string2 =
    NK_STRING__BUCKET_INITIALIZER_FROM(&my_string2, "Ooo Hello, World!");

    NK_TEST__EXPECT_BOOL(false);
    NK_TEST__ACTUAL_BOOL(nk_string__endswith(&my_string1.string, &my_string2.string));
#undef TEST_STRING_SIZE
}

static void
test__rstrip(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER_FROM(&my_string1, "Hello, World!");
    struct my_string2_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string2 =
    NK_STRING__BUCKET_INITIALIZER_FROM(&my_string2, ", World!");
    struct my_string3_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string3 =
    NK_STRING__BUCKET_INITIALIZER_FROM(&my_string3, "Hello");

    nk_string__rstrip(&my_string1.string, &my_string2.string);
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(nk_string__is_equal(&my_string1.string, &my_string3.string));
#undef TEST_STRING_SIZE
}

static void
test__lower(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER_FROM(&my_string1, "Hello, World!");
    struct my_string2_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string2 =
    NK_STRING__BUCKET_INITIALIZER_FROM(&my_string2, "hello, world!");

    nk_string__lower(&my_string1.string);
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(nk_string__is_equal(&my_string1.string, &my_string2.string));
#undef TEST_STRING_SIZE
}

static void
test__upper(void)
{
#define TEST_STRING_SIZE 20
    struct my_string1_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string1 =
    NK_STRING__BUCKET_INITIALIZER_FROM(&my_string1, "Hello, World!");
    struct my_string2_type
        NK_STRING__BUCKET_T(TEST_STRING_SIZE)
    my_string2 =
    NK_STRING__BUCKET_INITIALIZER_FROM(&my_string2, "HELLO, WORLD!");

    nk_string__upper(&my_string1.string);
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(nk_string__is_equal(&my_string1.string, &my_string2.string));
#undef TEST_STRING_SIZE
}

void
test_nk_string(void)
{
    static const struct nk_testsuite__test tests[] = {
    NK_TEST__TEST(test__construction__initializer),
    NK_TEST__TEST(test__construction__initialize),
    NK_TEST__TEST(test__bucket_construction__initializer),
    NK_TEST__TEST(test__bucket_construction__initializer_from),
    NK_TEST__TEST(test__is_equal__true__same_size),
    NK_TEST__TEST(test__is_equal__true__different_size),
    NK_TEST__TEST(test__is_equal__false__same_size),
    NK_TEST__TEST(test__is_equal__false__different_size),
    NK_TEST__TEST(test__view),
    NK_TEST__TEST(test__contains__true),
    NK_TEST__TEST(test__contains__false__smaller_length),
    NK_TEST__TEST(test__contains__false__bigger_length),
    NK_TEST__TEST(test__endswith__true),
    NK_TEST__TEST(test__endswith__false__smaller_length),
    NK_TEST__TEST(test__endswith__false__bigger_length),
    NK_TEST__TEST(test__rstrip),
    NK_TEST__TEST(test__lower),
    NK_TEST__TEST(test__upper),
    NK_TEST__TEST_TERMINATE() };
    nk_test__run_fixture(tests, NULL, NULL, NK_TESTSUITE__FIXTURE_NAME(none));
}
#else /* !defined(NK_ENABLED_STRING) */
void
test_nk_string(void)
{
}
#endif /* defined(NK_ENABLED_STRING) */
