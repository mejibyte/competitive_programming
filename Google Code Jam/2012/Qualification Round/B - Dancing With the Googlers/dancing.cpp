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
#include <bitset>
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

struct Triplet {
    int a, b, c;
    
    Triplet(){}
    Triplet(int a, int b, int c) : a(a), b(b), c(c) {}
    
    bool good() {
        return abs(a - b) <= 2 and abs(a - c) <= 2 and abs(b - c) <= 2;
    }

    bool surprising() {
        return abs(a - b) == 2 or abs(a - c) == 2 or abs(b - c) == 2;
    }
    
    int sum() {
        return a + b + c;
    }
    
    int best_result() {
        return max(a, max(b, c));
    }
};


vector<Triplet> options[31];

const int MAXN = 105;
int dp[MAXN][MAXN];
int sum[MAXN];

void solve() {
    int N, S, P;
    cin >> N >> S >> P;
    for (int i = 0; i < N; ++i) cin >> sum[i];
    
    int total = 0;
    for (int a = 0; a <= 10; ++a){
        for (int b = 0; b <= 10; ++b){
            for (int c = 0; c <= 10; ++c){
                Triplet t(a, b, c);
                if (t.good()) {
                    total++;
                    options[t.sum()].push_back(t);
                }
            }
        }
    }
    
    assert(total < 200);
    for (int s = 0; s < MAXN; ++s) dp[N][s] = INT_MIN;
    dp[N][0] = 0;
    
    for (int i = N - 1; i >= 0; --i) {
        for (int s = 0; s <= S; ++s) {
            dp[i][s] = INT_MIN;
            assert(options[sum[i]].size() > 0);
            
            for (int k = 0; k < options[sum[i]].size(); ++k) {
                Triplet take = options[sum[i]][k];
                assert(take.good() and take.sum() == sum[i]);
                int score = (take.best_result() >= P);
                
                if (!take.surprising()) dp[i][s] = max(dp[i][s], dp[i + 1][s] + score);
                else if (s > 0) dp[i][s] = max(dp[i][s], dp[i + 1][s - 1] + score);
            }
        }
    }
    
    cout << dp[0][S] << endl;
    assert(dp[0][S] <= N);
}

int main(){
    int runs; cin >> runs;
    for (int i = 1; i <= runs; ++i) printf("Case #%d: ", i), solve();
    return 0;
}   