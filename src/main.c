#include <stdio.h>
#include <stdlib.h>

#include "bytecode/chunk.h"
#include "bytecode/debug.h"
#include "common.h"
#include "vm/vm.h"

static char* readFile(const char* path) {
  FILE* file = fopen(path, "rb");

  // No file or user doesn't have access
  if (file == NULL) {
    fprintf(stderr, "Could not open file \"%s\".\n", path);
    exit(74);
  }

  fseek(file, 0L, SEEK_END);
  size_t fileSize = ftell(file);
  rewind(file);

  char* buffer = (char*)malloc(fileSize + 1);

  // Memeory not allocated
  if (buffer == NULL) {
    fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
    exit(74);
  }

  size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
  // Bytes misread
  if (bytesRead < fileSize) {
    fprintf(stderr, "Could not read file \"%s\".\n", path);
    exit(74);
  }

  buffer[bytesRead] = '\0';

  fclose(file);
  return buffer;
}

/// REPL should reall be able to handle new lines at any length
static void repl(VM* vm) {
  char line[1024];

  for (;;) {
    printf("~> ");
    if (!fgets(line, sizeof(line), stdin)) {
      printf("\n");
      break;
    }
    interpret(line, vm);
  }
}

static void runFile(const char* path, VM* vm) {
  char* source = readFile(path);
  InterpretResult result = interpret(source, vm);
  free(source);

  if (result == INTERPRET_COMPILE_ERROR) exit(65);
  if (result == INTERPRET_RUNTIME_ERROR) exit(70);
}

int main(int argc, const char* argv[]) {
  VM vm;
  initVM(&vm);

  if (argc == 1) {
    repl(&vm);
  } else if (argc == 2) {
    runFile(argv[1], &vm);
  } else {
    fprintf(stderr, "Usage: snek [path]\n");
    exit(64);
  }

  freeVM(&vm);
  return 0;
}

//
// static char* readFile(const char* path) {
//   FILE* file = fopen(path, "rb");
//
//   if (file == NULL) {
//     fprintf(stderr, "Could not open file \"%s\" .\n", path);
//   }
//
//   fseek(file, 0L, SEEK_END);
//   size_t fileSize = ftell(file);
//   rewind(file);
//
//   char* buffer = (char*)malloc(fileSize + 1);
//
//   if (buffer == NULL) {
//     fprintf(stderr, "Not enought memory to read \"%s\" .\n", path);
//   }
//   size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
//
//   if (bytesRead < fileSize) {
//     fprintf(stderr, "Could not read file \"%s\" .\n", path);
//   }
//
//   buffer[bytesRead] = '\0';
//
//   fclose(file);
//
//   return buffer;
// }
//
// static void runFile(const char* path, VM* vm) {
//   char* source = readFile(path);
//   InterpretResult result = interpret(source, vm);
//   free(source);
//
//   if (result == INTERPRET_COMPILE_ERROR) exit(65);
//   if (result == INTERPRET_RUNTIME_ERROR) exit(70);
// }
//
// int main(int argc, const char* argv[]) {
//   VM vm;
//   initVM(&vm);
//
//   if (argc == 1) {
//     repl(&vm);
//   } else if (argc == 2) {
//     runFile(argv[1], &vm);
//   } else {
//     fprintf(stderr, "Usage: snek [path]\n");
//     exit(64);
//   }
//
//   freeVM(&vm);
//   return 0;
// }
