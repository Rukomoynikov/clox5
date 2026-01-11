#include "debug.h"
#include "value.h"
#include <stdio.h>

static int simpleInstruction(const char * opCodeName, const int offset);
static int constantInstruction(const char * opCodeName, Chunk * chunk, const int offset);

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
    case OP_CONSTANT:
      return constantInstruction("OP_CONSTANT", chunk, offset);
    default:
      printf("Unknown code %d\n", instruction);
      return offset + 1;
  }
}

static int simpleInstruction(const char * opCodeName, const int offset) {
  printf("%s\n", opCodeName);
  return offset + 1;
}

static int constantInstruction(const char * opCodeName, Chunk * chunk, const int offset) {
  uint8_t constantIndex = chunk -> code[offset + 1];
  printf("%-16s %4d '", opCodeName, constantIndex);
  printValue(chunk -> constants.values[constantIndex]);
  printf("'\n");
  return offset + 2;
}