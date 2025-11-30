#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int judge_NULL(int *a, int N, ll idx) {
    return (idx >= N) || (a[idx] == -1);
}
// ตÝน้
int compare(int *a, int N ,ll i, ll j) {
    int ni = judge_NULL(a, N, i);
    int nj = judge_NULL(a, N, j);
    if (ni && nj) return 1;
    if (ni || nj) return 0;
    if (a[i] != a[j]) return 0;
    return compare(a, N, 2 * i + 1, 2 * j + 2) && compare(a, N, 2 * i + 2, 2 * j + 1);
}

int main() {
    int N;
    scanf("%d", &N);
    
    int *arr = (int *)malloc(N * sizeof(int));
    if (!arr) {
        return 0;
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }
    int result = compare(arr, N, 0, 0);
    printf(result ? "Yes\n" : "No\n");
    free(arr);
    return 0;
}