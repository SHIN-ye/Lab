#include <stdio.h>
#include <stdlib.h>

typedef long long ll;
typedef struct {
    ll l , r;
} report; 

int cmp(const void *a, const void *b) {
    const report *ra = (const report *)a;
    const report *rb = (const report *)b;
    if (ra->r != rb->r) return (ra->r < rb->r) ? -1 : 1;
    if (ra->l != rb->l) return (ra->l < rb->l) ? -1 : 1;
    return 0;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    
    report *group = (report *)malloc(sizeof(report) * n);
    if (group == NULL) return 0;

    int count = 0;
    ll end_time = -1;

    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &group[i].l, &group[i].r);
    }

    qsort(group, n, sizeof(report), cmp);

    for (int i = 0; i < n; i++) {
        if (group[i].l >= end_time) {
            count++;
            end_time = group[i].r;
        }
    }

    printf("%d\n", count);
    free(group);
    return 0;
}