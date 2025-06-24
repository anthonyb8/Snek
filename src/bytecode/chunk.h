#ifndef snek_chunk_h
#define snek_chunk_h

#include <stdint.h>

#include "common.h"
#include "cvec/cvec.h"
#include "value.h"

// Each bytecode instruction has a one-byte operation code (opcode)
// to indicate the type of action being handled
typedef enum {
  OP_RETURN,
  OP_NIL,
  OP_TRUE,
  OP_FALSE,
  OP_NEGATE,
  OP_ADD,
  OP_SUBTRACT,
  OP_MULTIPLY,
  OP_DIVIDE,
  OP_CONSTANT
} OpCode;

// Represents a 'chunk' of bytecode, implemented as a dynamic array.
typedef struct {
  int count;      // used elements in array
  int capacity;   // number of elements in array
  uint8_t* code;  // bytes
  int* lines;     // line number array
  Vec constants;  // Constants, dynamic array.
} Chunk;

// Initializer for Chunk struct.
void initChunk(Chunk* chunk);

// Append bytecode block to Chunk array, with line in source.
void writeChunk(Chunk* chunk, uint8_t byte, int line);

// Add a constant to the Constants array
int addConstant(Chunk* chunk, Value* value);

// Destroy Chunk struct.
void freeChunk(Chunk* chunk);

#endif
