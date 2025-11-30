// 题意：有 n 个人、k 个行业。每个人当前所在行业为 a[i]，若说服其改行成本为 b[i]。
// 目标：通过说服若干人改行，使得每个行业至少有 1 人，且总成本最小。
// 思路（贪心）：
// - 设缺失行业数量 m = 统计有多少行业人数为 0。
// - 任一非空行业至少要保留 1 人，因此该行业可“外迁”的名额为 cnt[j]-1。
// - 将所有人按改行成本 b 升序排序，依次选择其所在行业仍有可外迁名额 (cnt[j]-1 尚未用尽) 的人外迁，直到选满 m 人。
//   由于选择总数固定为 m，且对每个行业只受“最多外迁 cnt[j]-1 人”的约束，
//   直接按成本从小到大选择可外迁的人可得最小总成本。

#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
	ll cost;   // b[i]
	int ind;   // a[i]
} Person;

static int cmp_person(const void *pa, const void *pb) {
	const Person *x = (const Person *)pa;
	const Person *y = (const Person *)pb;
	if (x->cost < y->cost) return -1;
	if (x->cost > y->cost) return 1;
	// 次序任意
	return 0;
}

int main(void) {
	int n, k;
	if (scanf("%d %d", &n, &k) != 2) return 0;
	int *a = (int *)malloc(sizeof(int) * (size_t)n);
	ll *b = (ll *)malloc(sizeof(ll) * (size_t)n);
	if (!a || !b) {
		free(a); free(b);
		return 0;
	}

	for (int i = 0; i < n; ++i) {
		if (scanf("%d", &a[i]) != 1) a[i] = 1;
	}
	for (int i = 0; i < n; ++i) {
		if (scanf("%lld", &b[i]) != 1) b[i] = 0;
	}

	// 统计各行业人数
	int *cnt = (int *)calloc((size_t)k + 1, sizeof(int));
	if (!cnt) {
		free(a); free(b);
		return 0;
	}
	for (int i = 0; i < n; ++i) {
		if (a[i] >= 1 && a[i] <= k) cnt[a[i]]++;
	}

	// 缺失行业数量 m
	int missing = 0;
	for (int j = 1; j <= k; ++j) if (cnt[j] == 0) ++missing;
	if (missing == 0) {
		printf("0\n");
		free(a); free(b); free(cnt);
		return 0;
	}

	// 可外迁名额：每个行业最多外迁 cnt[j]-1 人
	int *movable = (int *)malloc(sizeof(int) * ((size_t)k + 1));
	if (!movable) {
		free(a); free(b); free(cnt);
		return 0;
	}
	for (int j = 1; j <= k; ++j) movable[j] = (cnt[j] > 0 ? cnt[j] - 1 : 0);

	// 将所有人按成本排序
	Person *arr = (Person *)malloc(sizeof(Person) * (size_t)n);
	if (!arr) {
		free(a); free(b); free(cnt); free(movable);
		return 0;
	}
	for (int i = 0; i < n; ++i) {
		arr[i].cost = b[i];
		arr[i].ind = (a[i] >= 1 && a[i] <= k) ? a[i] : 1;
	}
	qsort(arr, (size_t)n, sizeof(Person), cmp_person);

	ll ans = 0;
	int need = missing;
	for (int i = 0; i < n && need > 0; ++i) {
		int j = arr[i].ind;
		if (movable[j] > 0) {
			ans += arr[i].cost;
			movable[j]--;
			--need;
		}
	}

	// 理论上总可外迁人数 n - 非空行业数 >= 缺失行业数，故一定能满足 need==0
	printf("%lld\n", ans);

	free(a); free(b); free(cnt); free(movable); free(arr);
	return 0;
}

