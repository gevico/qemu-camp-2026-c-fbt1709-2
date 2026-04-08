#include "circular_linked_list.h"

#include <stdlib.h>

Node *create_circular_list(int n) {
    if (n <= 0) {
        return NULL;
    }
    Node *head = malloc(sizeof(Node));
    if (!head) {
        return NULL;
    }
    head->id = 1;
    head->next = head;
    Node *tail = head;
    for (int i = 2; i <= n; i++) {
        Node *nn = malloc(sizeof(Node));
        if (!nn) {
            free_list(head);
            return NULL;
        }
        nn->id = i;
        nn->next = head;
        tail->next = nn;
        tail = nn;
    }
    return head;
}

void free_list(Node *head) {
    if (!head) {
        return;
    }
    Node *p = head->next;
    while (p != head) {
        Node *n = p->next;
        free(p);
        p = n;
    }
    free(head);
}
