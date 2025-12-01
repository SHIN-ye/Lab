#include <stdio.h>
#include <stdlib.h>

#define MAXN 5005

int n;
long long a[MAXN];
long long S[MAXN];
long long dp[MAXN];
int q[MAXN];

int check(long long limit) {
    int head = 0, tail = -1;
    int min_j = 0;
    
    dp[0] = 0;
    q[++tail] = 0; 
    
    for (int i = 1; i <= n + 1; i++) {
        long long target = S[i-1] - limit;
        while (min_j < i && S[min_j] < target) {
            min_j++;
        }
        
        while (head <= tail && q[head] < min_j) {
            head++;
        }
        
        if (head > tail) {
            dp[i] = 2000000000000000000LL; 
        } else {
            int best_j = q[head];
            dp[i] = dp[best_j] + a[i];
        }
        
        if (i <= n) {
            while (head <= tail && dp[q[tail]] >= dp[i]) {
                tail--;
            }
            q[++tail] = i;
        }
    }
    
    return dp[n+1] <= limit;
}

int main() {
    if (scanf("%d", &n) != 1) return 0;
    
    S[0] = 0;
    long long sum_all = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        S[i] = S[i-1] + a[i];
        sum_all += a[i];
    }
    
    a[n+1] = 0;
    
    long long low = 0, high = sum_all;
    long long ans = sum_all;
    
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        if (check(mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    
    printf("%lld\n", ans);
    
    return 0;
}