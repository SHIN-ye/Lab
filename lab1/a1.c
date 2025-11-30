#include <stdio.h>
#include <stdlib.h>

void merge (long long *arr, int left, int  mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    long long *L = (long long *)malloc((size_t)n1 * sizeof(long long));
    long long *R = (long long *)malloc((size_t)n2 * sizeof(long long));

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

 void mergeSort(long long *arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
 }
int count_accord(long long *arr, int len, long long limit ) {
    int l = 0, r = len;
    while(l < r) {
        int mid = l + (r - l) / 2;
        if(arr[mid] <= limit) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    return l;
}

int check_condition(long long x, long long *arr, int N, long long Sum ) {
    long long Sum_total = Sum + x;
    long  long limit = (Sum_total - 1) / (2LL * N);
    int count = 0;
    if (N > 1) {
		count = count_accord(arr, N - 1, limit);
	}
    long long largest = arr[N - 1] + x;
    long long scaled = 2LL * N * largest;
    if (scaled < Sum_total) {
        count++;
    }
    return count > N / 2;
}

int main() {
    int N;
    scanf("%d", &N);
    if (N <= 2) {
        printf("-1\n");
        return 0;
    }
    long long *arr = (long long*)malloc(sizeof(long long) * (size_t)N);
    if (arr == NULL) {
        printf("Memory allocation failed\n");
    }
    long long Sum = 0;
    for (int i = 0; i < N; i++) {
        long long a = 0;
        scanf("%lld", &a);
        arr[i] = a;
        Sum += a;
    }
    mergeSort(arr, 0, N - 1);

    if (check_condition(0, arr, N, Sum)) {
        printf("0\n");
        free(arr);
        return 0;
    }
    long long lo = 0;
    long long hi = 2LL * N * arr[N - 1] - Sum;
    if (!check_condition(hi, arr, N, Sum)) {
		if (hi == 0) {
			hi = 1;
		}
		while (!check_condition(hi, arr, N, Sum)) {
			hi <<= 1;
		}
	}
    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (check_condition(mid, arr, N, Sum)){
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    printf("%lld", lo);
    free(arr);
    return 0;
}

