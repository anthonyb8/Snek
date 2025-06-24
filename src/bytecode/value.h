#ifndef clox_value_h
#define clox_value_h

#include <stdbool.h>
#include <stdint.h>

typedef enum {
  VAL_BOOL,
  VAL_NIL,
  VAL_NUMBER,
} ValueType;

typedef union {
  bool boolean;
  double number;
} Values;

typedef struct {
  ValueType type;
  Values as;
} Value;

// Consructors
#define BOOL_VAL(value) ((Value){VAL_BOOL, {.boolean = value}})
#define NIL_VAL ((Value){VAL_NIL, {.number = 0}})
#define NUMBER_VAL(value) ((Value){VAL_NUMBER, {.number = value}})

// Access value
#define AS_BOOL(value) ((value).as.boolean)
#define AS_NUMBER(value) ((value).as.number)

// Type checks
#define IS_BOOL(value) ((value).type == VAL_BOOL)
#define IS_NIL(value) ((value).type == VAL_NIL)
#define IS_NUMBER(value) ((value).type == VAL_NUMBER)

void printValue(Value* value);

// typedef double Value;
//
// void printValue(Value value);
//
// typedef struct {
//   int capacity;
//   int count;
//   Value* values;
// } ValueArray;
//
// void initValueArray(ValueArray* array);
// void writeValueArray(ValueArray* array, Value value);
// void freeValueArray(ValueArray* array);
//
#endif  // !clox_value_h
