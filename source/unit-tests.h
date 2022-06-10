/*
 * unit-tests.h
 *
 *  Created on: Nov 17, 2021
 *      Author: Nenad.Radulovic
 */

#ifndef TESTS_UNIT_TESTS_H_
#define TESTS_UNIT_TESTS_H_

#include <stddef.h>

typedef void
(*test_t)(void);

extern const test_t g__enabled_tests[];
extern const size_t g__n_tests;

#endif /* TESTS_UNIT_TESTS_H_ */
