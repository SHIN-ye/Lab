// 判断二叉树是否轴对称（镜像对称）
// 输入：
//   第一行：N (1 ≤ N ≤ 1e5)
//   第二行：N 个整数，表示层序遍历，-1 表示空节点
// 输出：
//   Yes 或 No

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static inline bool is_null(const int *a, int n, long long idx) {
	return (idx >= n) || (a[idx] == -1);
}

int main(void) {
	int N;
	if (scanf("%d", &N) != 1) {
		return 0;
	}
	if (N <= 0) {
		printf("No\n");
		return 0;
	}

	int *arr = (int *)malloc(sizeof(int) * (size_t)N);
	if (!arr) {
		fprintf(stderr, "Memory allocation failed.\n");
		return 0;
	}
	for (int i = 0; i < N; ++i) {
		if (scanf("%d", &arr[i]) != 1) {
			free(arr);
			return 0;
		}
	}

	// 队列保存成对的索引 (i, j)，检查是否镜像
	// 规模上限：最多推进约 2 * 非空节点对，分配 2*N 足够
	long long cap = (long long)N * 2 + 4;
	long long *qi = (long long *)malloc(sizeof(long long) * (size_t)cap);
	long long *qj = (long long *)malloc(sizeof(long long) * (size_t)cap);
	if (!qi || !qj) {
		free(arr);
		free(qi);
		free(qj);
		fprintf(stderr, "Memory allocation failed.\n");
		return 0;
	}

	long long head = 0, tail = 0;
	// 根与根成对开始
	qi[tail] = 0; qj[tail] = 0; ++tail;

	bool ok = true;
	while (head < tail) {
		long long i = qi[head];
		long long j = qj[head];
		++head;

		bool ni = is_null(arr, N, i);
		bool nj = is_null(arr, N, j);
		if (ni && nj) continue;          // 都为空，镜像成立
		if (ni || nj) { ok = false; break; } // 只有一个为空
		if (arr[i] != arr[j]) { ok = false; break; }

		// 入队镜像孩子：(left(i), right(j)) 与 (right(i), left(j))
		long long li = 2 * i + 1;
		long long ri = 2 * i + 2;
		long long lj = 2 * j + 1;
		long long rj = 2 * j + 2;

		// 扩容保护（极限情况下）
		if (tail + 2 >= cap) {
			long long new_cap = cap * 2;
			long long *nqi = (long long *)realloc(qi, sizeof(long long) * (size_t)new_cap);
			long long *nqj = (long long *)realloc(qj, sizeof(long long) * (size_t)new_cap);
			if (!nqi || !nqj) { ok = false; break; }
			qi = nqi; qj = nqj; cap = new_cap;
		}

		qi[tail] = li; qj[tail] = rj; ++tail;
		qi[tail] = ri; qj[tail] = lj; ++tail;
	}

	printf(ok ? "Yes\n" : "No\n");

	free(arr);
	free(qi);
	free(qj);
	return 0;
}

