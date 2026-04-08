#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

int main(void)
{
	typedef struct {
		int r;
		int c;
	} Point;

	Point queue[MAX_ROW * MAX_COL];
	int head = 0;
	int tail = 0;
	int visited[MAX_ROW][MAX_COL] = {0};
	int pr[MAX_ROW][MAX_COL];
	int pc[MAX_ROW][MAX_COL];

	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			pr[i][j] = -1;
			pc[i][j] = -1;
		}
	}

	if (maze[0][0] != 0 || maze[MAX_ROW - 1][MAX_COL - 1] != 0) {
		printf("起点或终点为墙，无法寻路\n");
		return 0;
	}

	visited[0][0] = 1;
	queue[tail++] = (Point){0, 0};

	const int dr[] = {-1, 1, 0, 0};
	const int dc[] = {0, 0, -1, 1};

	int end_r = -1;
	int end_c = -1;

	while (head < tail) {
		Point p = queue[head++];
		if (p.r == MAX_ROW - 1 && p.c == MAX_COL - 1) {
			end_r = p.r;
			end_c = p.c;
			break;
		}
		for (int k = 0; k < 4; k++) {
			int nr = p.r + dr[k];
			int nc = p.c + dc[k];
			if (nr < 0 || nr >= MAX_ROW || nc < 0 || nc >= MAX_COL) {
				continue;
			}
			if (maze[nr][nc] != 0 || visited[nr][nc]) {
				continue;
			}
			visited[nr][nc] = 1;
			pr[nr][nc] = p.r;
			pc[nr][nc] = p.c;
			queue[tail++] = (Point){nr, nc};
		}
	}

	if (end_r < 0) {
		printf("无解（未到达右下角）\n");
		return 0;
	}

	Point path[MAX_ROW * MAX_COL];
	int len = 0;
	for (int r = end_r, c = end_c; r >= 0;) {
		path[len++] = (Point){r, c};
		int tr = pr[r][c];
		int tc = pc[r][c];
		r = tr;
		c = tc;
	}

	printf("队列（BFS）求得的最短路径（行,列）：\n");
	/* 与评测一致：从终点到起点，且坐标格式为 "(行, 列)" */
	for (int i = 0; i < len; i++) {
		printf("(%d, %d)\n", path[i].r, path[i].c);
	}

	return 0;
}