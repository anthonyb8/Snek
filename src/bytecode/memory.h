#ifndef snek_memory_h
#define snek_memory_h

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "common.h"

// Reallocates a pointer, handles destruction/null pointers as needed.
void* memReallocate(void* pointer, size_t oldSize, size_t newSize);

// 8 is choosen arbitrarily
static inline int growCapacity(int capacity) {
  return (capacity < 8 ? 8 : capacity * 2);
}

static inline uint8_t* growArray(void* pointer, size_t oldSize,
                                 size_t newSize) {
  return (uint8_t*)memReallocate(pointer, oldSize, newSize);
}

// reallocates the array to 0
static inline void freeArray(void* pointer, size_t oldSize) {
  memReallocate(pointer, sizeof(uint8_t) * oldSize, 0);
}

#endif
