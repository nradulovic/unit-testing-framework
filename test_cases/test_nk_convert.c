/*
 * test_nk_convert.c
 *
 *  Created on: Apr 19, 2021
 *      Author: nenad
 */

#include "../nk_test.h"
#include "test_nk_convert.h"
#include "generic/nk_string.h"
#include "generic/nk_farray.h"
#include "generic/convert/nk_convert.h"

static void
test__hex_to_bin__valid(void)
{
    struct test_value
    {
        struct nk_convert__hex hex;
        uint8_t value;
    };
    struct test_values NK_FARRAY__T(struct test_value, 16) test_values =
    {
        .items = {
            {
                .hex = {'0', '0'},
                .value = 0,
            },
            {
                .hex = {'0', '1'},
                .value = 1,
            },
            {
                .hex = {'0', '2'},
                .value = 2,
            },
            {
                .hex = {'0', '3'},
                .value = 3,
            },
            {
                .hex = {'0', 'e'},
                .value = 14,
            },
            {
                .hex = {'0', 'f'},
                .value = 15,
            },
            {
                .hex = {'1', '0'},
                .value = 16,
            },
            {
                .hex = {'1', '1'},
                .value = 17,
            },
            {
                .hex = {'1', '2'},
                .value = 18,
            },
            {
                .hex = {'1', '3'},
                .value = 19,
            },
            {
                .hex = {'1', 'f'},
                .value = 31,
            },
            {
                .hex = {'2', 'f'},
                .value = 47,
            },
            {
                .hex = {'3', 'f'},
                .value = 63,
            },
            {
                .hex = {'4', 'f'},
                .value = 79,
            },
            {
                .hex = {'e', 'f'},
                .value = 239,
            },
            {
                .hex = {'f', 'f'},
                .value = 255,
            },
        }
    };

    for (size_t i = 0; i < NK_FARRAY__LENGTH(&test_values); i++) {
        struct nk_result__u8 result;
        result = nk_convert__hex_to_bin(test_values.items[i].hex);

        NK_TEST__EXPECT_INT((int) NK_ERROR__OK);
        NK_TEST__ACTUAL_INT((int) result.error);
        NK_TEST__EXPECT_UINT(test_values.items[i].value);
        NK_TEST__ACTUAL_UINT(result.value);
    }
}

static void
test__hex_to_bin__invalid(void)
{
    struct test_values NK_FARRAY__T(struct nk_convert__hex, 16) test_values =
    {
        .items = {
            {'0', 'g'},
            {'0', 'h'},
            {'0', 'i'},
            {'0', 'j'},
            {'0', '-'},
            {'0', '!'},
            {'g', '0'},
            {'h', '1'},
            {'i', '2'},
            {'j', '3'},
            {'-', 'f'},
            {'-', 'f'},
            {'!', 'f'},
            {'@', '#'},
            {'%', '^'},
            {'&', '('},
        }
    };

    for (size_t i = 0; i < NK_FARRAY__LENGTH(&test_values); i++) {
        struct nk_result__u8 result;
        result = nk_convert__hex_to_bin(test_values.items[i]);

        NK_TEST__EXPECT_INT((int) NK_ERROR__DATA_INVALID);
        NK_TEST__ACTUAL_INT((int) result.error);
    }
}

static void
test__bin_to_hex(void)
{
    struct test_value
    {
        uint8_t bin;
        struct nk_convert__hex hex;
    };
    struct test_values NK_FARRAY__T(struct test_value, 16) test_values =
    {
        .items =
        {
            {
                .bin = 0,
                .hex = {'0', '0'}
            },
            {
                .bin = 1,
                .hex = {'0', '1'}
            },
            {
                .bin = 2,
                .hex = {'0', '2'}
            },
            {
                .bin = 3,
                .hex = {'0', '3'}
            },
            {
                .bin = 14,
                .hex = {'0', 'e'}
            },
            {
                .bin = 15,
                .hex = {'0', 'f'}
            },
            {
                .bin = 16,
                .hex = {'1', '0'}
            },
            {
                .bin = 17,
                .hex = {'1', '1'}
            },
            {
                .bin = 18,
                .hex = {'1', '2'}
            },
            {
                .bin = 19,
                .hex = {'1', '3'}
            },
            {
                .bin = 31,
                .hex = {'1', 'f'}
            },
            {
                .bin = 47,
                .hex = {'2', 'f'}
            },
            {
                .bin = 63,
                .hex = {'3', 'f'}
            },
            {
                .bin = 79,
                .hex = {'4', 'f'}
            },
            {
                .bin = 239,
                .hex = {'e', 'f'}
            },
            {
                .bin = 255,
                .hex = {'f', 'f'}
            }
        }
    };
    for (size_t i = 0u; i < NK_FARRAY__LENGTH(&test_values); i++) {
        struct nk_convert__hex result = nk_convert__bin_to_hex(test_values.items[i].bin);

        NK_TEST__EXPECT_INT(test_values.items[i].hex.msb);
        NK_TEST__ACTUAL_INT(result.msb);
        NK_TEST__EXPECT_INT(test_values.items[i].hex.lsb);
        NK_TEST__ACTUAL_INT(result.lsb);
    }
}

static void
test__str_to_u32__number(void)
{
    struct test_string_type
        NK_STRING__BUCKET_T(20)
    test_string = NK_STRING__BUCKET_INITIALIZER(&test_string, "123");

    struct nk_result__u32 result;

    result = nk_convert__str_to_u32(&test_string.array);

    NK_TEST__EXPECT_INT((int) NK_ERROR__OK);
    NK_TEST__ACTUAL_INT((int) result.error);
    NK_TEST__EXPECT_UINT(123u);
    NK_TEST__ACTUAL_UINT(result.value);
}

static void
test__str_to_u32__number_with_text(void)
{
    struct test_string_type
        NK_STRING__BUCKET_T(20)
    test_string = NK_STRING__BUCKET_INITIALIZER(&test_string, "12345some text");

    struct nk_result__u32 result;

    result = nk_convert__str_to_u32(&test_string.array);

    NK_TEST__EXPECT_INT((int) NK_ERROR__OK);
    NK_TEST__ACTUAL_INT((int) result.error);
    NK_TEST__EXPECT_UINT(12345u);
    NK_TEST__ACTUAL_UINT(result.value);
}


static void
test__str_to_u32__number_with_spaces(void)
{
    struct test_string_type
        NK_STRING__BUCKET_T(20)
    test_string = NK_STRING__BUCKET_INITIALIZER(&test_string, "  4445text");

    struct nk_result__u32 result;

    result = nk_convert__str_to_u32(&test_string.array);

    NK_TEST__EXPECT_INT((int) NK_ERROR__OK);
    NK_TEST__ACTUAL_INT((int) result.error);
    NK_TEST__EXPECT_UINT(4445u);
    NK_TEST__ACTUAL_UINT(result.value);
}

static void
test__str_to_u32__numbers(void)
{
    struct test_string_type
        NK_STRING__BUCKET_T(20)
    test_string = NK_STRING__BUCKET_INITIALIZER(&test_string, "44455 123");

    struct nk_result__u32 result;

    result = nk_convert__str_to_u32(&test_string.array);

    NK_TEST__EXPECT_INT((int) NK_ERROR__OK);
    NK_TEST__ACTUAL_INT((int) result.error);
    NK_TEST__EXPECT_UINT(44455u);
    NK_TEST__ACTUAL_UINT(result.value);
}

static void
test__str_to_u32__no_numbers(void)
{
    struct test_string_type
        NK_STRING__BUCKET_T(20)
    test_string = NK_STRING__BUCKET_INITIALIZER(&test_string, "some text");

    struct nk_result__u32 result;

    result = nk_convert__str_to_u32(&test_string.array);

    NK_TEST__EXPECT_INT((int) NK_ERROR__OK);
    NK_TEST__ACTUAL_INT((int) result.error);
    NK_TEST__EXPECT_UINT(0u);
    NK_TEST__ACTUAL_UINT(result.value);
}

#if defined(NK_ENABLED_CONVERT)
void
test_nk_convert(void)
{
    static const struct nk_testsuite__test tests[] = {
    NK_TEST__TEST(test__hex_to_bin__valid),
    NK_TEST__TEST(test__hex_to_bin__invalid),
    NK_TEST__TEST(test__bin_to_hex),
    NK_TEST__TEST(test__str_to_u32__number),
    NK_TEST__TEST(test__str_to_u32__number_with_text),
    NK_TEST__TEST(test__str_to_u32__number_with_spaces),
    NK_TEST__TEST(test__str_to_u32__numbers),
    NK_TEST__TEST(test__str_to_u32__no_numbers),
    NK_TEST__TEST_TERMINATE() };
    nk_test__run_fixture(tests, NULL, NULL, NK_TESTSUITE__FIXTURE_NAME(none));
}
#else /* !defined(NK_ENABLED_CONVERT) */
void
test_nk_convert(void)
{
}
#endif /* !defined(NK_ENABLED_CONVERT) */
