#include "table.h"

#include "memory.h"

void initTable(Table * table) {
  table -> count = 0;
  table -> capacity = 0;
  table -> entries = nullptr;
}

void freeTable(Table * table) {
  FREE_ARRAY(Entry, table -> entries, table -> capacity);
  // reallocate(pointer, sizeof(type) * capacity, 0)
  // void * reallocate(void * pointer, size_t oldCapacity, size_t newCapacity);
}