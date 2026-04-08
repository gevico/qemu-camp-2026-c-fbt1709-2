#include <stdio.h>
#include <stdlib.h>

#include "singly_linked_list.h"

void print_item(link p) { printf("%d ", p->item); }

static link g_first_node = NULL;
static void capture_first(link p) {
    if (g_first_node == NULL) {
        g_first_node = p;
    }
}

static link get_head_node(void) {
    g_first_node = NULL;
    traverse(capture_first);
    return g_first_node;
}

static inline link next_wrap(link p) {
    if (p == NULL) {
        return get_head_node();
    }
    return p->next ? p->next : get_head_node();
}

void create_list(int n) {
    if (n <= 0) {
        return;
    }

    destroy();
    for (int i = n; i >= 1; i--) {
        link new_node = make_node((unsigned char)i);
        push(new_node);
    }
}

void josephus_problem(int n, int k, int m) {
    if (n <= 0 || k <= 0 || m <= 0) {
        printf("参数错误：n, k, m 都必须大于 0\n");
        return;
    }

    create_list(n);

    link current = get_head_node();
    if (!current) {
        printf("\n");
        return;
    }
    for (int i = 1; i < k; ++i) {
        current = next_wrap(current);
    }

    for (int out = 0; out < n; ++out) {
        link target;
        if (m == 1) {
            target = current;
        } else {
            target = current;
            for (int i = 0; i < m - 1; ++i) {
                target = next_wrap(target);
            }
        }

        print_item(target);
        link nxt;
        if (target->next) {
            nxt = target->next;
        } else {
            nxt = get_head_node();
            if (nxt == target) {
                nxt = NULL;
            }
        }
        delete(target);
        free_node(target);

        if (!get_head_node()) {
            break;
        }
        current = nxt ? nxt : get_head_node();
    }

    printf("\n");
}

int main(void) {
    josephus_problem(5, 1, 2);
    josephus_problem(7, 3, 1);
    josephus_problem(9, 1, 8);
    return 0;
}
