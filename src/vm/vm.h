#ifndef clox_vm_h
#define clox_vm_h

#include <stdint.h>
#include <stdio.h>

#include "bytecode/chunk.h"
// #include "bytecode/debug.h"
#include "bytecode/value.h"

#define STACK_MAX 256

// Responses from the VM after interpreting a chunk of bytecode
typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR,
} InterpretResult;

// Excution engine. (IP: Potentially be moved to a Chunk).
typedef struct {
  Chunk* chunk;  //  Chunk currently being executed
  uint8_t* ip;   // instruction pointer, points to next byte to be execuated
  Value stack[STACK_MAX];
  Value* stackTop;
} VM;

void initVM(VM* vm);
void freeVM(VM* vm);

InterpretResult interpret(const char* source, VM* vm);
void push(Value value, VM* vm);
Value pop(VM* vm);

#endif  // !clox_vm_h
