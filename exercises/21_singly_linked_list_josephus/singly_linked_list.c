#include "singly_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

// 全局头指针
static link head = NULL;

// 创建新节点
link make_node(unsigned char item) {
    link p = malloc(sizeof(struct node));
    if (!p) {
        return NULL;
    }
    p->item = item;
    p->next = NULL;
    return p;
}

// 释放节点
void free_node(link p) { free(p); }

// 查找节点
link search(unsigned char key) {
    for (link p = head; p; p = p->next) {
        if (p->item == key) {
            return p;
        }
    }
    return NULL;
}

void insert(link p) {
    if (!p) {
        return;
    }
    p->next = head;
    head = p;
}

void delete(link p) {
    if (!p) {
        return;
    }
    if (p == head) {
        head = head->next;
        return;
    }
    link prev = head;
    while (prev && prev->next != p) {
        prev = prev->next;
    }
    if (prev) {
        prev->next = p->next;
    }
}

void traverse(void (*visit)(link)) {
    for (link p = head; p; p = p->next) {
        visit(p);
    }
}

void destroy(void) {
    link p = head;
    head = NULL;
    while (p) {
        link n = p->next;
        free(p);
        p = n;
    }
}

void push(link p) { insert(p); }

link pop(void) {
    if (!head) {
        return NULL;
    }
    link r = head;
    head = head->next;
    r->next = NULL;
    return r;
}

void free_list(link list_head) {
    while (list_head) {
        link n = list_head->next;
        free(list_head);
        list_head = n;
    }
}
