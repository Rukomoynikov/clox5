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
    case OP_NEGATE:
      return simpleInstruction("OP_NEGATE", offset);
    case OP_ADD:
      return simpleInstruction("OP_ADD", offset);
    case OP_SUBTRACT:
      return simpleInstruction("OP_SUBTRACT", offset);
    case OP_MULTIPLY:
      return simpleInstruction("OP_MULTIPLY", offset);
    case OP_DIVIDE:
      return simpleInstruction("OP_DIVIDE", offset);
    case OP_CONSTANT:
      return constantInstruction("OP_CONSTANT", chunk, offset);
    case OP_NIL:
      return simpleInstruction("OP_NIL", offset);
    case OP_TRUE:
      return simpleInstruction("OP_TRUE", offset);
    case OP_FALSE:
      return simpleInstruction("OP_FALSE", offset);
    case OP_NOT:
      return simpleInstruction("OP_NOT", offset);
    case OP_EQUAL:
      return simpleInstruction("OP_EQUAL", offset);
    case OP_GREATER:
      return simpleInstruction("OP_GREATER", offset);
    case OP_LESS:
      return simpleInstruction("OP_LESS", offset);
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