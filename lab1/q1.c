// 采用 a1.c 中的归并排序思路，对输入数据排序后通过二分寻找最小满足条件的 x。
/*外层二分：在变量 x 上二分，寻找满足条件的最小追加量。随着 x 增大，条件从“不满足”变成“满足”，这是一个典型的单调判定问题，所以用二分迅速锁定最小可行的 x。
内层二分(count_less_equal)：为了高效统计已经排序好的数组中, 有多少瓶子的药量不超过给定阈值。排序后使用二分查找第一个大于阈值的位置位置, O(log n) 时间就能得到数量，从而让判定函数 check_condition 的复杂度也保持在 O(log n)。
*/
#include <stdio.h>
#include <stdlib.h>

static void merge(long long *arr, int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;
	long long *L = (long long *)malloc((size_t)n1 * sizeof(long long));
	long long *R = (long long *)malloc((size_t)n2 * sizeof(long long));
	if (!L || !R) {
		free(L);
		free(R);
		exit(1);
	}
	for (int i = 0; i < n1; ++i) {
		L[i] = arr[left + i];
	}
	for (int j = 0; j < n2; ++j) {
		R[j] = arr[mid + 1 + j];
	}
	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k++] = L[i++];
		} else {
			arr[k++] = R[j++];
		}
	}
	while (i < n1) {
		arr[k++] = L[i++];
	}
	while (j < n2) {
		arr[k++] = R[j++];
	}
	free(L);
	free(R);
}

static void mergeSort(long long *arr, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		mergeSort(arr, left, mid);
		mergeSort(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}
}

static int count_less_equal(const long long *arr, int len, long long limit) {
	int l = 0, r = len;
	while (l < r) {
		int mid = l + (r - l) / 2;
		if (arr[mid] <= limit) {
			l = mid + 1;
		} else {
			r = mid;
		}
	}
	return l;
}

static int check_condition(long long x, const long long *arr, int n, long long sum) {
	long long total = sum + x;
	long long twice_n = 2LL * n;
	long long limit = (total - 1) / twice_n;
	int count = 0;
	if (n > 1) {
		count = count_less_equal(arr, n - 1, limit);
	}
	long long largest = arr[n - 1] + x;
	long long scaled = twice_n * largest;
	if (scaled < total) {
		count++;
	}
	return count > n / 2;
}

int main(void) {
	int n;
	if (scanf("%d", &n) != 1) {
		return 0;
	}
	if (n <= 0) {
		printf("-1\n");
		return 0;
	}
	if (n <= 2) {
		for (int i = 0; i < n; ++i) {
			long long tmp;
			if (scanf("%lld", &tmp) != 1) {
				break;
			}
		}
		printf("-1\n");
		return 0;
	}

	long long *arr = (long long *)malloc((size_t)n * sizeof(long long));
	if (!arr) {
		fprintf(stderr, "Memory allocation failed\n");
		return 0;
	}

	long long sum = 0;
	for (int i = 0; i < n; ++i) {
		long long value = 0;
		if (scanf("%lld", &value) != 1) {
			value = 0;
		}
		arr[i] = value;
		sum += value;
	}

	mergeSort(arr, 0, n - 1);

	if (check_condition(0, arr, n, sum)) {
		printf("0\n");
		free(arr);
		return 0;
	}

	long long hi = 2LL * n * arr[n - 2] - sum + 1;
	if (hi < 0) {
		hi = 0;
	}
	if (!check_condition(hi, arr, n, sum)) {
		if (hi == 0) {
			hi = 1;
		}
		while (!check_condition(hi, arr, n, sum)) {
			hi <<= 1;
		}
	}

	long long lo = 0;
	while (lo < hi) {
		long long mid = lo + (hi - lo) / 2;
		if (check_condition(mid, arr, n, sum)) {
			hi = mid;
		} else {
			lo = mid + 1;
		}
	}

	printf("%lld\n", lo);
	free(arr);
	return 0;
}

