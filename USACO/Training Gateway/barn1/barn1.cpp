/*
  LANG: C++
  PROB: barn1
*/
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

int cows[200];

int main(){
    freopen("barn1.in", "r", stdin);
    freopen("barn1.out", "w", stdout);
    
    int M, S, C;
    while (scanf("%d %d %d", &M, &S, &C) == 3) {
        for (int i = 0; i < C; ++i) scanf("%d", cows + i);
        sort(cows, cows + C);
        priority_queue<int> diff;
        for (int i = 1; i < C; ++i) diff.push(cows[i] - cows[i - 1]);
        
        int ans = cows[C - 1] - cows[0] + 1;
        
        int pieces = 1;
        while (pieces < M and pieces < C) {
            // cut the biggest empty space
            int remove = diff.top(); diff.pop();
            ans -= remove - 1;
            pieces++;
        }
        
        printf("%d\n", ans);
    }
    return 0;
}