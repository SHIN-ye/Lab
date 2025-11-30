#include <stdio.h>
#include <stdint.h>
// 矩阵快速幂
/*模运算是环同态，满足：
(a + b) mod M = ((a mod M) + (b mod M)) mod M
(a × b) mod M = ((a mod M) × (b mod M)) mod M
*/
#define MOD 1000000007ULL

typedef struct {
    uint64_t a11, a12;
    uint64_t a21, a22;
} matrix;

uint64_t mul(uint64_t x, uint64_t y) {
    return (x * y) % MOD;
}

matrix mat_mul(matrix A, matrix B) {
    matrix C;
    C.a11 = (mul(A.a11, B.a11) + mul(A.a12, B.a21)) % MOD;
    C.a12 = (mul(A.a11, B.a12) + mul(A.a12, B.a22)) % MOD;
    C.a21 = (mul(A.a21, B.a11) + mul(A.a22, B.a21)) % MOD;
    C.a22 = (mul(A.a21, B.a12) + mul(A.a22, B.a22)) % MOD;
    return C;
}

matrix mat_pow(matrix base, uint64_t n) {
    matrix res = {1, 0, 0, 1}; // 单位矩阵
    while (n) {
        if (n & 1ULL) res = mat_mul(res, base);
        base = mat_mul(base, base);
        n >>= 1;
    }
    return res;
}

int main() {
    uint64_t n;
    scanf("%llu", &n);

    matrix B = {1, 1, 1, 0};
    matrix P = mat_pow(B, n); 
    printf("%llu\n", P.a12); 
    return 0;
}