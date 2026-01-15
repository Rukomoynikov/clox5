#include <stdio.h>
#include <stdlib.h>

#include "chunk.h"
#include "debug.h"
#include "vm.h"

static void repl();
static void runFile(char * filePath);
static char * readFile(char * filePath);

int main(int arg_count, const char* argv[]) {
  initVM();

  repl();

  if (arg_count == 1) {
    repl();
  } else if (arg_count == 2) {
    runFile(argv[1]);
  } else {
    fprintf(stderr, "Unknown number of arguments\n");
    exit(64);
  }

  freeVM();
  return 0;
}

static void repl() {
  char line[1024];

  for (;;) {
    printf("> ");

    if (!fgets(line, sizeof(line), stdin)) {
      printf("\n");
      break;
    }

    interpret(line);
  }
}

static void runFile(char * filePath) {
  char * source = readFile(filePath);
  InterpretResult result = interpret(source);
  free(source);

  if (result == INTERPRET_COMPILE_ERROR) exit(65);
  if (result == INTERPRET_RUNTIME_ERROR) exit(70);
}

static char * readFile(char * filePath) {
  FILE * file = fopen(filePath, "rb");

  fseek(file, 0L, SEEK_END);
  size_t fileSize = ftell(file);
  rewind(file);

  char* buffer = (char*)malloc(fileSize + 1);
  size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
  buffer[bytesRead] = '\0';

  fclose(file);
  return buffer;
}