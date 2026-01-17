#pragma once

#include "scanner.h"

typedef struct {
  Token previous;
  Token current;
  bool hadError;
  bool panicMode;
} Parser;

Parser parser;
Chunk * compilingChunk;

bool compile(char * source, Chunk * chunk);
