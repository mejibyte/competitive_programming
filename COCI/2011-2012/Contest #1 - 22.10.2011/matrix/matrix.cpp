// Andrés Mejía
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

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

const int MAXN = 405;
int mat[MAXN][MAXN];

vector<int> A[2 * MAXN], B[2 * MAXN];

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &mat[i][j]);
        }
    }
    
    for (int k = 0; k < n; ++k) {
        int i = n - k - 1, j = 0;
        A[k].push_back(0);
        while (i < n and j < n) {
            A[k].push_back(mat[i][j] + A[k].back());
            i++; j++;
        }
    }
    
    for (int k = 1; k < n; ++k) {
        int i = 0, j = k;
        A[n - 1 + k].push_back(0);
        while (i < n and j < n) {
            A[n - 1 + k].push_back(mat[i][j] + A[n - 1 + k].back());
            i++; j++;
        }
    }
    
    for (int k = 0; k < n; ++k) {
        int i = 0, j = k;
        B[k].push_back(0);
        while (i < n and j >= 0) {
            B[k].push_back(mat[i][j] + B[k].back());
            i++; j--;
        }
    }

    for (int k = 1; k < n; ++k) {
        int i = k, j = n - 1;
        B[n - 1 + k].push_back(0);
        while (i < n and j >= 0) {
            B[n - 1 + k].push_back(mat[i][j] + B[n - 1 + k].back());
            i++; j--;
        }
    }

    // For(k, 0, 2 * n - 1) {
    //     printf("A[k=%d]: ", k);
    //     For(i, 0, A[k].size()) printf("%d ", A[k][i]);
    //     puts("");
    // }
    // For(k, 0, 2 * n - 1) {
    //     printf("B[k=%d]: ", k);
    //     For(i, 0, B[k].size()) printf("%d ", B[k][i]);
    //     puts("");
    // }
    
    
    
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int delta = 0; i + delta < n and j + delta < n; ++delta) {
                int ka = n - 1 - i + j;
                int kb = i + j + delta;
                
                int sumA = A[ka].at( min(i, j) + delta + 1 ) - A[ka].at( min(i, j) );
                int sumB = B[kb].at( min(i, n - 1 - j - delta) + delta + 1 ) - B[kb].at( min(i, n - 1 - j - delta) );

                if (sumA - sumB > ans) {
                    //printf("new best sum from [%d, %d] and delta = %d, (sumA = %d, sumB = %d, i + delta =%d, j + delta = %d)\n", i, j, delta, sumA, sumB, i + delta, j + delta);
                    ans = sumA - sumB;
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}