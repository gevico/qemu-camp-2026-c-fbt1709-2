#include "doubly_circular_queue.h"

#include <stdlib.h>

static struct node headsentinel;
static struct node tailsentinel;

static void link_sentinels(void) {
    headsentinel.data = tailsentinel.data = 0;
    headsentinel.prev = &tailsentinel;
    headsentinel.next = &tailsentinel;
    tailsentinel.prev = &headsentinel;
    tailsentinel.next = &headsentinel;
}

static link head = &headsentinel;
static link tail = &tailsentinel;
static int linked = 0;

static void ensure(void) {
    if (!linked) {
        link_sentinels();
        linked = 1;
    }
}

link make_node(int data) {
    ensure();
    link p = malloc(sizeof(struct node));
    if (!p) {
        return NULL;
    }
    p->data = data;
    p->prev = p->next = NULL;
    return p;
}

void free_node(link p) {
    if (p && p != &headsentinel && p != &tailsentinel) {
        free(p);
    }
}

link search(int key) {
    ensure();
    for (link p = head->next; p != tail; p = p->next) {
        if (p->data == key) {
            return p;
        }
    }
    return NULL;
}

void insert(link p) {
    ensure();
    if (!p) {
        return;
    }
    p->next = head->next;
    p->prev = head;
    head->next->prev = p;
    head->next = p;
}

void delete(link p) {
    ensure();
    if (!p || p == &headsentinel || p == &tailsentinel) {
        return;
    }
    p->prev->next = p->next;
    p->next->prev = p->prev;
    p->prev = p->next = NULL;
}

void traverse(void (*visit)(link)) {
    ensure();
    for (link p = head->next; p != tail; p = p->next) {
        visit(p);
    }
}

void destroy(void) {
    ensure();
    while (head->next != tail) {
        link p = head->next;
        delete(p);
        free_node(p);
    }
}
