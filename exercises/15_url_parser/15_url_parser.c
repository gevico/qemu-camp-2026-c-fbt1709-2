#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * URL参数解析器
 * 输入：包含http/https超链接的字符串
 * 输出：解析出所有的key-value键值对，每行显示一个
 */

int parse_url(const char *url) {
    int err = 0;

    const char *q = strchr(url, '?');
    if (!q) {
        err = EINVAL;
        goto exit;
    }

    char *query = strdup(q + 1);
    if (!query) {
        err = ENOMEM;
        goto exit;
    }

    char *saveptr = NULL;
    char *pair = strtok_r(query, "&", &saveptr);
    while (pair) {
        char *eq = strchr(pair, '=');
        if (eq) {
            *eq = '\0';
            printf("key = %s, value = %s\n", pair, eq + 1);
        }
        pair = strtok_r(NULL, "&", &saveptr);
    }

    free(query);

exit:
    return err;
}

int main(void) {
    const char *test_url =
        "https://cn.bing.com/search?name=John&age=30&city=New+York";

    printf("Parsing URL: %s\n", test_url);
    printf("Parameters:\n");

    parse_url(test_url);

    return 0;
}
