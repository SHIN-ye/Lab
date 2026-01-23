#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 基于四分法的 Rabin-Karp 加速近似匹配（允许汉明距离 <= 3）
// 对于每个测试样例：
//  - 读入 s, t
//  - 若 |t| <= 3，直接暴力滑窗统计汉明距离 <= 3 的位置
//  - 否则将 t 划分为 4 段，对每段在 s 中做精确匹配（Rabin-Karp 滚动哈希），
//    将能使得某段对齐的位置作为候选起点，最后对候选进行逐字符验证。

typedef unsigned long long ull;

// 计算字符串 s 从 pos 长度 len 的滚动哈希（基于 ull 溢出）
static inline int map_char(char c) {
	switch (c) {
		case 'A': case 'a': return 0;
		case 'C': case 'c': return 1;
		case 'G': case 'g': return 2;
		case 'T': case 't': return 3;
		default: return (unsigned char)c + 4; // 保底映射
	}
}

static inline ull calc_hash(const char *s, int pos, int len, ull base) {
	ull h = 0;
	for (int i = 0; i < len; ++i) h = h * base + (ull)(map_char(s[pos + i]) + 1);
	return h;
}

int main() {
	int T;
	if (scanf("%d", &T) != 1) return 0;

	// 预分配足够大的缓冲（题目长度上限约 1e5）
	int maxN = 200000 + 5;
	char *s = (char*)malloc(maxN);
	char *t = (char*)malloc(maxN);

	const ull BASE = 1315423911ULL; // 随机选一个较大的基，使用 ull 模 2^64

	while (T--) {
		if (scanf("%s", s) != 1) break;
		if (scanf("%s", t) != 1) break;
		int n = (int)strlen(s);
		int m = (int)strlen(t);

		if (n < m) { printf("0\n"); continue; }

		// 使用四分法 Rabin-Karp 筛选候选（所有情况统一使用）

		int slots = n - m + 1;
		int *mark = (int*)calloc(slots, sizeof(int));

		// 将 m 分成 4 段，长度尽量均匀
		int base_len = m / 4;
		int extra = m % 4;
		int offsets[4];
		int lens[4];
		int cur = 0;
		for (int b = 0; b < 4; ++b) {
			offsets[b] = cur;
			lens[b] = base_len + (b < extra ? 1 : 0);
			cur += lens[b];
		}

		// 对每一段进行 RK 匹配
		for (int b = 0; b < 4; ++b) {
			int L = lens[b];
			if (L == 0) continue;
			int ofs = offsets[b];

			ull hash_t = calc_hash(t, ofs, L, BASE);

			// 计算 s 的首窗口哈希
			ull hash_s = 0;
			for (int i = 0; i < L; ++i) hash_s = hash_s * BASE + (ull)(map_char(s[i]) + 1);
			// 预计算 BASE^L
			ull powL = 1;
			for (int i = 0; i < L; ++i) powL *= BASE;

			if (hash_s == hash_t) {
				// 逐字符验证避免碰撞
				if (memcmp(s + 0, t + ofs, L) == 0) {
					int start = 0 - ofs;
					if (start >= 0 && start < slots) mark[start] = 1;
				}
			}

			for (int i = 1; i + L <= n; ++i) {
				// 从位置 i-1 滑到 i
				// hash_s = hash_s * BASE - s[i-1]*BASE^L + s[i+L-1]
				hash_s = hash_s * BASE - (ull)(map_char(s[i-1]) + 1) * powL + (ull)(map_char(s[i+L-1]) + 1);

				if (hash_s == hash_t) {
					// 验证
					if (memcmp(s + i, t + ofs, L) == 0) {
						int start = i - ofs;
						if (start >= 0 && start < slots) mark[start] = 1;
					}
				}
			}
		}

		// 对候选位置验证汉明距离
		int ans = 0;
		for (int i = 0; i < slots; ++i) {
			if (!mark[i]) continue;
			int diff = 0;
			for (int j = 0; j < m; ++j) {
				if (s[i + j] != t[j]) { if (++diff > 3) break; }
			}
			if (diff <= 3) ++ans;
		}

		printf("%d\n", ans);

		free(mark);
	}

	free(s);
	free(t);
	return 0;
}

