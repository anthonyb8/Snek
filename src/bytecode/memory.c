#include <stdio.h>
#include <stdlib.h>

#include "memory.h"

void* memReallocate(void* pointer, size_t oldSize, size_t newSize) {
  // printf("New Size %lu\n", newSize);
  if (newSize == 0) {
    free(pointer);
    return NULL;
  }

  void* newPtr = realloc(pointer, newSize);

  if (newPtr == NULL) {
    exit(1);
  }

  return newPtr;
}
