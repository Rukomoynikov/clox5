#include "debug.h"
#include <stdio.h>

static int simpleInstruction(const char * opCodeName, const int offset);

void disassembleChunk(Chunk * chunk, const char * message) {
  printf("== %s ==\n", message);

  for (int offset = 0; offset < chunk -> count;) {
    offset = disassembleInstruction(chunk, offset);
  }
}

int disassembleInstruction(Chunk * chunk, const int offset) {
  printf("%04d ", offset);

  uint8_t instruction = chunk -> code[offset];

  switch (instruction) {
    case OP_RETURN:
      return simpleInstruction("OP_RETURN", offset);
    default:
      printf("Unknown code %d\n", instruction);
      return offset + 1;
  }
}

static int simpleInstruction(const char * opCodeName, const int offset) {
  printf("%s\n", opCodeName);
  return offset + 1;
}