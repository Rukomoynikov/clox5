#include <string.h>
#include <stdio.h>

#include "object.h"
#include "value.h"
#include "memory.h"

#define ALLOCATE_OBJ(type, objectType) (type*)allocateObject(sizeof(type), objectType);

static Obj * allocateObject(size_t size, ObjType type);
static ObjString * allocateString(char * chars, int length, uint32_t hash);
static uint32_t hashString(const char * key, int length);

static ObjString * allocateString(char * chars, int length, uint32_t hash) {
  ObjString * obj_string = ALLOCATE_OBJ(ObjString, OBJ_STRING);
  obj_string -> length = length;
  obj_string -> chars = chars;
  obj_string -> hash = hash;
  return obj_string;
}

ObjString * copyString(const char  * chars, int length) {
  uint32_t hash = hashString(chars, length);
  char * heapChars = ALLOCATE(char, length + 1);
  memcpy(heapChars, chars, length);
  heapChars[length] = '\0';
  return allocateString(heapChars, length, hash);
}

static Obj * allocateObject(size_t size, ObjType type) {
  Obj* object = (Obj*)reallocate(NULL, 0, size);
  object->type = type;
  return object;
}

ObjString * takeString(char * chars, int length) {
  uint32_t hash = hashString(chars, length);
  return allocateString(chars, length, hash);
}

void printObject(Value value) {
  switch (OBJ_TYPE(value)) {
    case OBJ_STRING:
      printf("%s", AS_CSTRING(value));
      break;
  }
}

static uint32_t hashString(const char * key, int length) {
  uint32_t hash = 2166136261u;
  for (int i = 0; i < length; i++) {
    hash ^= (uint8_t)key[i];
    hash *= 16777619;
  }
  return hash;
}