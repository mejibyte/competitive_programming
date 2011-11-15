/*
  LANG: C++
  PROB: crypt1
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

set<int> valid;

bool check(int num) {
    assert(valid.count(0) == 0);
    assert(num > 0);
    while (num > 0) {
        if (valid.count(num % 10) == 0) return false;
        num /= 10;
    }
    return true;
}

int main(){
    freopen("crypt1.in", "r", stdin);
    freopen("crypt1.out", "w", stdout);
    int n;
    while (scanf("%d", &n) == 1) {
        valid.clear();
        for (int i = 0; i < n; ++i) {
            int x; scanf("%d", &x);
            valid.insert(x);
            assert(x > 0);
        }
        
        int ans = 0;
        for (int first = 111; first <= 999; ++first) {
            for (int second = 11; second <= 99; ++second) {
                int p1 = first * (second % 10);
                int p2 = first * (second / 10);
                int result = first * second;
                
                if (!check(first) or !check(second) or !check(p1) or !check(p2) or !check(result)) continue;
                if (p1 < 111 or p1 > 999) continue;
                if (p2 < 111 or p2 > 999) continue;
                if (result < 1111 or result > 9999) continue;
                
                //printf("first = %d, second = %d, first * second %% 10 = %d, first * second / 10 = %d, first * second = %d\n", first, second, first * (second % 10), first * (second / 10), first * second);
                ans++;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}