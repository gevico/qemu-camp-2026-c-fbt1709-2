#include <stdio.h>
#include <ctype.h>

int main() {
    char str[]="Don't ask what your country can do for you, but ask what you can do for your country.";
    int wordCount = 0;
    int in_word = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        if (isalpha(c)) {
            if (!in_word) {
                wordCount++;
                in_word = 1;
            }
        } else if (c == '\'' && in_word) {
            /* Don't 等缩写：撇号仍在同一单词内 */
        } else {
            in_word = 0;
        }
    }

    printf("单词数量: %d\n", wordCount);
    
    return 0;
}