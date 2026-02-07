#pragma once

#include "common.h"
#include "chunk.h"
#include "table.h"

#define STACK_MAX 256

typedef struct {
  Chunk * chunk;
  uint8_t * ip;
  Value stack[STACK_MAX];
  Value * stackTop;
  Table strings;
} VM;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM();
InterpretResult interpret(char * source);
void freeVM();
void push(Value value);
Value pop();

extern VM vm;