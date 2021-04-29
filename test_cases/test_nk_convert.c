/*
 * test_nk_convert.c
 *
 *  Created on: Apr 19, 2021
 *      Author: nenad
 */

#include "../nk_test.h"
#include "test_nk_convert.h"
#include "generic/nk_string.h"
#include "generic/convert/nk_convert.h"

static void
test__str_to_u32__number(void)
{
    struct test_string_type
        NK_STRING__BUCKET_T(20)
    test_string = NK_STRING__BUCKET_INITIALIZER(&test_string, "123");

    struct nk_convert__str_to_u32__result result;

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

    struct nk_convert__str_to_u32__result result;

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

    struct nk_convert__str_to_u32__result result;

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

    struct nk_convert__str_to_u32__result result;

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

    struct nk_convert__str_to_u32__result result;

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
