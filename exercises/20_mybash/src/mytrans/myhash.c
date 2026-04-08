// hash_table.c
#include "myhash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long hash_function(const char *str) {
  unsigned long hash = 5381;
  int c;
  while ((c = *str++))
    hash = ((hash << 5) + hash) + c;
  return hash;
}

HashTable *create_hash_table() {
  HashTable *table = malloc(sizeof(HashTable));
  if (!table)
    return NULL;
  for (int i = 0; i < HASH_TABLE_SIZE; i++) {
    table->buckets[i] = NULL;
  }
  return table;
}

void free_node(HashNode *node) {
  if (node) {
    free(node->key);
    free(node->value);
    free(node);
  }
}

void free_hash_table(HashTable *table) {
  if (!table)
    return;
  for (int i = 0; i < HASH_TABLE_SIZE; i++) {
    HashNode *curr = table->buckets[i];
    while (curr) {
      HashNode *tmp = curr;
      curr = curr->next;
      free_node(tmp);
    }
  }
  free(table);
}

int hash_table_insert(HashTable *table, const char *key, const char *value) {
  if (!table || !key || !value)
    return 0;

  unsigned long h = hash_function(key) % HASH_TABLE_SIZE;
  HashNode *node = table->buckets[h];

  while (node) {
    if (strcmp(node->key, key) == 0) {
      free(node->value);
      node->value = strdup(value);
      return 1;
    }
    node = node->next;
  }

  HashNode *new = malloc(sizeof(HashNode));
  if (!new)
    return 0;
  new->key = strdup(key);
  new->value = strdup(value);
  if (!new->key || !new->value) {
    free(new->key);
    free(new->value);
    free(new);
    return 0;
  }
  new->next = table->buckets[h];
  table->buckets[h] = new;

  return 1;
}

const char *hash_table_lookup(HashTable *table, const char *key) {
  if (!table || !key)
    return NULL;

  unsigned long h = hash_function(key) % HASH_TABLE_SIZE;
  HashNode *node = table->buckets[h];

  while (node) {
    if (strcmp(node->key, key) == 0)
      return node->value;
    node = node->next;
  }

  return NULL;
}
