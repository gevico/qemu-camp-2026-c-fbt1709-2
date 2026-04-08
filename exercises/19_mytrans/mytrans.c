// mytrans.c
#include "myhash.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trim(char *str) {
  if (!str || !*str)
    return;

  char *start = str;
  while (*start && isspace((unsigned char)*start))
    start++;
  if (start != str)
    memmove(str, start, strlen(start) + 1);

  size_t len = strlen(str);
  while (len > 0 && isspace((unsigned char)str[len - 1])) {
    str[--len] = '\0';
  }
}

int load_dictionary(const char *filename, HashTable *table,
                    uint64_t *dict_count) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("无法打开词典文件");
    return -1;
  }

  char line[1024];
  char current_word[256] = {0};

  while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\r\n")] = '\0';
    trim(line);
    if (line[0] == '\0')
      continue;

    if (line[0] == '#') {
      strncpy(current_word, line + 1, sizeof(current_word) - 1);
      current_word[sizeof(current_word) - 1] = '\0';
      trim(current_word);
      continue;
    }

    if (strncmp(line, "Trans:", 6) == 0 && current_word[0] != '\0') {
      const char *val = line + 6;
      if (hash_table_insert(table, current_word, val))
        (*dict_count)++;
    }
  }

  fclose(file);
  return 0;
}
