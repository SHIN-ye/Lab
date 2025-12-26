#include <stdio.h>
#include <stdlib.h>

#define MAXN 5005
#define MAXM 100005

typedef struct {
    int u, v, w; //起点u, 终点v, 权重w
} Edge;

Edge edges[MAXM];
int parent[MAXN];

int compare(const void *a, const void *b) {
    return ((Edge *)a)->w - ((Edge *)b)->w;
}

int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]);
}

void unite(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    if (root_i != root_j) {
        parent[root_i] = root_j;
    }
}

int main() {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    qsort(edges, M, sizeof(Edge), compare);

    for (int i = 1; i <= N; i++) {
        parent[i] = i;
    }

    long long total_cost = 0;
    int edges_count = 0;

    for (int i = 0; i < M; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        if (find(u) != find(v)) {
            unite(u, v);
            total_cost += w;
            edges_count++;
        }
    }

    if (edges_count == N - 1) {
        printf("%lld\n", total_cost);
    } else {
        printf("-1\n");
    }

    return 0;
}
