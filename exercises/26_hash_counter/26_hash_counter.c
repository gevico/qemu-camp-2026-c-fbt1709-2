#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 1024

typedef struct HashNode {
    char *word;
    int count;
    struct HashNode *next;
} HashNode;

typedef struct {
    HashNode **table;
    int size;
} HashTable;

unsigned long djb2_hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = (unsigned char)*str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

HashTable *create_hash_table(int size) {
    HashTable *ht = malloc(sizeof(HashTable));
    ht->table = calloc((size_t)size, sizeof(HashNode *));
    ht->size = size;
    return ht;
}

void hash_table_insert(HashTable *ht, const char *word) {
    unsigned long hash = djb2_hash(word) % (unsigned long)ht->size;
    HashNode *cur = ht->table[hash];
    while (cur) {
        if (strcmp(cur->word, word) == 0) {
            cur->count++;
            return;
        }
        cur = cur->next;
    }
    HashNode *n = malloc(sizeof(HashNode));
    n->word = strdup(word);
    n->count = 1;
    n->next = ht->table[hash];
    ht->table[hash] = n;
}

void get_all_words(HashTable *ht, HashNode **nodes, int *count) {
    int idx = 0;
    for (int i = 0; i < ht->size; i++) {
        HashNode *cur = ht->table[i];
        while (cur) {
            nodes[idx++] = cur;
            cur = cur->next;
        }
    }
    *count = idx;
}

int compare_nodes(const void *a, const void *b) {
    HashNode *node_a = *(HashNode **)a;
    HashNode *node_b = *(HashNode **)b;
    if (node_b->count != node_a->count) {
        return node_b->count - node_a->count;
    }
    return strcmp(node_a->word, node_b->word);
}

void free_hash_table(HashTable *ht) {
    for (int i = 0; i < ht->size; i++) {
        HashNode *node = ht->table[i];
        while (node != NULL) {
            HashNode *temp = node;
            node = node->next;
            free(temp->word);
            free(temp);
        }
    }
    free(ht->table);
    free(ht);
}

char *get_next_word(const char **text) {
    const char *p = *text;
    while (*p && !isalpha((unsigned char)*p)) {
        p++;
    }
    if (!*p) {
        return NULL;
    }
    const char *start = p;
    while (*p && isalpha((unsigned char)*p)) {
        p++;
    }
    size_t len = (size_t)(p - start);
    char *w = malloc(len + 1);
    if (!w) {
        return NULL;
    }
    for (size_t i = 0; i < len; i++) {
        w[i] = (char)tolower((unsigned char)start[i]);
    }
    w[len] = '\0';
    *text = p;
    return w;
}

int main(int argc, char *argv[]) {
    const char *file_path = "paper.txt";

    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("无法打开文件");
        return 1;
    }

    HashTable *ht = create_hash_table(TABLE_SIZE);
    char buffer[4096];

    printf("正在读取文件: %s\n", file_path);

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        const char *ptr = buffer;
        char *word;

        while ((word = get_next_word(&ptr)) != NULL) {
            hash_table_insert(ht, word);
            free(word);
        }
    }

    fclose(file);

    int cap = 0;
    for (int i = 0; i < ht->size; i++) {
        for (HashNode *p = ht->table[i]; p; p = p->next) {
            cap++;
        }
    }
    HashNode **nodes = malloc((size_t)cap * sizeof(HashNode *));
    int node_count = 0;
    get_all_words(ht, nodes, &node_count);

    qsort(nodes, (size_t)node_count, sizeof(HashNode *), compare_nodes);

    printf("\n单词统计结果（按频率降序排列）:\n");
    printf("%-20s %s\n", "单词", "出现次数");
    printf("-------------------- ----------\n");
    for (int i = 0; i < node_count; i++) {
        printf("%s:%d\n", nodes[i]->word, nodes[i]->count);
    }

    free(nodes);
    free_hash_table(ht);

    return 0;
}
