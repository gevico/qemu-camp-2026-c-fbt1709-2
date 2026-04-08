#include <stdio.h>
#include <stdlib.h>

#if DEBUG_LEVEL >= 2
#define DEBUG_PRINT(fmt, ...) printf("DEBUG: func=%s, line=%d, " fmt "\n", __func__, __LINE__, ##__VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...) ((void)0)
#endif

void test(void) {
    int x = 42;




































    DEBUG_PRINT("x=%d", x);
}

int main(void) {
    test();
    return 0;
}
