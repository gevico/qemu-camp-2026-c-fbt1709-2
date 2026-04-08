#include <stddef.h>
#include <stdio.h>

struct Test {
    int a;
    char b;
};

#define container_of(ptr, type, member) \
    ((type *)((char *)(const typeof(((type *)0)->member) *)(ptr) - offsetof(type, member)))

int main(void) {
    struct Test t = {.a = 42, .b = 'Z'};

    char *ptr_to_b = &t.b;

    struct Test *owner = container_of(ptr_to_b, struct Test, b);

    printf("container_of(ptr_to_b) = %p\n", (void *)owner);
    printf("&t                  = %p\n", (void *)&t);

    if (owner != &t) {
        fprintf(stderr, "校验失败：地址不一致\n");
        return 1;
    }
    return 0;
}
