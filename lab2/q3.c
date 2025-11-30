// 题目：计算 F_n mod 1e9+7，其中 F1 = 1，Fn = F(n-1) + F(n-2) (n>=2)
// 要求：60 < n < 2^31 - 1
// 解法：矩阵快速幂（O(log n)）。基础矩阵 B=[[1,1],[1,0]]，有 B^n = [[F_{n+1}, F_n],[F_n, F_{n-1}]]。

#include <stdio.h>
#include <stdint.h>

#define MOD 1000000007ULL

typedef struct {
	uint64_t a11, a12;
	uint64_t a21, a22;
} Mat2;

static inline uint64_t addm(uint64_t x, uint64_t y) {
	uint64_t s = x + y;
	if (s >= MOD) s -= MOD;
	return s;
}

static inline uint64_t mulm(uint64_t x, uint64_t y) {
	// 在 uint64 下安全：(MOD-1)^2 < 2^64
	return (x * y) % MOD;
}

static inline Mat2 mat_mul(Mat2 A, Mat2 B) {
	Mat2 C;
	C.a11 = (mulm(A.a11, B.a11) + mulm(A.a12, B.a21)) % MOD;
	C.a12 = (mulm(A.a11, B.a12) + mulm(A.a12, B.a22)) % MOD;
	C.a21 = (mulm(A.a21, B.a11) + mulm(A.a22, B.a21)) % MOD;
	C.a22 = (mulm(A.a21, B.a12) + mulm(A.a22, B.a22)) % MOD;
	return C;
}

static inline Mat2 mat_pow(Mat2 base, uint64_t n) {
	// 幂为 0 时返回单位矩阵 I
	Mat2 res = {1, 0, 0, 1};
	while (n) {
		if (n & 1ULL) res = mat_mul(res, base);
		base = mat_mul(base, base);
		n >>= 1;
	}
	return res;
}

int main(void) {
	// 标准定义：F0=0, F1=1。对 n=0 特判，其余用 B^n 取到 F_n。
	uint64_t n;
	if (scanf("%llu", &n) != 1) return 0;

	if (n == 0) {
		printf("0\n");
		return 0;
	}

	Mat2 B = {1, 1, 1, 0};
	Mat2 P = mat_pow(B, n); // P = B^n = [[F_{n+1}, F_n],[F_n, F_{n-1}]]
	printf("%llu\n", P.a12 % MOD); // 输出 F_n
	return 0;
}

