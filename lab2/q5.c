// LAB2 a5: 计算树的最大深度、最大宽度，以及定制的 x->y 通讯延迟（经 LCA，上行每边耗时2，下行每边耗时1）
#include <stdio.h>
#include <string.h>

#define MAXN 100

// 邻接表（仅存父->子方向）
int head[MAXN], to[MAXN], nxt[MAXN], idx = 0;

// 基本信息
int n;
int parentArr[MAXN]; // parentArr[v] = u
int depthArr[MAXN];  // depth of node, root 1 has depth 1

static void add_edge(int u, int v) {
	to[idx] = v;
	nxt[idx] = head[u];
	head[u] = idx++;
}

static void bfs_build_depth_and_width(int root, int *maxDepth, int *maxWidth) {
	int q[MAXN];
	int front = 0, rear = 0;
	memset(depthArr, 0, sizeof(depthArr));

	depthArr[root] = 1;
	q[rear++] = root;
	*maxDepth = 1;
	*maxWidth = 0;

	while (front < rear) {
		int levelSize = rear - front;
		if (levelSize > *maxWidth) *maxWidth = levelSize;
		for (int i = 0; i < levelSize; ++i) {
			int u = q[front++];
			for (int e = head[u]; e != -1; e = nxt[e]) {
				int v = to[e];
				depthArr[v] = depthArr[u] + 1;
				if (depthArr[v] > *maxDepth) *maxDepth = depthArr[v];
				q[rear++] = v;
			}
		}
	}
}

static int lca(int a, int b) {
	// 提升到同一深度
	while (depthArr[a] > depthArr[b]) a = parentArr[a];
	while (depthArr[b] > depthArr[a]) b = parentArr[b];
	// 同步向上直到相等
	while (a != b) {
		a = parentArr[a];
		b = parentArr[b];
	}
	return a;
}

int main(void) {
	if (scanf("%d", &n) != 1) return 0;

	memset(head, -1, sizeof(head));
	memset(parentArr, 0, sizeof(parentArr));

	// 读入 n-1 条边：u 是 v 的父节点
	for (int i = 0; i < n - 1; ++i) {
		int u, v;
		if (scanf("%d %d", &u, &v) != 2) return 0;
		parentArr[v] = u;
		add_edge(u, v);
	}

	int x, y;
	if (scanf("%d %d", &x, &y) != 2) return 0;

	// 根为 1
	parentArr[1] = 0; // 根没有父亲

	int maxDepth = 1, maxWidth = 1;
	bfs_build_depth_and_width(1, &maxDepth, &maxWidth);

	// 计算 LCA 及通讯延迟
	int L = lca(x, y);
	int upEdges = depthArr[x] - depthArr[L];
	int downEdges = depthArr[y] - depthArr[L];
	int latency = 2 * upEdges + 1 * downEdges;

	// 输出
	printf("%d\n", maxDepth);
	printf("%d\n", maxWidth);
	printf("%d\n", latency);

	return 0;
}


















































