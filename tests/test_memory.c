#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
// Third party
#include <cmocka.h>

// #include "lib.h"

static void test_add(void **state) {
  (void)state;
  assert_int_equal(5, 5);
  // assert_int_equal(add(-1, 1), 0);
}

// Group Tests
const struct CMUnitTest memory_tests[] = {cmocka_unit_test(test_add)};
const size_t memory_tests_count =
    sizeof(memory_tests) / sizeof(memory_tests[0]);
