#include <stdio.h>
#include <stdlib.h>

#include "circular_linked_list.h"

static void josephus_problem(int n, int k, int m) {
    if (n <= 0 || k <= 0 || m <= 0) {
        printf("参数错误\n");
        return;
    }

    Node *head = create_circular_list(n);
    if (!head) {
        printf("\n");
        return;
    }

    Node *current = head;
    Node *prev = head;
    while (prev->next != head) {
        prev = prev->next;
    }

    for (int i = 1; i < k; ++i) {
        prev = current;
        current = current->next;
    }

    int left = n;
    while (left > 0) {
        for (int i = 1; i < m; ++i) {
            prev = current;
            current = current->next;
        }
        printf("%d ", current->id);
        prev->next = current->next;
        Node *nx = current->next;
        if (current == head) {
            head = nx;
        }
        free(current);
        current = nx;
        left--;
    }
    printf("\n");
}

int main(void) {
    josephus_problem(5, 1, 2);
    josephus_problem(7, 3, 1);
    josephus_problem(9, 1, 8);
    return 0;
}
