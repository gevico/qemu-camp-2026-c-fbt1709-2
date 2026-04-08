#include <stdio.h>

#define MAX_PEOPLE 50

typedef struct {
    int id;
} People;

typedef struct {
    People data[MAX_PEOPLE];
    int head;
    int tail;
    int count;
} Queue;

int main() {
    Queue q;
    int total_people=50;
    int report_interval=5;

    /* 环形队列：令部为 data[(head + i) % MAX_PEOPLE]，count 为人数 */
    q.head = 0;
    q.tail = 0;
    q.count = total_people;
    for (int i = 0; i < total_people; i++) {
        q.data[i].id = i + 1;
    }

    /* 约瑟夫环：每 report_interval 人中报数到第 report_interval 者出列 */
    while (q.count > 1) {
        for (int i = 0; i < report_interval - 1; i++) {
            People p = q.data[q.head];
            /* 队头出队并排到环上队尾 */
            int rear = (q.head + q.count) % MAX_PEOPLE;
            q.data[rear] = p;
            q.head = (q.head + 1) % MAX_PEOPLE;
        }
        /* 第 report_interval 人出列（当前队头即被淘汰者） */
        printf("淘汰: %d\n", q.data[q.head].id);
        q.head = (q.head + 1) % MAX_PEOPLE;
        q.count--;
    }

    printf("最后剩下的人是: %d\n", q.data[q.head].id);

    return 0;
}