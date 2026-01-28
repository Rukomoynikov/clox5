#pragma once

#include "common.h"
#include <stdlib.h>

#define GROW_CAPACITY(oldCapacity) (oldCapacity < 8 ? 8 : oldCapacity * 2);

#define GROW_ARRAY(type, pointer, oldCapacity, newCapacity) \
  (type *)reallocate(pointer, sizeof(type) * oldCapacity, sizeof(type) * newCapacity)

#define FREE_ARRAY(type, pointer, capacity) \
  reallocate(pointer, sizeof(type) * capacity, 0)

#define ALLOCATE(type, length) (type*)reallocate(NULL, 0, sizeof(type) * length);

void * reallocate(void * pointer, size_t oldCapacity, size_t newCapacity);