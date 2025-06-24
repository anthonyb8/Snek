#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "chunk.h"
#include "cvec/cvec.h"
#include "memory.h"
#include "value.h"

// void printValue(Value* value) { printf("Value %g", *value); }

void initChunk(Chunk* chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  chunk->lines = NULL;
  vec_init(&chunk->constants, sizeof(Value));
  // initValueArray(&chunk->constants);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
  printf("Byte %u\n", byte);
  //  Extends array if at capacity
  if (chunk->capacity < chunk->count + 1) {
    int oldCapacity = chunk->capacity;
    chunk->capacity = growCapacity(oldCapacity);
    chunk->lines = (int*)memReallocate(chunk->lines, sizeof(int) * oldCapacity,
                                       sizeof(int) * chunk->capacity);
    chunk->code =
        (uint8_t*)memReallocate(chunk->code, sizeof(uint8_t) * oldCapacity,
                                sizeof(uint8_t) * chunk->capacity);
  }
  // Append chunk knowing that chunk has enough capacity.
  chunk->code[chunk->count] = byte;
  chunk->lines[chunk->count] = line;
  chunk->count++;
}

int addConstant(Chunk* chunk, Value* value) {
  vec_push(&chunk->constants, value);
  // writeValueArray(&chunk->constants, value);
  return chunk->constants.length - 1;
}

void freeChunk(Chunk* chunk) {
  freeArray(chunk->code, chunk->capacity);
  freeArray(chunk->lines, chunk->capacity);
  freeVec(&chunk->constants);
  // freeValueArray(&chunk->constants);
  initChunk(chunk);
}
