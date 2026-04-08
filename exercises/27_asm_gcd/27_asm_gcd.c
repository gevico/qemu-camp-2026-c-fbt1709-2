#include <stdio.h>

unsigned int gcd_asm(unsigned int a, unsigned int b) {
    unsigned int result;

    __asm__ volatile(
        "movl %1, %%eax\n\t"
        "movl %2, %%ebx\n\t"
        ".Lgcd_check:\n\t"
        "testl %%ebx, %%ebx\n\t"
        "jz .Lgcd_done\n\t"
        "cmpl %%eax, %%ebx\n\t"
        "je .Lgcd_done\n\t"
        "ja .Lgcd_agtb\n\t"
        "subl %%eax, %%ebx\n\t"
        "jmp .Lgcd_check\n\t"
        ".Lgcd_agtb:\n\t"
        "subl %%ebx, %%eax\n\t"
        "jmp .Lgcd_check\n\t"
        ".Lgcd_done:\n\t"
        : "=a"(result)
        : "r"(a), "r"(b)
        : "ebx", "cc");

    return result;
}

int main(int argc, char *argv[]) {
    printf("%d\n", gcd_asm(12, 8));
    printf("%d\n", gcd_asm(7, 5));
    return 0;
}
