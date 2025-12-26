#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 200005 // 双向边,所以是 M * 2
#define MOD 1000000007

// 邻接表存储
int head[MAXN];
int to[MAXM];
int next[MAXM];
int edge_cnt = 0;

void add_edge(int u, int v) {
    to[edge_cnt] = v;
    next[edge_cnt] = head[u];
    head[u] = edge_cnt++;
}

// BFS队列
int q[MAXN];
int dist[MAXN];
int count[MAXN];

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;

    // 初始化邻接表
    memset(head, -1, sizeof(head));
    edge_cnt = 0;

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u); // 双向通道
    }

    // 初始化距离和方案数
    // dist初始化为-1表示未访问
    for (int i = 1; i <= n; i++) {
        dist[i] = -1;
        count[i] = 0;
    }

    // BFS初始化
    int front = 0, rear = 0;
    q[rear++] = 1;
    dist[1] = 0;
    count[1] = 1;

    while (front < rear) {
        int u = q[front++];
        
        // 遍历u的所有邻居
        for (int i = head[u]; i != -1; i = next[i]) {
            int v = to[i];
            
            if (dist[v] == -1) {
                // 第一次发现 v，这是最短路径
                dist[v] = dist[u] + 1;
                count[v] = count[u];
                q[rear++] = v;
            } else if (dist[v] == dist[u] + 1) {
                // 再次发现 v，且距离等于最短距离，累加方案数
                count[v] = (count[v] + count[u]) % MOD;
            }
            // 如果 dist[v] < dist[u] + 1,说明不是最短路,忽略
        }
    }

    // 输出结果:从2到N号房间
    for (int i = 2; i <= n; i++) {
        if (dist[i] == -1) {
            printf("0\n");
        } else {
            printf("%d\n", count[i]);
        }
    }

    return 0;
}
