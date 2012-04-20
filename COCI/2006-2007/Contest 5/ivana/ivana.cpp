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

const int MAXN = 105;

int numbers[MAXN], score[MAXN][MAXN], n;
int memo[MAXN][MAXN];

int f(int i, int j) {
    if (i == j) return score[i][j];
    if (memo[i][j] != -1) return memo[i][j];
    
    int ans = score[i][j] - min(f(i + 1, j), f(i, j - 1));
    return memo[i][j] = ans;
}


int main(){
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }
    
    int ans = 0;
    for (int k = 0; k < n; ++k) {
        
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                score[i][j] = (numbers[j] % 2);
                if (j - 1 >= 0) score[i][j] += score[i][j - 1];
            }
        }
        
        
        memset(memo, -1, sizeof memo);
        int get = score[0][n - 1] - f(1, n - 1);
        if (get > score[0][n - 1] - get) ans++;
        rotate(numbers, numbers + 1, numbers + n);
    }
    printf("%d\n", ans);
    return 0;
}