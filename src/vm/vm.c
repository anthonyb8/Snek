#include <stdarg.h>
#include <stdio.h>

#include "bytecode/chunk.h"
#include "bytecode/debug.h"
#include "bytecode/value.h"
#include "compiler/compiler.h"
#include "vm.h"

#ifdef DEBUG_TRACE_EXECUTION
void debug_trace(VM* vm) {
  printf("          ");
  for (Value* slot = vm->stack; slot < vm->stackTop; slot++) {
    printf("[ ");
    printValue(slot);
    printf(" ]");
  }
  printf("\n");
  disassembleInstruction(vm->chunk, (int)(vm->ip - vm->chunk->code));
}
#else
static inline void debug_trace(VM* vm) { (void)vm; };
#endif

static void resetStack(VM* vm) { vm->stackTop = vm->stack; };
static Value peek(int distance, VM* vm) { return vm->stackTop[-1 - distance]; }

static void runtimeError(VM* vm, const char* format, ...) {
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
  fputs("\n", stderr);

  size_t instruction = vm->ip - vm->chunk->code - 1;
  int line = vm->chunk->lines[instruction];
  fprintf(stderr, "[line %d] in script\n", line);
  resetStack(vm);
}

void initVM(VM* vm) { resetStack(vm); }
void freeVM(VM* vm) {}

// Core of the VM,
static InterpretResult run(VM* vm) {
#define BINARY_OP(valueType, op, vm)                          \
  do {                                                        \
    if (!IS_NUMBER(peek(0, vm)) || !IS_NUMBER(peek(1, vm))) { \
      runtimeError(vm, "Operands must be numbers.");          \
      return INTERPRET_RUNTIME_ERROR;                         \
    }                                                         \
    double b = AS_NUMBER(pop(vm));                            \
    double a = AS_NUMBER(pop(vm));                            \
    push(valueType(a op b), vm);                              \
  } while (false)

  for (;;) {
    debug_trace(vm);

    uint8_t instruction;
    switch (instruction = *vm->ip++) {
      case OP_CONSTANT: {
        Value constant = *(Value*)vec_get(&vm->chunk->constants, *vm->ip++);
        ;
        push(constant, vm);
        break;
      }
      case OP_ADD:
        BINARY_OP(NUMBER_VAL, +, vm);
        break;
      case OP_SUBTRACT:
        BINARY_OP(NUMBER_VAL, -, vm);
        break;
      case OP_MULTIPLY:
        BINARY_OP(NUMBER_VAL, *, vm);
        break;
      case OP_DIVIDE:
        BINARY_OP(NUMBER_VAL, /, vm);
        break;
      case OP_NEGATE:
        if (!IS_NUMBER(peek(0, vm))) {
          runtimeError(vm, "Operand must be a number.");
          return INTERPRET_RUNTIME_ERROR;
        }
        push(NUMBER_VAL(-AS_NUMBER(pop(vm))), vm);
        // push(-pop(vm), vm);
        break;
      case OP_RETURN: {
        Value v = pop(vm);
        printValue(&v);
        printf("\n");
        return INTERPRET_OK;
      }
    }
  }

#undef BINARY_OP
}

InterpretResult interpret(const char* source, VM* vm) {
  Chunk chunk;
  initChunk(&chunk);

  if (!compile(source, &chunk)) {
    freeChunk(&chunk);
    return INTERPRET_COMPILE_ERROR;
  }
  vm->chunk = &chunk;
  vm->ip = vm->chunk->code;

  InterpretResult result = run(vm);

  freeChunk(&chunk);
  return result;
}

// InterpretResult interpret(const char* source, VM* vm) {
//   Chunk chunk;
//   initChunk(&chunk);
//
//   if (!compile(source, &chunk)) {
//     freeChunk(&chunk);
//     return INTERPRET_COMPILE_ERROR;
//   }
//
//   vm->chunk = &chunk;
//   vm->ip = vm->chunk->code;
//
//   InterpretResult result = run(vm);
//   freeChunk(&chunk);
//   return result;
// }

void push(Value value, VM* vm) {
  *vm->stackTop = value;
  vm->stackTop++;
}

Value pop(VM* vm) {
  vm->stackTop--;
  return *vm->stackTop;
}
