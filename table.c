#include "table.h"

#include "memory.h"
#include "object.h"

#define TABLE_MAX_LOAD 0.75

static Entry * findEntry(Entry * entries, int capacity, ObjString * key);
static void adjustCapacity(Table * table, int capacity);

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

bool tableSet(Table * table, ObjString * key, Value value) {
  if (table -> count < table -> capacity * TABLE_MAX_LOAD) {
    int capacity = GROW_CAPACITY(table -> capacity);
    adjustCapacity(table, capacity);
  }

  Entry * entry = findEntry(table -> entries, table -> capacity, key);
  bool isNewKey = entry -> key == nullptr;

  if (isNewKey && IS_NIL(entry -> value)) table -> count++;

  entry -> key = key;
  entry -> value = value;

  return isNewKey;
}

static Entry * findEntry(Entry * entries, int capacity, ObjString * key) {
  uint32_t index = key -> hash % capacity;
  Entry * tombstone = nullptr;

  for (;;) {
    Entry * entry = &entries[index];

    if (entry -> key == nullptr) {
      if (IS_NIL(entry -> value)) {
        return tombstone != nullptr ? tombstone : entry;
      } else {
        if (tombstone == nullptr) tombstone = entry;
      }
    } else if (entry -> key == key) {
      return entry;
    }

    index = (index + 1) % capacity;
  }
}

static void adjustCapacity(Table * table, int capacity) {
  Entry * entries = ALLOCATE(Entry, capacity);

  table -> count = 0;

  for (int i = 0; i < table -> capacity; i++) {
    entries[i].key = nullptr;
    entries[i].value = NIL_VAL;
  }

  for (int i = 0; i < table -> capacity; i++) {
    Entry * entry = &table -> entries[i];
    if (entry -> key == nullptr) continue;

    Entry * dest = findEntry(entries, capacity, entry -> key);

    dest -> key = entry -> key;
    dest -> value = entry -> value;
  }

  FREE_ARRAY(Entry, table -> entries, table -> capacity);

  table -> entries = entries;
  table -> capacity = capacity;
}

void tableAddAll(Table * from, Table * to) {
  for (int i = 0; i < from -> capacity; i++) {
    Entry * entry = &from -> entries[i];
    if (entry -> key != nullptr) tableSet(to, entry -> key, entry -> value);
  }
}

bool tableGet(Table * table, ObjString * key, Value * value) {
  if (table -> count == 0) return false;

  Entry * entry = findEntry(table -> entries, table -> capacity, key);
  if (entry -> key == nullptr) return false;

  *value = entry -> value;
  return true;
}

bool tableDelete(Table * table, ObjString * key) {
  if (table -> count == 0) return false;

  Entry * entry = findEntry(table -> entries, table -> capacity, key);
  if (entry -> key == nullptr) return false;

  entry -> key = nullptr;
  entry -> value = BOOL_VAL(true);

  return true;
}