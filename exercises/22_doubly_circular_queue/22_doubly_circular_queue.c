#include <stdio.h>
#include <stdlib.h>

#include "doubly_circular_queue.h"

static link g_last = NULL;
static void capture_last(link p) { g_last = p; }

static link get_last(void) {
    g_last = NULL;
    traverse(capture_last);
    return g_last;
}

static void enqueue_int(int v) {
    insert(make_node(v));
}

static int dequeue_int(int *out) {
    link last = get_last();
    if (!last) {
        return 0;
    }
    if (out) {
        *out = last->data;
    }
    delete(last);
    free_node(last);
    return 1;
}

static void print_dequeue_n(int n) {
    for (int i = 0; i < n; i++) {
        int v;
        if (!dequeue_int(&v)) {
            break;
        }
        if (i) {
            printf(" ");
        }
        printf("%d", v);
    }
}

int main(void) {
    enqueue_int(1);
    enqueue_int(2);
    enqueue_int(3);
    print_dequeue_n(3);
    printf("\n");
    destroy();

    enqueue_int(42);
    printf("single: ");
    print_dequeue_n(1);
    printf("\n");
    destroy();

    {
        int ok = dequeue_int(NULL);
        printf("empty: %s\n", ok ? "NG" : "OK");
    }
    destroy();

    return 0;
}
