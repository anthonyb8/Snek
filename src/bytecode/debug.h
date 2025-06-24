#ifndef snek_debug_h
#define snek_debug_h

#include "chunk.h"

void disassembleChunk(Chunk* chunk, char* name);
int disassembleInstruction(Chunk* chunk, int offset);

#endif  // ! snek_debug_h
