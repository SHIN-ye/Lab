#include <stdio.h>
#include <limits.h>

int main(void) {
	int n;
    scanf("%d", &n);
	long long best = LLONG_MIN;
	long long current = LLONG_MIN;
	for (int i = 0; i < n; i++) {
		long long x;
		scanf("%lld", &x);
		if (current == LLONG_MIN) {
			current = x;             
		} else {
			long long extend = current + x;
			current = (extend > x) ? extend : x;
		}
		if (current > best) best = current;  
	}

	printf("%lld\n", best);
	return 0;
}

