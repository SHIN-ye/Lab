// 根据给定的中序序列与前序序列，输出后序序列
// 输入：两行字符串（仅包含大写字母），第一行为中序，第二行为前序
// 输出：一行字符串，为对应二叉树的后序遍历

#include <stdio.h>
#include <string.h>

// 递归：直接用区间索引计算后序输出，无需显式建树
static void post_from_pre_in(const char *pre, int preL, int preR,
							 int inL, int inR, const int pos[256]) {
	if (preL > preR || inL > inR) return;
	char root = pre[preL];
	int k = pos[(unsigned char)root];
	int leftSize = k - inL;
	// 左子树：前序[preL+1 .. preL+leftSize]，中序[inL .. k-1]
	post_from_pre_in(pre, preL + 1, preL + leftSize, inL, k - 1, pos);
	// 右子树：前序[preL+leftSize+1 .. preR]，中序[k+1 .. inR]
	post_from_pre_in(pre, preL + leftSize + 1, preR, k + 1, inR, pos);
	// 根
	putchar(root);
}

// 去除行末换行符（兼容 Windows 的 \r\n）
static void chomp(char *s) {
	size_t n = strcspn(s, "\r\n");
	s[n] = '\0';
}

int main(void) {
	char inorder[128];
	char preorder[128];

	if (!fgets(inorder, sizeof(inorder), stdin)) return 0;
	if (!fgets(preorder, sizeof(preorder), stdin)) return 0;
	chomp(inorder);
	chomp(preorder);

	int n = (int)strlen(inorder);
	// 构造字符到中序下标的映射，便于 O(1) 查找分割点
	int pos[256];
	for (int i = 0; i < 256; ++i) pos[i] = -1;
	for (int i = 0; i < n; ++i) pos[(unsigned char)inorder[i]] = i;

	if (n > 0) {
		post_from_pre_in(preorder, 0, n - 1, 0, n - 1, pos);
	}
	putchar('\n');
	return 0;
}

