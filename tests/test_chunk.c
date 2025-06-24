#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
// Third party
#include <cmocka.h>

// #include "lib.h"

static void test_add2(void **state) {
  (void)state;
  assert_int_equal(10, 10);
  // assert_int_equal(add(2, 3), 5);
  // assert_int_equal(add(-1, 1), 0);
}

// Group Tests
const struct CMUnitTest chunk_tests[] = {cmocka_unit_test(test_add2)};
const size_t chunk_tests_count = sizeof(chunk_tests) / sizeof(chunk_tests[0]);
