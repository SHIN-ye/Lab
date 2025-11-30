//递归的DFS
#include <stdio.h> 
#include <stdlib.h>
#include <limits.h>

typedef long long ll;

int N;
ll *a;
int *head_g, *to_g, *nxt_g;
ll ans = LLONG_MIN; //定义当前最大子树和

void add_edge(int u, int v, int *head, int *to, int *next, int *idx) {
    to[*idx] = v; //当前边的终点
    next[*idx] = head[u];
    head[u] = (*idx)++; //head[u]变为当前边的索引
}

ll DFS(int u, int parent) {
    ll sum = a[u]; 
    for (int e = head_g[u]; e != -1; e = nxt_g[e]) {
        int v = to_g[e];
        if (v == parent) continue; //跳过父节点
        sum += DFS(v, u); //累加子节点的子树和
    }
    if (sum > ans) {
        ans = sum; //更新最大子树和
    }
    return sum; //这里只是为了返回此子节点的sum, 方便父节点累加而不是返回ans, ans为全局变量, 
}

int main() {
    scanf("%d", &N);
    a = (ll *)malloc((N + 1) * sizeof(ll));
    for (int i = 1; i <= N; i++) {
        scanf("%lld", &a[i]);
    }
    head_g = (int *)malloc((N + 1) * sizeof(int));
    to_g = (int *)malloc(N * 2 * sizeof(int));
    nxt_g = (int *)malloc(N * 2 * sizeof(int));
    for (int i = 1; i <= N; ++i) head_g[i] = -1;
    int idx = 0;
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v, head_g, to_g, nxt_g, &idx);
        add_edge(v, u, head_g, to_g, nxt_g, &idx);
    }
    DFS(1, 0);
    printf("%lld\n", ans);
    free(a);
    free(head_g);
    free(to_g);
    free(nxt_g);
    return 0;
}
