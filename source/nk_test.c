/*
 * nk_test.cpp
 *
 *  Created on: Feb 21, 2021
 *      Author: nenad
 */

#include <string.h>
#include <stdio.h>

#include "nk_test.h"

struct testsuite__context
{
    const struct nk_testsuite__test *test;
    struct np_testsuite_fixture
    {
        const char *name;
    } fixture;
    struct np_testsuite_test_case
    {
        union np_testsuite__test_val expected;
        enum np_testsuite__type type;
    } test_case;
    struct nk_testsuite__config config;
    bool has_failed;
    uint32_t total_tests;
    uint32_t total_asserts;
};

static struct testsuite__context g_testsuite__context;

void
nk_test__setup(const struct nk_testsuite__config *config)
{
    g_testsuite__context.config = *config;
}

void
nk_test__run_fixture(const struct nk_testsuite__test *tests,
                     void
                     (*setup)(void),
                     void
                     (*teardown)(void),
                     const char *name)
{
    if (tests == NULL) {
        return;
    }
    if (g_testsuite__context.has_failed) {
        if (g_testsuite__context.config.is_verbose) {
            printf("Skipping fixture: %s\n", g_testsuite__context.fixture.name);
        }
        return;
    }
    g_testsuite__context.fixture.name = name;
    if (g_testsuite__context.config.is_verbose) {
        printf("%s\n", g_testsuite__context.fixture.name);
    }

    for (uint32_t i = 0u; (tests[i].test_fn != NULL) && (tests[i].name != NULL); i++) {
        uint32_t asserts;

        asserts = g_testsuite__context.total_asserts;

        if (g_testsuite__context.config.is_verbose) {
            printf("  %s...", tests[i].name);
            fflush(stdout);
        }
        g_testsuite__context.test = &tests[i];
        g_testsuite__context.total_tests++;

        if (setup != NULL) {
            setup();
        }
        tests[i].test_fn();
        if (teardown != NULL) {
            teardown();
        }
        if (g_testsuite__context.has_failed) {
            break;
        }

        if (g_testsuite__context.config.is_verbose) {
            if (g_testsuite__context.total_asserts == asserts) {
                printf(" SKIPPED\n");
            } else {
                printf(" PASSED\n");
            }
        } else {
            if (g_testsuite__context.total_asserts == asserts) {
                printf("s");
            } else {
                printf(".");
            }
            fflush(stdout);
        }
    }
}

int
nk_test__epilogue(void)
{
    printf("\nTotal asserts: %u\n", g_testsuite__context.total_asserts);
    printf("Total tests  : %u\n", g_testsuite__context.total_tests);
    return g_testsuite__context.has_failed ? -1 : 0;
}

void
nk_test__p__expect(union np_testsuite__test_val value,
                   enum np_testsuite__type type)
{
    g_testsuite__context.test_case.type = type;
    g_testsuite__context.test_case.expected = value;
    g_testsuite__context.total_asserts++;
}

bool
nk_test__p__actual(uint32_t line,
                   union np_testsuite__test_val actual)
{
    switch (g_testsuite__context.test_case.type) {
    case NP_TESTSUITE__TYPE_BOOL:
        if (actual.b != g_testsuite__context.test_case.expected.b) {
            g_testsuite__context.has_failed = true;
        }
        break;
    case NP_TESTSUITE__TYPE_SIZE:
        if (actual.size != g_testsuite__context.test_case.expected.size) {
            g_testsuite__context.has_failed = true;
        }
        break;
    case NP_TESTSUITE__TYPE_UINT:
        if (actual.ui != g_testsuite__context.test_case.expected.ui) {
            g_testsuite__context.has_failed = true;
        }
        break;
    case NP_TESTSUITE__TYPE_INT:
        if (actual.si != g_testsuite__context.test_case.expected.si) {
            g_testsuite__context.has_failed = true;
        }
        break;
    case NP_TESTSUITE__TYPE_PTR:
        if (actual.ptr != g_testsuite__context.test_case.expected.ptr) {
            g_testsuite__context.has_failed = true;
        }
        break;
    case NP_TESTSUITE__TYPE_STR:
        if (strcmp(actual.str, g_testsuite__context.test_case.expected.str) != 0) {
            g_testsuite__context.has_failed = true;
        }
        break;
    case NP_TESTSUITE__TYPE_NOT_BOOL:
        if (actual.b == g_testsuite__context.test_case.expected.b) {
            g_testsuite__context.has_failed = true;
        }
        break;
    case NP_TESTSUITE__TYPE_NOT_SIZE:
        if (actual.size == g_testsuite__context.test_case.expected.size) {
            g_testsuite__context.has_failed = true;
        }
        break;
    case NP_TESTSUITE__TYPE_NOT_UINT:
        if (actual.ui == g_testsuite__context.test_case.expected.ui) {
            g_testsuite__context.has_failed = true;
        }
        break;
    case NP_TESTSUITE__TYPE_NOT_INT:
        if (actual.si == g_testsuite__context.test_case.expected.si) {
            g_testsuite__context.has_failed = true;
        }
        break;
    case NP_TESTSUITE__TYPE_NOT_PTR:
        if (actual.ptr == g_testsuite__context.test_case.expected.ptr) {
            g_testsuite__context.has_failed = true;
        }
        break;
    case NP_TESTSUITE__TYPE_NOT_STR:
        if (strcmp(actual.str, g_testsuite__context.test_case.expected.str) == 0) {
            g_testsuite__context.has_failed = true;
        }
        break;
    default:
        g_testsuite__context.has_failed = true;
        break;
    }

    if (g_testsuite__context.has_failed) {
        printf("\n\nTest FAILED at %s() in %s:%u\n",
               g_testsuite__context.test->name,
               g_testsuite__context.fixture.name,
               line);

        switch (g_testsuite__context.test_case.type) {
        case NP_TESTSUITE__TYPE_BOOL:
            printf("Expected: %u\nActual  : %u\n",
                   g_testsuite__context.test_case.expected.b,
                   actual.b);
            break;
        case NP_TESTSUITE__TYPE_SIZE:
            printf("Expected: %lu\nActual  : %lu\n",
                   g_testsuite__context.test_case.expected.size,
                   actual.size);
            break;
        case NP_TESTSUITE__TYPE_UINT:
            printf("Expected: %u (0x%x)\nActual  : %u (0x%x)\n",
                   g_testsuite__context.test_case.expected.ui,
                   g_testsuite__context.test_case.expected.ui,
                   actual.ui,
                   actual.ui);
            break;
        case NP_TESTSUITE__TYPE_INT:
            printf("Expected: %d\nActual  : %d\n",
                   g_testsuite__context.test_case.expected.si,
                   actual.si);
            break;
        case NP_TESTSUITE__TYPE_PTR:
            printf("Expected: %p\nActual  : %p\n",
                   g_testsuite__context.test_case.expected.ptr,
                   actual.ptr);
            break;
        case NP_TESTSUITE__TYPE_STR:
            printf("Expected: %s\nActual   : %s\n",
                   g_testsuite__context.test_case.expected.str,
                   actual.str);
            break;
        case NP_TESTSUITE__TYPE_NOT_BOOL:
            printf("Unexpected: %u\nActual    : %u\n",
                   g_testsuite__context.test_case.expected.b,
                   actual.b);
            break;
        case NP_TESTSUITE__TYPE_NOT_SIZE:
            printf("Unexpected: %lu\nActual    : %lu\n",
                   g_testsuite__context.test_case.expected.size,
                   actual.size);
            break;
        case NP_TESTSUITE__TYPE_NOT_UINT:
            printf("Unexpected: %u\nActual    : %u\n",
                   g_testsuite__context.test_case.expected.ui,
                   actual.ui);
            break;
        case NP_TESTSUITE__TYPE_NOT_INT:
            printf("Unexpected: %d\nActual    : %d\n",
                   g_testsuite__context.test_case.expected.si,
                   actual.si);
            break;
        case NP_TESTSUITE__TYPE_NOT_PTR:
            printf("Unexpected: %p\nActual    : %p\n",
                   g_testsuite__context.test_case.expected.ptr,
                   actual.ptr);
            break;
        case NP_TESTSUITE__TYPE_NOT_STR:
            printf("Unexpected: %s\nActual    : %s\n",
                   g_testsuite__context.test_case.expected.str,
                   actual.str);
            break;
        default:
            printf("Inconsistent test case\n");
            break;
        }
    }
    return g_testsuite__context.has_failed;
}
