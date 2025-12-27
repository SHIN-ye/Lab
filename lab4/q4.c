#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 5005
#define MAXM 100005
#define MOD 1000000007

// 邻接表
int head[MAXN];
int to[MAXM];
int next[MAXM];
int edge_cnt = 0;

// 度数数组
int in_degree[MAXN];
int out_degree[MAXN];

// DP数组:dp[i]表示从任意起点到达节点i的路径数量
int dp[MAXN];

// 队列
int q[MAXN];

void add_edge(int u, int v) {
    to[edge_cnt] = v;
    next[edge_cnt] = head[u];
    head[u] = edge_cnt++;
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;

    // 初始化
    memset(head, -1, sizeof(head));
    memset(in_degree, 0, sizeof(in_degree));
    memset(out_degree, 0, sizeof(out_degree));
    memset(dp, 0, sizeof(dp));
    edge_cnt = 0;

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        out_degree[u]++;
        in_degree[v]++;
    }

    // 拓扑排序初始化
    int front = 0, rear = 0;


    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            q[rear++] = i;
            dp[i] = 1; // 起点自身的路径数为1
        }
    }

    // 拓扑排序+ DP
    while (front < rear) {
        int u = q[front++];

        for (int i = head[u]; i != -1; i = next[i]) {
            int v = to[i];
            
            // 状态转移:累加前驱节点的路径数
            dp[v] = (dp[v] + dp[u]) % MOD;

            // 减少入度
            in_degree[v]--;
            if (in_degree[v] == 0) {
                q[rear++] = v;
            }
        }
    }

    int total_chains = 0;
    for (int i = 1; i <= n; i++) {
        if (out_degree[i] == 0) {
            total_chains = (total_chains + dp[i]) % MOD;
        }
    }

    printf("%d\n", total_chains);

    return 0;
}
