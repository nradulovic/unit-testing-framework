/*
 * test_nk_array.cpp
 *
 *  Created on: Feb 21, 2021
 *      Author: nenad
 */

#include "../nk_test.h"

#include "fff.h"
#include "eds/source/sys/eds_mem.h"
#include "eds/source/eds_object.h"

DEFINE_FFF_GLOBALS

static void * dummy_alloc(void * arg0, size_t arg1)
{
    (void)arg0;
    (void)arg1;

    return NULL;
}

static void dummy_free(void * arg0, void * arg1)
{
    (void)arg0;
    (void)arg1;
}

static void
test__eds_mem__init_NULL_1(void)
{
    /* CUT */
    struct eds_object__mem mem;

    eds_mem__init(&mem, dummy_alloc, dummy_free, NULL, 1);

    NK_TEST__EXPECT_PTR(NULL);
    NK_TEST__ACTUAL_PTR(eds_mem__context(&mem));
    NK_TEST__EXPECT_SIZE(1);
    NK_TEST__ACTUAL_SIZE(eds_mem__max_size(&mem));
}

static void
test__eds_mem__init_nNULL_M(void)
{
    /* CUT */
    struct eds_object__mem mem;
    uint32_t dummy_context;
#define DUMMY_SIZE 12345

    eds_mem__init(&mem, dummy_alloc, dummy_free, &dummy_context, DUMMY_SIZE);

    NK_TEST__EXPECT_PTR(&dummy_context);
    NK_TEST__ACTUAL_PTR(eds_mem__context(&mem));
    NK_TEST__EXPECT_SIZE(DUMMY_SIZE);
    NK_TEST__ACTUAL_SIZE(eds_mem__max_size(&mem));
#undef DUMMY_SIZE
}

static void
setup(void)
{
}

void
test_execute(void)
{
    static const struct nk_testsuite__test tests[] = {
    NK_TEST__TEST(test__eds_mem__init_NULL_1),
    NK_TEST__TEST(test__eds_mem__init_nNULL_M),
    NK_TEST__TEST_TERMINATE() };
    nk_test__run_fixture(tests, setup, NULL, NK_TESTSUITE__FIXTURE_NAME(none));
}
