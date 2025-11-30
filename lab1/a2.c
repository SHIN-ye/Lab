#include<stdio.h>
#include<math.h>

long long select_insert_bubble_sort(long long n) {
    return n * (n - 1) / 2;
}

int ceil_log2_ll(long long n) {
    if (n <= 1) return 0;               
    unsigned long long x = (unsigned long long)(n - 1); 
    int k = 0;
    while (x) { 
        x >>= 1; 
        k++; 
    }
    return k;
}

long long merge_sort(long long n) {
    int k = ceil_log2_ll(n);
    unsigned long long two_k = 1ULL << k;  
    long long result = n * (long long)k - (long long)two_k + 1;
    return result;
}

int main() {
    long long n;
    if(scanf("%lld", &n) != 1) {
        return 1;
    }

    if(n <= 0) {
        return 1;
    }

    long long select_ops = select_insert_bubble_sort(n);
    long long merge_ops = merge_sort(n);

    if(select_ops < merge_ops) {
        printf("%lld\n", select_ops);
    } else {
        printf("%lld\n", merge_ops);
    }

    return 0;
}