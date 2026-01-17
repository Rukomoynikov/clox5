#include "scanner.h"
#include "chunk.h"
#include <stdio.h>
#include <stdlib.h>
#include "compiler.h"

static void advance();
static void errorAtCurrent(const char * message);
static void errorAt(Token * token, const char * message);
static void consume(TokenType type, const char * errorMessage);
static Chunk * currentChunk();
static void endCompiler();
static void emitReturn();

bool compile(char * source, Chunk * chunk) {
  initScanner(source);
  compilingChunk = chunk;

  parser.panicMode = false;
  parser.hadError = false;

  advance();
  expression();
  consume(TOKEN_EOF, "Expected end of expression");
  endCompiler();
  return !parser.hadError;
}

static void advance() {
  parser.previous = parser.current;

  for (;;) {
    parser.current = scanToken();
    if (parser.current.type != TOKEN_ERROR) break;

    errorAtCurrent(parser.current.start);;
  }
}

static void errorAtCurrent(const char * message) {
  errorAt(&parser.current, message);
}

static void error(const char * message) {
  errorAt(&parser.previous, message);
}

static void errorAt(Token * token, const char * message) {
  if (parser.panicMode) return;
  parser.panicMode = true;
  fprintf(stderr, "[ line %d] Error", token -> line);

  if (token -> type == TOKEN_EOF) {
    fprintf(stderr, "at the end.");
  } else if (token -> type == TOKEN_ERROR) {

  } else {
    fprintf(stderr, "at '%.*s'", token -> length, token -> start);
  }

  fprintf(stderr, ": %s\n", message);
  parser.hadError = true;
}

static void consume(TokenType type, const char * errorMessage) {
  if (parser.current.type == type) {
    advance();
    return;
  }

  errorAtCurrent(errorMessage);
}

static void emitByte(uint8_t byte) {
  writeChunk(currentChunk(), byte, parser.previous.line);
}

static Chunk * currentChunk() {
  return compilingChunk;
}

static void endCompiler() {
  emitReturn();
}

static void emitReturn() {
  emitByte(OP_RETURN);
}

static void emitBytes(uint8_t byte1, uint8_t byte2) {
  emitByte(byte1);
  emitByte(byte2);
}