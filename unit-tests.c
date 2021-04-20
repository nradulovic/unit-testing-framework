/*
 * unit-tests.cpp
 *
 *  Created on: Feb 21, 2021
 *      Author: nenad
 */

#include <stdbool.h>
#include "nk_test.h"
#include "test_cases/test_nk_array.h"
#include "test_cases/test_nk_fqueue.h"
#include "test_cases/test_nk_string.h"
#include "test_cases/test_nk_manchester.h"
#include "test_cases/test_nk_convert.h"

int
main(int argc, char **argv)
{
    static const struct nk_testsuite__config silent_config = { .is_verbose = false, };
    static const struct nk_testsuite__config verbose_config = { .is_verbose = true, };
    if (argc == 2 && argv[1][0] == 'v') {
        nk_testsuite__setup(&verbose_config);
    } else {
        nk_testsuite__setup(&silent_config);
    }
    test_nk_array();
    test_nk_fqueue();
    test_nk_string();
    test_nk_manchester();
    test_nk_convert();

    return nk_testsuite__epilogue();
}
