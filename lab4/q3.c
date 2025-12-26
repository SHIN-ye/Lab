#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005
#define MAX_COMPONENTS 1000005

// 地图
char map[MAXN][MAXN];
// 记录每个点所属的连通块ID
int component_id[MAXN][MAXN];
// 记录每个连通块的大小
int component_size[MAX_COMPONENTS];

// 方向数组:上下左右
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// BFS队列节点
typedef struct {
    int x, y;
} Point;

Point q[MAXN * MAXN];

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;

    // 读取地图
    for (int i = 1; i <= n; i++) {
        scanf("%s", map[i] + 1); // 从下标1开始存储
    }

    int current_id = 0;

    // 遍历所有点,进行BFS预处理
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            // 如果该点未被访问过,说明发现了一个新的连通块
            if (component_id[i][j] == 0) {
                current_id++;
                int size = 0;
                
                // BFS初始化
                int front = 0, rear = 0;
                q[rear++] = (Point){i, j};
                component_id[i][j] = current_id;
                size++;

                while (front < rear) {
                    Point curr = q[front++];
                    
                    for (int k = 0; k < 4; k++) {
                        int nx = curr.x + dx[k];
                        int ny = curr.y + dy[k];

                        // 边界检查
                        if (nx >= 1 && nx <= n && ny >= 1 && ny <= n) {
                            // 如果未访问过,且特产类型不同(0 vs 1)
                            if (component_id[nx][ny] == 0 && map[nx][ny] != map[curr.x][curr.y]) {
                                component_id[nx][ny] = current_id;
                                size++;
                                q[rear++] = (Point){nx, ny};
                            }
                        }
                    }
                }
                // 记录该连通块的大小
                component_size[current_id] = size;
            }
        }
    }

    // 处理查询
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        // 直接查表输出
        printf("%d\n", component_size[component_id[x][y]]);
    }

    return 0;
}
