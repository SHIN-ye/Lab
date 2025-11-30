// 计算四种排序算法在最坏情况下的比较次数，并输出其中的最小值
// 选择/插入/冒泡：最坏比较次数均为 n*(n-1)/2（元素间比较次数，与数据无关或为最坏排列时达到）
// 归并排序（自顶向下二分合并）：最坏比较次数为 n*ceil(log2 n) - 2^{ceil(log2 n)} + 1

#include <stdio.h>

typedef long long ll;

static inline ll worst_simple(ll n) {
	// 选择/插入/冒泡的最坏比较次数（元素间比较）
	return n * (n - 1) / 2;
}

static inline int ceil_log2_ll(ll n) {
	// 返回 ceil(log2(n))，约定 n>=1
	if (n <= 1) return 0;
	ll x = n - 1; // ceil(log2 n) == floor(log2(n-1)) + 1 (n>=2)
	int k = 0;
	while (x > 0) {
		x >>= 1;
		++k;
	}
	return k;
}

static inline ll worst_merge(ll n) {
	int k = ceil_log2_ll(n);
	ll pow2k = 1LL << k; // k<=30 when n<=1e9，安全
	return n * (ll)k - pow2k + 1;
}

int main(void) {
	ll n;
	if (scanf("%lld", &n) != 1) return 0;
	if (n < 1) {
		// 按题意 n>=1，这里做个兜底
		printf("0\n");
		return 0;
	}
	ll simple = worst_simple(n);
	ll mergec = worst_merge(n);
	ll ans = (simple < mergec) ? simple : mergec;
	printf("%lld\n", ans);
	return 0;
}

