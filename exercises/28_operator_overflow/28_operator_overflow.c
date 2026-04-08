#include <stdio.h>
#include <limits.h>

#define CHECK_OVERFLOW(carry) carry ? "Overflow" : "Not Overflow"

int check_add_overflow_asm(unsigned int a, unsigned int b) {
    unsigned char carry;
    unsigned int tmp = a;
    __asm__ volatile("addl %2, %0\n\t"
                     "setc %1"
                     : "+r"(tmp), "=qm"(carry)
                     : "r"(b)
                     : "cc");
    return carry;
}

int check_sub_overflow_asm(unsigned int a, unsigned int b) {
    unsigned char cf;
    unsigned int tmp = a;
    __asm__ volatile("subl %2, %0\n\t"
                     "setc %1"
                     : "+r"(tmp), "=qm"(cf)
                     : "r"(b)
                     : "cc");
    return cf;
}

int check_mul_overflow_asm(unsigned int a, unsigned int b) {
    unsigned int lo, hi;
    __asm__ volatile("mull %%ebx\n\t" : "=a"(lo), "=d"(hi) : "a"(a), "b"(b) : "cc");
    (void)lo;
    return hi != 0;
}

int check_div_overflow_asm(unsigned int a, unsigned int b) {
    (void)a;
    unsigned char z;
    __asm__ volatile("cmpl $0, %1\n\t"
                     "sete %0"
                     : "=qm"(z)
                     : "r"(b)
                     : "cc");
    return z;
}

int main(void) {
    printf("(UINT_MAX + 1)Add: %s\n", CHECK_OVERFLOW(check_add_overflow_asm(UINT_MAX, 1)));
    printf("(1, 0)Add: %s\n", CHECK_OVERFLOW(check_add_overflow_asm(1, 0)));
    printf("(0, 1)Sub: %s\n", CHECK_OVERFLOW(check_sub_overflow_asm(0, 1)));
    printf("(2, 1)Sub: %s\n", CHECK_OVERFLOW(check_sub_overflow_asm(2, 1)));
    printf("(UINT_MAX, 2)Mul: %s\n", CHECK_OVERFLOW(check_mul_overflow_asm(UINT_MAX, 2)));
    printf("(1, 2)Mul: %s\n", CHECK_OVERFLOW(check_mul_overflow_asm(1, 2)));
    printf("(10, 0)Div: %s\n", CHECK_OVERFLOW(check_div_overflow_asm(10, 0)));
    printf("(2, 1)Div: %s\n", CHECK_OVERFLOW(check_div_overflow_asm(2, 1)));
    return 0;
}
