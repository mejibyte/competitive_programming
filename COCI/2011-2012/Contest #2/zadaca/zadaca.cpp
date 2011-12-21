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

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

const int MAXN = 1005;
int A[MAXN];
int B[MAXN];
int N, M;

map<int, int> times[2];

void decompose(int x, int side) {
    while (x % 2 == 0) {
        times[side][2]++;
        x /= 2;
    }
    
    for (int p = 3; 1LL * p * p <= x; p += 2) {
        while (x % p == 0) {
            times[side][p]++;
            x /= p;
        }
    }
    if (x > 1) times[side][x]++;
}

int main(){
    cin >> N;
    for(int i = 0; i < N; ++i) cin >> A[i];
    cin >> M;
    for(int i = 0; i < M; ++i) cin >> B[i];
    
    times[0][1] = 1;
    times[1][1] = 1;
    
    for(int i = 0; i < N; ++i) decompose(A[i], 0);
    for(int i = 0; i < M; ++i) decompose(B[i], 1);
    
    bool pad = false;
    const int mod = 1000000000;
    
    long long ans = 1;
    foreach(p, times[0]) {
        int prime = p->first;
        int exponent = min(p->second, times[1][prime]);
        
        for (int k = 0; k < exponent; ++k) {
            ans *= prime;
            if (ans >= mod) {
                ans %= mod;
                pad = true;
            }
        }
    }
    
    pad ? printf("%.9lld\n", ans) : printf("%lld\n", ans);
    return 0;
}