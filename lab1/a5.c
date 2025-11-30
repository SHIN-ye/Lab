#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    ll cost;   
    int ind;   
} person;

int compare(const void *a, const void *b) {
    return (int)(((person *)a)->cost - ((person *)b)->cost);
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int *a = (int *)malloc(n * sizeof(int));
    ll *b = (ll *)malloc(n * sizeof(ll));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%lld", &b[i]);
    }

    int *count = (int *)calloc(k + 1, sizeof(int));
    for (int i = 0; i < n; i++) {
        count[a[i]]++;
    }

    int missing = 0;
    for (int i = 1; i <= k; i++) {
        if (count[i] == 0) {
            missing++;
        }
    }

    int *move = (int *)calloc(k + 1, sizeof(int));
    for (int i = 1; i <= k; i++) {
        if (count[i] > 0) {
            move[i] = count[i] > 1 ? count[i] - 1 : 0;
        }
    }

    person *people = (person *)malloc(n * sizeof(person));
    for (int i = 0; i < n; i++) {
        people[i].cost = b[i];
        people[i].ind = (a[i] >= 1 && a[i] <= k) ? a[i] : 1;;
    }

    qsort(people, n, sizeof(person), compare);

    ll min = 0;
    int need = missing;
    for (int i = 0; i < n && need > 0; i++) {
        int j = people[i].ind;
        if (move[j] > 0) {
            ll cost = people[i].cost;
            min += cost;
            move[j]--;
            need--;
        }
    }
    
    printf("%lld\n", min);
    free(a);
    free(b);
    free(count);
    free(move);
    free(people);
    return 0;
}