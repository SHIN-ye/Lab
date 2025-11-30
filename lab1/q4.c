    #include <stdio.h>
    #include <stdlib.h>

    int main() {
        int n;
        int s2 = 0; // 编号人数大于等于2的编号
        int s1 = 0; // 编号人数等于1的编号
        scanf("%d", &n);
        int number = n / 2;
        int *arr = (int *)calloc((n + 1) * sizeof(int));
        if (arr == NULL) {
            return 1; 
        }
        for (int i = 0; i < n; i++) {
            int a;
            scanf("%d", &a);
            if (a >= 1 && a <= n) {
                arr[a]++;
            }
        }

        for (int i = 1; i < n + 1; i++) {
            if (arr[i] >= 2) {
                s2++;
            } else if (arr[i] == 1) {
                s1++;
            }
        }
        int use2 = s2 < number ? s2 : number;
        int need = number - use2;
        int use1 = s1 < need ? s1 : need;
        int total = n - use2 * 2 - use1;
        printf("%d\n", total);
        free(arr);
        return 0;

    }