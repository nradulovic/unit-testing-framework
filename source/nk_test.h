/*
 * nk_test.hpp
 *
 *  Created on: Feb 21, 2021
 *      Author: nenad
 */

#ifndef NK_TEST_HPP_
#define NK_TEST_HPP_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NK_TEST__TEST(test_name)                                            \
    {                                                                       \
        .test_fn = test_name,                                               \
        .name = # test_name                                                 \
    }

#define NK_TEST__TEST_TERMINATE()                                           \
    {                                                                       \
        .test_fn = NULL,                                                    \
        .name = NULL                                                        \
    }

#define NK_TEST__EXPECT_SIZE(a_number)                                      \
    do {                                                                    \
        union np_testsuite__test_val val;                                   \
        val.size = (a_number);                                              \
        nk_test__p__expect(val, NP_TESTSUITE__TYPE_SIZE);                   \
    } while (0)

#define NK_TEST__EXPECT_UINT(a_number)                                      \
    do {                                                                    \
        union np_testsuite__test_val val;                                   \
        val.ui = (a_number);                                                \
        nk_test__p__expect(val, NP_TESTSUITE__TYPE_UINT);                   \
    } while (0)

#define NK_TEST__EXPECT_INT(a_number)                                       \
    do {                                                                    \
        union np_testsuite__test_val val;                                   \
        val.si = (a_number);                                                \
        nk_test__p__expect(val, NP_TESTSUITE__TYPE_INT);                    \
    } while (0)

#define NK_TEST__EXPECT_PTR(a_pointer)                                      \
    do {                                                                    \
        union np_testsuite__test_val val;                                   \
        val.ptr = (a_pointer);                                              \
        nk_test__p__expect(val, NP_TESTSUITE__TYPE_PTR);                    \
    } while (0)

#define NK_TEST__EXPECT_STR(a_string)                                       \
    do {                                                                    \
        union np_testsuite__test_val val;                                   \
        val.str = (a_string);                                               \
        nk_test__p__expect(val, NP_TESTSUITE__TYPE_STR);                    \
    } while (0)

#define NK_TEST__EXPECT_BOOL(a_bool)                                        \
    do {                                                                    \
        union np_testsuite__test_val val;                                   \
        val.b = (a_bool);                                                   \
        nk_test__p__expect(val, NP_TESTSUITE__TYPE_BOOL);                   \
    } while (0)

#define NK_TESTSUITE__NOT_EXPECT_SIZE(a_number)                             \
    do {                                                                    \
        union np_testsuite__test_val val;                                   \
        val.size = (a_number);                                              \
        nk_test__p__expect(val, NP_TESTSUITE__TYPE_NOT_SIZE);               \
    } while (0)

#define NK_TESTSUITE__NOT_EXPECT_UINT(a_number)                             \
    do {                                                                    \
        union np_testsuite__test_val val;                                   \
        val.ui = (a_number);                                                \
        nk_test__p__expect(val, NP_TESTSUITE__TYPE_NOT_UINT);               \
    } while (0)

#define NK_TESTSUITE__NOT_EXPECT_INT(a_number)                              \
    do {                                                                    \
        union np_testsuite__test_val val;                                   \
        val.si = (a_number);                                                \
        nk_test__p__expect(val, NP_TESTSUITE__TYPE_NOT_INT);                \
    } while (0)

#define NK_TESTSUITE__NOT_EXPECT_PTR(a_pointer)                             \
    do {                                                                    \
        union np_testsuite__test_val val;                                   \
        val.ptr = (a_pointer);                                              \
        nk_test__p__expect(val, NP_TESTSUITE__TYPE_NOT_PTR);                \
    } while (0)

#define NK_TESTSUITE__NOT_EXPECT_STR(a_string)                              \
    do {                                                                    \
        union np_testsuite__test_val val;                                   \
        val.str = (a_string);                                               \
        nk_test__p__expect(val, NP_TESTSUITE__TYPE_NOT_STR);                \
    } while (0)

#define NK_TESTSUITE__NOT_EXPECT_BOOL(a_bool)                               \
    do {                                                                    \
        union np_testsuite__test_val val;                                   \
        val.b = (a_bool);                                                   \
        nk_test__p__expect(val, NP_TESTSUITE__TYPE_NOT_BOOL);               \
    } while (0)

#define NK_TEST__ACTUAL_SIZE(a_number)                                      \
    do {                                                                    \
        union np_testsuite__test_val val;                                   \
        val.size = (a_number);                                              \
        if (nk_test__p__actual(__LINE__, (val))) {                          \
            return;                                                         \
        }                                                                   \
    } while (0)

#define NK_TEST__ACTUAL_UINT(a_number)                                      \
    do {                                                                    \
        union np_testsuite__test_val val;                                   \
        val.ui = (a_number);                                                \
        if (nk_test__p__actual(__LINE__, (val))) {                          \
            return;                                                         \
        }                                                                   \
    } while (0)

#define NK_TEST__ACTUAL_INT(a_number)                                       \
    do {                                                                    \
        union np_testsuite__test_val val;                                   \
        val.si = (a_number);                                                \
        if (nk_test__p__actual(__LINE__, (val))) {                          \
            return;                                                         \
        }                                                                   \
    } while (0)

#define NK_TEST__ACTUAL_PTR(a_pointer)                                      \
    do {                                                                    \
        union np_testsuite__test_val val;                                   \
        val.ptr = (a_pointer);                                              \
        if (nk_test__p__actual(__LINE__, (val))) {                          \
            return;                                                         \
        }                                                                   \
    } while (0)

#define NK_TEST__ACTUAL_STR(a_string)                                       \
    do {                                                                    \
        union np_testsuite__test_val val;                                   \
        val.str = (a_string);                                               \
        if (nk_test__p__actual(__LINE__, (val))) {                          \
            return;                                                         \
        }                                                                   \
    } while (0)

#define NK_TEST__ACTUAL_BOOL(a_bool)                                        \
    do {                                                                    \
        union np_testsuite__test_val val;                                   \
        val.b = (a_bool);                                                   \
        if (nk_test__p__actual(__LINE__, (val))) {                          \
            return;                                                         \
        }                                                                   \
    } while (0)

#define NK_TESTSUITE__FIXTURE_NAME(a_name)                                  \
        __FILE__ ":" # a_name

enum np_testsuite__type
{
    NP_TESTSUITE__TYPE_SIZE,
    NP_TESTSUITE__TYPE_UINT,
    NP_TESTSUITE__TYPE_INT,
    NP_TESTSUITE__TYPE_PTR,
    NP_TESTSUITE__TYPE_BOOL,
    NP_TESTSUITE__TYPE_STR,
    NP_TESTSUITE__TYPE_NOT_SIZE,
    NP_TESTSUITE__TYPE_NOT_UINT,
    NP_TESTSUITE__TYPE_NOT_INT,
    NP_TESTSUITE__TYPE_NOT_PTR,
    NP_TESTSUITE__TYPE_NOT_BOOL,
    NP_TESTSUITE__TYPE_NOT_STR,
};

struct nk_testsuite__config
{
    bool is_verbose;
};

struct nk_testsuite__test
{
    void
    (*test_fn)(void);
    const char *name;
};

union np_testsuite__test_val
{
    size_t size;
    uint32_t ui;
    int32_t si;
    const void *ptr;
    const char *str;
    bool b;
};

void
nk_test__setup(const struct nk_testsuite__config *config);

void
nk_test__run_fixture(const struct nk_testsuite__test *array,
                     void
                     (*setup)(void),
                     void
                     (*teardown)(void),
                     const char *name);

int
nk_test__epilogue(void);

void
nk_test__p__expect(union np_testsuite__test_val value,
                   enum np_testsuite__type type);

bool
nk_test__p__actual(uint32_t line,
                   union np_testsuite__test_val value);

extern void
nk_test__execute(void);

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */

#endif /* NK_TEST_HPP_ */
