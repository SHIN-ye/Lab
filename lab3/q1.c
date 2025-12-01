#include<stdio.h>
#include<limits.h>

#define MAX 300

int dp[MAX][MAX];
int sum[MAX];
int m[MAX];

int main() {
    int N;
    scanf("%d", &N);

    for (int i = 1; i <= N; i++) {
        scanf("%d", &m[i]);
        sum[i] = sum[i - 1] + m[i];
        dp[i][i] = 0; // 合并自身代价为0
    }

    for (int len = 2; len <= N; len++) {
        for (int i = 1; i <= N - len + 1; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;

            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k + 1][j] + sum[j] - sum[i - 1];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                }
            }
        }
    }
    printf("%d\n", dp[1][N]);
    return 0;
}