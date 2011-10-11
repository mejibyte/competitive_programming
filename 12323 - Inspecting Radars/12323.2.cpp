// Accepted
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

typedef pair<int, int> point;

const int MAXN = 10000;
const int MAXR = 101;
const int MAXW = 720;

int mat[MAXR][MAXW];
int sum[MAXR][MAXW];

void precompute() {
    for (int i = 0; i < MAXR; ++i) {
        for (int j = 0; j < MAXW; ++j) {
            sum[i][j] = mat[i][j];
            if (i > 0) sum[i][j] += sum[i-1][j];
            if (j > 0) sum[i][j] += sum[i][j-1];
            if (i > 0 and j > 0) sum[i][j] -= sum[i-1][j-1];
        }
    }
}

int rectangle(int r1, int c1,   int r2, int c2) {
    int ans = sum[r2][c2];
    if (r1 > 0) ans -= sum[r1-1][c2];
    if (c1 > 0) ans -= sum[r2][c1-1];
    if (r1 > 0 and c1 > 0) ans += sum[r1-1][c1-1];
    return ans;
}

void solve(int height, int width) {
    int ans = 0;
    for (int i = 0; i + height < MAXR; ++i) {
        for (int j = 0; j + width < MAXW; ++j) {
            int option = rectangle(i, j,     i + height, j + width);
            if (option > ans) ans = option;
        }
    }
    printf("%d\n", ans);
}

int main(){
    int N, R;
    while (scanf("%d %d", &N, &R) == 2) {
        if (N == 0 and R == 0) break;
        memset(mat, 0, sizeof mat);
        
        for (int i = 0; i < N; ++i) {
            int distance, angle;
            scanf("%d %d", &distance, &angle);
            mat[distance][angle]++;
            mat[distance][angle + 360]++;
        }
        precompute();
        
        int E;
        scanf("%d", &E);
        while (E--) {
            int distance, angle;
            scanf("%d %d", &distance, &angle);
            solve(distance - 1, angle);
        }
    }
    return 0;
}