// main.c
#include "myhash.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void to_lowercase(char *str) {
  for (; *str; ++str)
    *str = (char)tolower((unsigned char)*str);
}

static void strip_word(char *s) {
  size_t i = 0;
  while (s[i] && !isalpha((unsigned char)s[i]))
    i++;
  if (i)
    memmove(s, s + i, strlen(s + i) + 1);

  size_t n = strlen(s);
  while (n > 0 && !isalpha((unsigned char)s[n - 1]))
    s[--n] = '\0';

  to_lowercase(s);
}

int main(void) {
  HashTable *table = create_hash_table();
  if (!table) {
    fprintf(stderr, "无法创建哈希表\n");
    return 1;
  }

  printf("=== 哈希表版英语翻译器（支持百万级数据）===\n");
  uint64_t dict_count = 0;
  if (load_dictionary("dict.txt", table, &dict_count) != 0) {
    fprintf(stderr, "加载词典失败，请确保 dict.txt 存在。\n");
    free_hash_table(table);
    return 1;
  }
  printf("词典加载完成，共计%lu词条。\n", (unsigned long)dict_count);

  FILE *file = fopen("text.txt", "r");
  if (file == NULL) {
    fprintf(stderr, "无法打开文件 text.txt。\n");
    free_hash_table(table);
    return 1;
  }

  char line[1024];
  while (fgets(line, sizeof(line), file) != NULL) {
    line[strcspn(line, "\r\n")] = '\0';

    if (strlen(line) == 0) {
      continue;
    }

    char *saveptr = NULL;
    for (char *tok = strtok_r(line, " \t", &saveptr); tok != NULL;
         tok = strtok_r(NULL, " \t", &saveptr)) {
      char buf[256];
      strncpy(buf, tok, sizeof(buf) - 1);
      buf[sizeof(buf) - 1] = '\0';
      strip_word(buf);
      if (buf[0] == '\0')
        continue;

      const char *translation = hash_table_lookup(table, buf);
      printf("原文: %s\t", buf);
      if (translation)
        printf("翻译: %s\n", translation);
      else
        printf("未找到该单词的翻译。\n");
    }
  }

  fclose(file);
  free_hash_table(table);
  return 0;
}
