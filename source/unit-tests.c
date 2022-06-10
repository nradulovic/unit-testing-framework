/*
 * unit-tests.cpp
 *
 *  Created on: Feb 21, 2021
 *      Author: nenad
 */

#include "unit-tests.h"
#include "nk_test.h"

int
main(int argc,
     char **argv)
{
    static const struct nk_testsuite__config silent_config =
    { .is_verbose = false, };
    static const struct nk_testsuite__config verbose_config =
    { .is_verbose = true, };
    if (argc == 2 && argv[1][0] == 'v') {
        nk_test__setup(&verbose_config);
    } else {
        nk_test__setup(&silent_config);
    }
    nk_test__execute();

    return nk_test__epilogue();
}
