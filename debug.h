#pragma once

#include "chunk.h"

void disassembleChunk(Chunk * chunk, const char * message);
int disassembleInstruction(Chunk * chunk, const int offset);