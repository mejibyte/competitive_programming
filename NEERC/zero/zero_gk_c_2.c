#include<stdio.h>
__int64 a[100000];
int i, n;

int main() {
    freopen("zero.in", "r", stdin);
    freopen("zero.out", "w", stdout);

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%I64d", a + i);
    }

    for (i = n - 1; i >= 0; i--) {
        printf("%I64d ", a[i]);
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}
