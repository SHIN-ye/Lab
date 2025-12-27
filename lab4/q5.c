#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXN 100005
#define MAXM 200005 // 双向边

// 邻接表
int head[MAXN];
int to[MAXM];
int next[MAXM];
int edge_cnt = 0;

// 节点快乐值
long long a[MAXN];
// 素数标记
bool is_prime[MAXN];
// 访问标记
bool visited[MAXN];

// 队列
int q[MAXN];

void add_edge(int u, int v) {
    to[edge_cnt] = v;
    next[edge_cnt] = head[u];
    head[u] = edge_cnt++;
}

// 埃氏筛法预处理素数
void sieve(int n) {
    // 初始化:假设都是素数
    for (int i = 2; i <= n; i++) is_prime[i] = true;
    is_prime[0] = is_prime[1] = false; // 1不是素数

    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    // 读取快乐值
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }

    // 初始化邻接表
    memset(head, -1, sizeof(head));
    edge_cnt = 0;

    // 读取边
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }

    // 预处理素数
    sieve(n);

    long long total_happiness = 0;
    memset(visited, 0, sizeof(visited));

    // 遍历所有节点
    for (int i = 1; i <= n; i++) {
        if (visited[i]) continue;

        long long current_block_sum = 0;

        // 如果是合数, 它自己就是一个独立的块
        if (!is_prime[i]) {
            visited[i] = true;
            current_block_sum = a[i];
        } else {
            // 如果是素数，搜索整个素数连通块
            int front = 0, rear = 0;
            q[rear++] = i;
            visited[i] = true;
            current_block_sum = a[i];

            while (front < rear) {
                int u = q[front++];

                for (int e = head[u]; e != -1; e = next[e]) {
                    int v = to[e];
                    // 只有当邻居也是素数, 且未访问过时, 才属于同一个块
                    if (is_prime[v] && !visited[v]) {
                        visited[v] = true;
                        current_block_sum += a[v];
                        q[rear++] = v;
                    }
                }
            }
        }

        // 贪心：如果这个块的总快乐值大于0, 就选它
        if (current_block_sum > 0) {
            total_happiness += current_block_sum;
        }
    }

    printf("%lld\n", total_happiness);

    return 0;
}
