#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 101  

int head[MAXN], to[MAXN], nxt[MAXN], idx = 0;
int parentArr[MAXN], depthArr[MAXN], n;

void add_edge(int u, int v) {
    to[idx] = v; //当前边的终点
    nxt[idx] = head[u];
    head[u] = idx++; //head[u]变为当前边的索引
}

void BFS_depth_width(int root, int *maxDepth, int *maxWidth) {
    int queue[MAXN];
    int front = 0, rear = 0;
    memset(depthArr, 0, sizeof(depthArr)); //深度数组清零

    depthArr[root] = 1;
    queue[rear++] = root;
    *maxDepth = 1;
    *maxWidth = 0;

    while (front < rear) {
        int levelSize = rear - front;
        if (levelSize > *maxWidth) *maxWidth = levelSize;
        for (int i = 0; i < levelSize; ++i) {
            int u = queue[front++];
            for (int e = head[u]; e != -1; e = nxt[e]) {
                int v = to[e];
                depthArr[v] = depthArr[u] + 1;
                if (depthArr[v] > *maxDepth) *maxDepth = depthArr[v];
                queue[rear++] = v;
            }
        }
    }
}

int LCA(int a, int b) {
    while (depthArr[a] > depthArr[b]) a = parentArr[a];
    while (depthArr[b] > depthArr[a]) b = parentArr[b]; //提升到相同高度
    while (a != b) {
        a = parentArr[a];
        b = parentArr[b]; //直到ab重合在最近公共祖先
    }
    return a;//即为最近公共祖先
}

int main() {
    scanf("%d", &n);
    memset(head, -1, sizeof(head));
    memset(parentArr, -1, sizeof(parentArr));
    idx = 0;
    for (int i = 0; i < n - 1; ++i) {
		int u, v;
		if (scanf("%d %d", &u, &v) != 2) return 0;
		parentArr[v] = u;
		add_edge(u, v);
	}
    parentArr[1] = -1;
    int a, b;
    scanf("%d %d", &a, &b);
    int maxDepth = 1, maxWidth = 1;
    BFS_depth_width(1, &maxDepth, &maxWidth);

    int public_parent = LCA(a, b);

    int delay = 2 * (depthArr[a] - depthArr[public_parent]) + (depthArr[b] - depthArr[public_parent]);
    printf("%d\n", maxDepth);
	printf("%d\n", maxWidth);
	printf("%d\n", delay);

	return 0;
}


