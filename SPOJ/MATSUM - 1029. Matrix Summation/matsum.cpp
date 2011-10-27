using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>

#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl

const int MAXN = 1025;
int tree[MAXN][MAXN];
int mat[MAXN][MAXN];
int N;

void add(int r, int c, int what) {
    for (r++; r <= N; r += r & -r) {
        for (int d = c + 1; d <= N; d += d & -d) {
            tree[r][d] += what;
        }
    }
}

int get(int r, int c) {
    int ans = 0;
    for (r++; r > 0; r -= r & -r) {
        for (int d = c + 1; d > 0; d -= d & -d) {
            ans += tree[r][d];
        }
    }
    return ans;
}

int sum(int r1, int c1, int r2, int c2) {
    return get(r2, c2) - get(r1 - 1, c2) - get(r2, c1 - 1) + get(r1 - 1, c1 - 1);
}

void set(int r, int c, int what) {
    int prev = mat[r+1][c+1];
    mat[r+1][c+1] = what;
    add(r, c, what - prev);
}

int main(){
    int t; scanf("%d", &t);
    while (t--) {
        scanf("%d", &N);
        for (int i = 0; i <= N; ++i) {
            for (int j = 0; j <= N; ++j) {
                tree[i][j] = mat[i][j] = 0;
            }
        }
        while (true) {
            char buf[4];
            scanf("%s", buf);
            if (!strcmp(buf, "SET")) {
                int r, c, x; scanf("%d %d %d", &r, &c, &x);
                //printf("Set (%d, %d) to %d\n", r, c, x);
                ::set(r, c, x);
            } else if (!strcmp(buf, "SUM")) {
                int r1, c1, r2, c2; scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
                //printf("Sum (%d, %d) to (%d, %d)\n", r1, c1, r2, c2);
                int ans = sum(r1, c1, r2, c2);
                printf("%d\n", ans);
            } else {
                //printf("Take a break.\n");
                break;
            }
        }
        printf("\n");
    }
    return 0;
}