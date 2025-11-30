// 问题：给定偶数 n 和 n 个编号 a[i]（范围在 [1..n]），
// 允许修改部分学生的编号，使调整后每个编号恰好被 2 名学生使用。
// 目标是最少修改人数。
//
// 思路（贪心）：
// 设 c[x] 为编号 x 的出现次数。最终我们必须选出正好 n/2 个“保留的编号”，
// 并让每个被选中的编号出现次数变为 2。
// 对于某个被选中的编号 x，最多可以“无修改”保留下 min(c[x], 2) 名学生。
// 因此，为了最大化“无需修改”的人数，我们应当选择 min(c[x], 2) 值尽可能大的 n/2 个编号。
// 因为 min(c[x], 2) ∈ {0,1,2}，策略等价为：
// 1) 优先选择所有 c[x] ≥ 2 的编号（每个能贡献 2），直到选满 n/2 个或没有更多；
// 2) 若仍未凑够 n/2 个编号，再用 c[x] = 1 的编号补足（每个能贡献 1）。
// 记 use2 为选到的 “c[x] ≥ 2 的编号数”，use1 为补充的 “c[x] = 1 的编号数”。
// 则“无需修改”的人数 = 2*use2 + use1；答案 = n - 无需修改人数。

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int n;
	if (scanf("%d", &n) != 1) {
		return 0;
	}
	if (n % 2 != 0 || n <= 0) {
		// 题目保证 n 为正偶数；若输入异常，温和处理。
		printf("0\n");
		return 0;
	}

	// 统计 1..n 各编号出现次数
	int *cnt = (int*)calloc((size_t)n + 1, sizeof(int));
	if (!cnt) return 0;

	for (int i = 0; i < n; ++i) {
		int x;
		if (scanf("%d", &x) != 1) x = 0;
		if (1 <= x && x <= n) {
			cnt[x]++;
		} else {
			// 若输入越界，本题按描述不应发生；这里忽略处理。
		}
	}

	int s2 = 0; // 满足 cnt >= 2 的编号个数
	int s1 = 0; // 满足 cnt == 1 的编号个数
	for (int x = 1; x <= n; ++x) {
		if (cnt[x] >= 2) ++s2;
		else if (cnt[x] == 1) ++s1;
	}

	int need = n / 2;
	int use2 = s2 < need ? s2 : need;
	int remaining = need - use2;
	int use1 = s1 < remaining ? s1 : remaining;

	int unchanged = 2 * use2 + use1;
	int answer = n - unchanged;
	if (answer < 0) answer = 0; // 安全兜底

	printf("%d\n", answer);

	free(cnt);
	return 0;
}

