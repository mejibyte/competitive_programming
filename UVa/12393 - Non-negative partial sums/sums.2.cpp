// Andrés Mejía

// Bruteforce solution to find the bug.

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

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

const int MAXN = 1000005;

int A[MAXN], S[MAXN], L[MAXN], R[MAXN];

int bruteforce(int n) {
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        bool is = true;
        int sum = 0;
        for (int k = 0; k < n; ++k) {
            sum += A[k];
            if (sum < 0) is = false;
        }
        ans += is;
        // if (is) {
        //     printf("This rotation is valid: "); for (int k = 0; k < n; ++k) printf("%d ", A[k]); puts("");
        //     printf("Partial sums: "); for (int k = 0, s = 0; k < n; ++k) { s += A[k]; printf("%d ", s); } puts("");
        // }
        rotate(A, A + 1, A + n);
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    int n;
    while (cin >> n) {
        if (n == 0) break;
        for (int i = 0; i < n; ++i) {
            cin >> A[i];
            S[i] = A[i];
            if (i > 0) {
                S[i] += S[i - 1];
            }
        }
        for (int i = 0; i < n; ++i) {
            L[i] = S[i];
            if (i - 1 >= 0 and L[i - 1] < L[i]) L[i] = L[i - 1];
        }
        for (int i = n - 1; i >= 0; --i) {
            R[i] = S[i];
            if (i + 1 < n and R[i + 1] < R[i]) R[i] = R[i + 1];
        }
        
        // printf("S: "); for (int i = 0; i < n; ++i) printf("%d ", S[i]); puts("");        
        // printf("L: "); for (int i = 0; i < n; ++i) printf("%d ", L[i]); puts("");
        // printf("R: "); for (int i = 0; i < n; ++i) printf("%d ", R[i]); puts("");
                
        int ans = R[0] >= 0;
        for (int k = 1; k < n; ++k) {
            ans += (R[k] >= S[k - 1] and L[k - 1] >= S[k - 1] - S[n - 1]);
        }
        int b = bruteforce(n);
        if (ans < b and ans == 0) {
            for (int i = 0; i < n; ++i) {
                printf("%d ", A[i]); 
            }
            puts("");
            printf("ans is %d, bruteforce is %d\n", ans, b);
            assert(false);
        }
        cout << ans << endl;
    }
    return 0;
}