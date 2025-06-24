#include <stdint.h>
#include <stdio.h>

#include "value.h"

void printValue(Value* value) { printf("Value %g", AS_NUMBER(*value)); }

// void printValue(Value value) { printf("Value %g", value); }
//
// void initValueArray(ValueArray* array) {
//   array->count = 0;
//   array->capacity = 0;
//   array->values = NULL;
// }
//
// void writeValueArray(ValueArray* array, Value value) {
//   if (array->capacity < array->count + 1) {
//     int oldCapacity = array->capacity;
//     array->capacity = grow_capacity(oldCapacity);
//     array->values =
//         (Value*)reallocate(array->values, sizeof(Value) * oldCapacity,
//                            sizeof(Value) * array->capacity);
//   }
//
//   array->values[array->count] = value;
//   array->count++;
// }
//
// void freeValueArray(ValueArray* array) {
//   freeArray(array->values, array->capacity);
//   initValueArray(array);
// }
