#include <stdio.h>
#include <string.h>

void del_CRLF(char *s) {
    size_t n = 0;
    while (s[n] != '\0' && s[n] != '\n' && s[n] != '\r') {
        n++;
    }
    s[n] = '\0';
}

void postorder(char *preorder, int in_l, int in_r, int pre_l, int pre_r, int pos[256]) {
    if (pre_l > pre_r || in_l > in_r) return;
    char root = preorder[pre_l];
    int k = pos[(unsigned char)root];
    int left_size = k - in_l;
    postorder(preorder, in_l, k - 1, pre_l + 1, pre_l + left_size, pos);
    postorder(preorder, k + 1, in_r, pre_l + left_size + 1, pre_r, pos);
    putchar(root);
}

int main() {
    char inorder[128];
    char preorder[128];

    fgets(inorder, sizeof(inorder), stdin);
    fgets(preorder, sizeof(preorder), stdin);
    del_CRLF(inorder);
    del_CRLF(preorder);

    int n = (int)strlen(inorder);
    int pos[256];

    for (int i = 0; i < 256; i++) {
        pos[i] = -1;
    }
    for (int i = 0; i < n; i++) {
        pos[(unsigned char)inorder[i]] = i;
    }
    postorder(preorder, 0, n - 1, 0, n - 1, pos);
    putchar('\n');

    return 0;
}