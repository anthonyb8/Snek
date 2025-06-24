#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
// Third party
#include <cmocka.h>

// #include "compiler/chunk.h"

extern const struct CMUnitTest memory_tests[];
extern const size_t memory_tests_count;

extern const struct CMUnitTest chunk_tests[];
extern const size_t chunk_tests_count;

int main(void) {
  // char testing[] = "hello";
  // printf("%s\n", testing);
  int failures = 0;

  failures += _cmocka_run_group_tests("memory_tests", memory_tests,
                                      memory_tests_count, NULL, NULL);

  failures += _cmocka_run_group_tests("chunk_tests", chunk_tests,
                                      chunk_tests_count, NULL, NULL);

  return failures;
}
