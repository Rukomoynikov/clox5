#include "chunk.h"
#include "debug.h"

int main(int arg_count, const char* argv[]) {
  Chunk chunk;
  initChunk(&chunk);
  int constantIndex = addConstant(&chunk, 1);
  writeChunk(&chunk, OP_CONSTANT, 100);
  writeChunk(&chunk, constantIndex, 100);
  writeChunk(&chunk, OP_RETURN, 100);
  disassembleChunk(&chunk, "test chunk");
  freeChunk(&chunk);
}