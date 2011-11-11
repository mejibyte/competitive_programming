// Andrés Mejía
#include <cstdio>
#include <cassert>

const int MAXN = 2005;

int m[MAXN][MAXN], left[MAXN], right[MAXN], down[MAXN], up[MAXN];

char buf[MAXN];

int main(){
    int n;
    while (scanf("%d ", &n) == 1) {
        for (int i = 0; i < n; ++i) left[i] = right[i] = down[i] = up[i] = 0;
        for (int i = 0; i < n; ++i) {
            gets(buf);
            for (int j = 0; j < n; ++j) {
                m[i][j] = buf[j] - '0';
            }
        }
        
        int ans = 0;
        for (int len = 1; len < n; ++len) {
            int i, j;
            
            // lower left
            i = n - len;
            j = 0;
            for (int k = 0; k < len; ++k) {
                int sum = left[i] + down[j];
                if (sum % 2 != m[i][j]) {
                    left[i]++, down[j]++, ans++;
                }
                i++, j++;
            }
            
            // upper right
            i = 0;
            j = n - len;
            for (int k = 0; k < len; ++k) {
                int sum = right[i] + up[j];
                if (sum % 2 != m[i][j]) {
                    right[i]++, up[j]++, ans++;
                }
                i++, j++;
            }
        }
        
        // Now the diagonal
        for (int i = 0; i < n; ++i) {
            int sum = left[i] + right[i] + down[i] + up[i];
            if (sum % 2 != m[i][i]) {
                ans++;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}