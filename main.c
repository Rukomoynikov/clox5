#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main(int arg_count, const char* argv[]) {
  initVM();
  Chunk chunk;
  initChunk(&chunk);
  int constantIndex = addConstant(&chunk, 1);
  writeChunk(&chunk, OP_CONSTANT, 100);
  writeChunk(&chunk, constantIndex, 100);
  writeChunk(&chunk, OP_NEGATE, 100);
  writeChunk(&chunk, OP_CONSTANT, 100);
  writeChunk(&chunk, constantIndex, 100);
  writeChunk(&chunk, OP_RETURN, 100);
  interpret(&chunk);
  // disassembleChunk(&chunk, "test chunk");
  freeVM();
  freeChunk(&chunk);
}