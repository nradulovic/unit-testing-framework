/*
 * test_nk_manchester.c
 *
 *  Created on: Apr 13, 2021
 *      Author: nenad
 */

#include "../nk_test.h"
#include "test_nk_manchester.h"
#include "generic/nk_array.h"
#include "generic/nk_types.h"
#include "generic/codec/nk_manchester.h"

#if defined(NK_ENABLED_MANCHESTER)

static void
test__encode(void)
{
    struct source
        NK_ARRAY__BUCKET_TYPED_T(uint8_t, 20, struct nk_types__array__u8)
    source_data =
    NK_ARRAY__BUCKET_INITIALIZER_WITH(&source_data, 4, {0, 1, 2, 3});
    struct destination
        NK_ARRAY__BUCKET_TYPED_T(bool, 320, struct nk_types__array__bool)
    destination_data =
    NK_ARRAY__BUCKET_INITIALIZER(&destination_data);

    enum nk_error error = nk_manchester__encode__biphasel(&source_data.array, &destination_data.array);

    NK_TEST__EXPECT_INT((int ) NK_ERROR__OK);
    NK_TEST__ACTUAL_INT((int ) error);
    NK_TEST__EXPECT_SIZE(4 * 16);
    NK_TEST__ACTUAL_SIZE(destination_data.array.length);

    /* Byte 0, bit 7 */
    NK_TEST__EXPECT_BOOL(false);
    NK_TEST__ACTUAL_BOOL(destination_data.array.items[0]);
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(destination_data.array.items[1]);
    /* Byte 0, bit 6 */
    NK_TEST__EXPECT_BOOL(false);
    NK_TEST__ACTUAL_BOOL(destination_data.array.items[2]);
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(destination_data.array.items[3]);
    /* Byte 0, bit 5 */
    NK_TEST__EXPECT_BOOL(false);
    NK_TEST__ACTUAL_BOOL(destination_data.array.items[4]);
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(destination_data.array.items[5]);
    /* Byte 0, bit 4 */
    NK_TEST__EXPECT_BOOL(false);
    NK_TEST__ACTUAL_BOOL(destination_data.array.items[6]);
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(destination_data.array.items[7]);

    /* Byte 1, bit 3 */
    NK_TEST__EXPECT_BOOL(false);
    NK_TEST__ACTUAL_BOOL(destination_data.array.items[16 + 8]);
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(destination_data.array.items[16 + 9]);
    /* Byte 1, bit 2 */
    NK_TEST__EXPECT_BOOL(false);
    NK_TEST__ACTUAL_BOOL(destination_data.array.items[16 + 10]);
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(destination_data.array.items[16 + 11]);
    /* Byte 1, bit 1 */
    NK_TEST__EXPECT_BOOL(false);
    NK_TEST__ACTUAL_BOOL(destination_data.array.items[16 + 12]);
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(destination_data.array.items[16 + 13]);
    /* Byte 1, bit 0 */
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(destination_data.array.items[16 + 14]);
    NK_TEST__EXPECT_BOOL(false);
    NK_TEST__ACTUAL_BOOL(destination_data.array.items[16 + 15]);

    /* Byte 2, bit 3 */
    NK_TEST__EXPECT_BOOL(false);
    NK_TEST__ACTUAL_BOOL(destination_data.array.items[32 + 8]);
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(destination_data.array.items[32 + 9]);
    /* Byte 2, bit 2 */
    NK_TEST__EXPECT_BOOL(false);
    NK_TEST__ACTUAL_BOOL(destination_data.array.items[32 + 10]);
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(destination_data.array.items[32 + 11]);
    /* Byte 2, bit 1 */
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(destination_data.array.items[32 + 12]);
    NK_TEST__EXPECT_BOOL(false);
    NK_TEST__ACTUAL_BOOL(destination_data.array.items[32 + 13]);
    /* Byte 2, bit 0 */
    NK_TEST__EXPECT_BOOL(false);
    NK_TEST__ACTUAL_BOOL(destination_data.array.items[32 + 14]);
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(destination_data.array.items[32 + 15]);

    /* Byte 3, bit 3 */
    NK_TEST__EXPECT_BOOL(false);
    NK_TEST__ACTUAL_BOOL(destination_data.array.items[48 + 8]);
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(destination_data.array.items[48 + 9]);
    /* Byte 3, bit 2 */
    NK_TEST__EXPECT_BOOL(false);
    NK_TEST__ACTUAL_BOOL(destination_data.array.items[48 + 10]);
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(destination_data.array.items[48 + 11]);
    /* Byte 3, bit 1 */
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(destination_data.array.items[48 + 12]);
    NK_TEST__EXPECT_BOOL(false);
    NK_TEST__ACTUAL_BOOL(destination_data.array.items[48 + 13]);
    /* Byte 3, bit 0 */
    NK_TEST__EXPECT_BOOL(true);
    NK_TEST__ACTUAL_BOOL(destination_data.array.items[48 + 14]);
    NK_TEST__EXPECT_BOOL(false);
    NK_TEST__ACTUAL_BOOL(destination_data.array.items[48 + 15]);
}

static void
test__decode_half_byte(void)
{
    struct source
        NK_ARRAY__BUCKET_TYPED_T(bool, 16, struct nk_types__array__bool)
    source_data =
    NK_ARRAY__BUCKET_INITIALIZER_WITH(&source_data, 8, {false, true, true, false, false, true, true, false});
    struct destination
        NK_ARRAY__BUCKET_TYPED_T(uint8_t, 8, struct nk_types__array__u8)
    destination_data = NK_ARRAY__BUCKET_INITIALIZER(&destination_data);

    enum nk_error error = nk_manchester__decode__biphasel(&source_data.array, &destination_data.array);

    NK_TEST__EXPECT_INT((int ) NK_ERROR__OK);
    NK_TEST__ACTUAL_INT((int ) error);
    NK_TEST__EXPECT_SIZE(1u);
    NK_TEST__ACTUAL_SIZE(destination_data.array.length);
    NK_TEST__EXPECT_UINT(0x50);
    NK_TEST__ACTUAL_UINT(destination_data.array.items[0]);
}

static void
test__decode(void)
{
    struct source
        NK_ARRAY__BUCKET_TYPED_T(bool, 16, struct nk_types__array__bool)
    source_data =
    NK_ARRAY__BUCKET_INITIALIZER_WITH(&source_data, 16,
    {
        false, true,    /* 0 */
        true, false,    /* 1 */
        false, true,    /* 0 */
        true, false,    /* 1 */
        false, true,    /* 0 */
        false, true,    /* 0 */
        false, true,    /* 0 */
        true,  false}); /* 1 */
    struct destination
        NK_ARRAY__BUCKET_TYPED_T(uint8_t, 8, struct nk_types__array__u8)
    destination_data = NK_ARRAY__BUCKET_INITIALIZER(&destination_data);

    enum nk_error error = nk_manchester__decode__biphasel(&source_data.array, &destination_data.array);

    NK_TEST__EXPECT_INT((int ) NK_ERROR__OK);
    NK_TEST__ACTUAL_INT((int ) error);
    NK_TEST__EXPECT_SIZE(1u);
    NK_TEST__ACTUAL_SIZE(destination_data.array.length);
    NK_TEST__EXPECT_UINT(0x51);
    NK_TEST__ACTUAL_UINT(destination_data.array.items[0]);
}

static void
test__decode_invalid_bit0_false(void)
{
    struct source
        NK_ARRAY__BUCKET_TYPED_T(bool, 16, struct nk_types__array__bool)
    source_data =
    NK_ARRAY__BUCKET_INITIALIZER_WITH(&source_data, 16,
    {
        false, false,   /* invalid */
        true, false,    /* 1 */
        false, true,    /* 0 */
        true, false,    /* 1 */
        false, true,    /* 0 */
        false, true,    /* 0 */
        false, true,    /* 0 */
        true,  false}); /* 1 */
    struct destination
        NK_ARRAY__BUCKET_TYPED_T(uint8_t, 8, struct nk_types__array__u8)
    destination_data = NK_ARRAY__BUCKET_INITIALIZER(&destination_data);

    enum nk_error error = nk_manchester__decode__biphasel(&source_data.array, &destination_data.array);

    NK_TEST__EXPECT_INT((int ) NK_ERROR__DATA_INVALID);
    NK_TEST__ACTUAL_INT((int ) error);
    NK_TEST__EXPECT_SIZE(0u);
    NK_TEST__ACTUAL_SIZE(destination_data.array.length);
}

static void
test__decode_invalid_bit0_true(void)
{
    struct source
        NK_ARRAY__BUCKET_TYPED_T(bool, 16, struct nk_types__array__bool)
    source_data =
    NK_ARRAY__BUCKET_INITIALIZER_WITH(&source_data, 16,
    {
        true, true,     /* invalid */
        true, false,    /* 1 */
        false, true,    /* 0 */
        true, false,    /* 1 */
        false, true,    /* 0 */
        false, true,    /* 0 */
        false, true,    /* 0 */
        true,  false}); /* 1 */
    struct destination
        NK_ARRAY__BUCKET_TYPED_T(uint8_t, 8, struct nk_types__array__u8)
    destination_data = NK_ARRAY__BUCKET_INITIALIZER(&destination_data);

    enum nk_error error = nk_manchester__decode__biphasel(&source_data.array, &destination_data.array);

    NK_TEST__EXPECT_INT((int ) NK_ERROR__DATA_INVALID);
    NK_TEST__ACTUAL_INT((int ) error);
    NK_TEST__EXPECT_SIZE(0u);
    NK_TEST__ACTUAL_SIZE(destination_data.array.length);
}

static void
test__decode_invalid_bit1_false(void)
{
    struct source
        NK_ARRAY__BUCKET_TYPED_T(bool, 16, struct nk_types__array__bool)
    source_data =
    NK_ARRAY__BUCKET_INITIALIZER_WITH(&source_data, 16,
    {
        false, true,    /* 0 */
        false, false,   /* invalid */
        false, true,    /* 0 */
        true, false,    /* 1 */
        false, true,    /* 0 */
        false, true,    /* 0 */
        false, true,    /* 0 */
        true,  false}); /* 1 */
    struct destination
        NK_ARRAY__BUCKET_TYPED_T(uint8_t, 8, struct nk_types__array__u8)
    destination_data = NK_ARRAY__BUCKET_INITIALIZER(&destination_data);

    enum nk_error error = nk_manchester__decode__biphasel(&source_data.array, &destination_data.array);

    NK_TEST__EXPECT_INT((int ) NK_ERROR__DATA_INVALID);
    NK_TEST__ACTUAL_INT((int ) error);
    NK_TEST__EXPECT_SIZE(0u);
    NK_TEST__ACTUAL_SIZE(destination_data.array.length);
}

static void
test__decode_invalid_bit1_true(void)
{
    struct source
        NK_ARRAY__BUCKET_TYPED_T(bool, 16, struct nk_types__array__bool)
    source_data =
    NK_ARRAY__BUCKET_INITIALIZER_WITH(&source_data, 16,
    {
        false, true,    /* 0 */
        true, true,     /* invalid */
        false, true,    /* 0 */
        true, false,    /* 1 */
        false, true,    /* 0 */
        false, true,    /* 0 */
        false, true,    /* 0 */
        true,  false}); /* 1 */
    struct destination
        NK_ARRAY__BUCKET_TYPED_T(uint8_t, 8, struct nk_types__array__u8)
    destination_data = NK_ARRAY__BUCKET_INITIALIZER(&destination_data);

    enum nk_error error = nk_manchester__decode__biphasel(&source_data.array, &destination_data.array);

    NK_TEST__EXPECT_INT((int ) NK_ERROR__DATA_INVALID);
    NK_TEST__ACTUAL_INT((int ) error);
    NK_TEST__EXPECT_SIZE(0u);
    NK_TEST__ACTUAL_SIZE(destination_data.array.length);
}

void
test_nk_manchester(void)
{
    static const struct nk_testsuite__test tests[] = {
    NK_TEST__TEST(test__encode),
    NK_TEST__TEST(test__decode_half_byte),
    NK_TEST__TEST(test__decode),
    NK_TEST__TEST(test__decode_invalid_bit0_false),
    NK_TEST__TEST(test__decode_invalid_bit0_true),
    NK_TEST__TEST(test__decode_invalid_bit1_false),
    NK_TEST__TEST(test__decode_invalid_bit1_true),
    NK_TEST__TEST_TERMINATE() };
    nk_test__run_fixture(tests, NULL, NULL, NK_TESTSUITE__FIXTURE_NAME(none));
}

#else /* !defined(NK_ENABLED_MANCHESTER) */
void
test_nk_manchester(void)
{
}
#endif /* !defined(NK_ENABLED_MANCHESTER) */