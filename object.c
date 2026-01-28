#include <string.h>
#include <stdio.h>

#include "object.h"
#include "value.h"
#include "memory.h"

#define ALLOCATE_OBJ(type, objectType) (type*)allocateObject(sizeof(type), objectType);

static Obj * allocateObject(size_t size, ObjType type);
static ObjString * allocateString(char * chars, int length);

ObjString * copyString(const char  * chars, int length) {
  char * heapChars = ALLOCATE(char, length + 1);
  memcpy(heapChars, chars, length);
  heapChars[length] = '\0';
  return allocateString(heapChars, length);
}

static ObjString * allocateString(char * chars, int length) {
  ObjString * obj_string = ALLOCATE_OBJ(ObjString, OBJ_STRING);
  obj_string -> length = length;
  obj_string -> chars = chars;
  return obj_string;
}

static Obj * allocateObject(size_t size, ObjType type) {
  Obj* object = (Obj*)reallocate(NULL, 0, size);
  object->type = type;
  return object;
}

ObjString * takeString(char * chars, int length) {
  return allocateString(chars, length);
}

void printObject(Value value) {
  switch (OBJ_TYPE(value)) {
    case OBJ_STRING:
      printf("%s", AS_CSTRING(value));
      break;
  }
}