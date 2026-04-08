#include <stdio.h>

char *my_strcpy(char *dest, const char *src) {
    char *d = dest;
    while ((*d++ = *src++) != '\0') {
        /* copy including terminating '\0' */
    }
    return dest;
}

int main() {
    char source[] = "Hello, World! This is a test string for my_strcpy function.\n";
    char destination[101];

    my_strcpy(destination, source);

    printf("拷贝后的字符串: %s", destination);
    
    return 0;
}