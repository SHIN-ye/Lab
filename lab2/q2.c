// 最大子树和（树已按 1 作为根来定义子树）
// 输入：
//   N (1<=N<=1e5)
//   a1..aN (-1e5..1e5)
//   N-1 条无向边
// 输出：最大的子树和
// 说明：
// - 用非递归后序 DFS，避免递归栈在链式树上溢出。
// - 子树和可能达 1e10，用 long long 存储。
// 复杂度：O(N)

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// 邻接表加边：u -> v
static inline void add_edge(int u, int v, int *head, int *to, int *nxt, int *idx) {
to[*idx] = v;
nxt[*idx] = head[u];
head[u] = (*idx)++;
}

typedef long long ll;

int main(void) {
int N;
if (scanf("%d", &N) != 1) {
return 0;
}

// 节点权值（1-indexed）
ll *a = (ll *)malloc((N + 1) * sizeof(ll));
if (!a) return 0;
for (int i = 1; i <= N; ++i) {
	long long v;
	scanf("%lld", &v);
	a[i] = v;
}

// 邻接表
int M = (N - 1) * 2 + 5; // 边数量（双向）
int *head = (int *)malloc((N + 1) * sizeof(int));
int *to = (int *)malloc(M * sizeof(int));
int *nxt = (int *)malloc(M * sizeof(int));
if (!head || !to || !nxt) return 0;
for (int i = 1; i <= N; ++i) head[i] = -1;
int idx = 0;

for (int i = 0; i < N - 1; ++i) {
	int u, v;
	scanf("%d %d", &u, &v);
add_edge(u, v, head, to, nxt, &idx);
add_edge(v, u, head, to, nxt, &idx);
}

// 非递归后序 DFS
int stackCap = (N * 2 + 10);
int *st_u = (int *)malloc(stackCap * sizeof(int));
int *st_p = (int *)malloc(stackCap * sizeof(int));
unsigned char *st_flag = (unsigned char *)malloc(stackCap * sizeof(unsigned char));
ll *sub = (ll *)malloc((N + 1) * sizeof(ll));
if (!st_u || !st_p || !st_flag || !sub) return 0;

int top = 0; // 栈顶元素下标（size）
// push(root=1, parent=0, flag=0)
st_u[top] = 1; st_p[top] = 0; st_flag[top] = 0; ++top;

ll ans = LLONG_MIN;

while (top > 0) {
	--top;
	int u = st_u[top];
	int p = st_p[top];
	unsigned char flag = st_flag[top];

	if (flag == 0) {
		// 首次到达：压入二次处理标记，然后扩展子节点
		st_u[top] = u; st_p[top] = p; st_flag[top] = 1; ++top;
		for (int e = head[u]; e != -1; e = nxt[e]) {
			int v = to[e];
			if (v == p) continue;
			st_u[top] = v; st_p[top] = u; st_flag[top] = 0; ++top;
		}
	} else {
		// 第二次到达：可聚合子树和
		ll sum = a[u];
		for (int e = head[u]; e != -1; e = nxt[e]) {
			int v = to[e];
			if (v == p) continue;
			sum += sub[v];
		}
		sub[u] = sum;
		if (sum > ans) ans = sum;
	}
}

printf("%lld\n", ans);

// 清理（在线评测通常不强制，但保持良好习惯）
free(a);
free(head);
free(to);
free(nxt);
free(st_u);
free(st_p);
free(st_flag);
free(sub);

return 0;
}