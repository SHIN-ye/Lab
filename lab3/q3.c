#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 205
#define MAXM 205
#define MAXK 205

typedef struct {
    int score;
    char type;
} Ship;

Ship grid[MAXN][MAXM];
int n, m, k;

// dp[w][0]: 消耗 w 弹药，且所有含 N 的列都以 Y 结尾（不满足耗尽弹药的条件）
// dp[w][1]: 消耗 w 弹药，且至少有一列以 N 结尾（满足耗尽弹药的条件）
int dp[MAXK][2];
int next_dp[MAXK][2];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    if (scanf("%d %d %d", &n, &m, &k) != 3) return 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int f;
            char c;
            scanf("%d %c", &f, &c);
            grid[i][j].score = f;
            grid[i][j].type = c;
        }
    }

    // 初始化 DP
    for (int w = 0; w <= k; w++) {
        dp[w][0] = -1;
        dp[w][1] = -1;
    }
    dp[0][0] = 0;


    // 逐列处理（分组背包）
    for (int j = 0; j < m; j++) {
        // 初始化 next_dp
        for (int w = 0; w <= k; w++) {
            next_dp[w][0] = -1;
            next_dp[w][1] = -1;
        }

        // 枚举当前列击落的飞船数量 d (从 0 到 n)
        // 注意：输入是从上到下，攻击是从下到上
        // grid[n-1][j] 是最下面的飞船
        for (int d = 0; d <= n; d++) {
            int current_cost = 0;
            int current_score = 0;
            char top_type = 0; // 0:无, 'Y', 'N'

            if (d > 0) {
                for (int r = 0; r < d; r++) {
                    Ship s = grid[n - 1 - r][j];
                    current_score += s.score;
                    if (s.type == 'N') {
                        current_cost++;
                    }
                    if (r == d - 1) {
                        top_type = s.type;
                    }
                }
            }

            if (current_cost > k) continue;

            // 状态转移
            for (int w = 0; w <= k; w++) {
                int next_w = w + current_cost;
                if (next_w > k) continue;

                if (d == 0) {
                    // 不选该列的任何飞船，状态继承
                    if (dp[w][0] != -1) next_dp[w][0] = max(next_dp[w][0], dp[w][0]);
                    if (dp[w][1] != -1) next_dp[w][1] = max(next_dp[w][1], dp[w][1]);
                } else {
                    if (top_type == 'Y') {
                        // 以 Y 结尾，保持原有状态类型
                        if (dp[w][0] != -1) next_dp[next_w][0] = max(next_dp[next_w][0], dp[w][0] + current_score);
                        if (dp[w][1] != -1) next_dp[next_w][1] = max(next_dp[next_w][1], dp[w][1] + current_score);
                    } else if (top_type == 'N') {
                        // 以 N 结尾，无论之前是什么状态，现在都变成了“存在以 N 结尾的列”
                        if (dp[w][0] != -1) next_dp[next_w][1] = max(next_dp[next_w][1], dp[w][0] + current_score);
                        if (dp[w][1] != -1) next_dp[next_w][1] = max(next_dp[next_w][1], dp[w][1] + current_score);
                    }
                }
            }
        }
        
        // 更新 DP 数组
        for (int w = 0; w <= k; w++) {
            dp[w][0] = next_dp[w][0];
            dp[w][1] = next_dp[w][1];
        }
    }

    int ans = 0;
    // 情况 1: 消耗 < k，任何状态都合法
    for (int w = 0; w < k; w++) {
        if (dp[w][0] != -1) ans = max(ans, dp[w][0]);
        if (dp[w][1] != -1) ans = max(ans, dp[w][1]);
    }
    // 情况 2: 消耗 = k，必须是状态 1 (以 N 结尾)
    if (dp[k][1] != -1) ans = max(ans, dp[k][1]);

    printf("%d\n", ans);

    return 0;
}