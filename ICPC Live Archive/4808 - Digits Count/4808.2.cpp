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

int count(int x, int digit) {
    int power = 1, ans = 0;
    int left = x, right = 0;
    while (left > 0) {
        int current = left % 10;
        left /= 10;
        ans += left * power;
        if (current == digit) {
            ans += right + 1;
        } else if (current > digit) {
            ans += power;
        }
        power *= 10;
        right = x % power;
    }
    if (digit == 0) {
        ans -= (power - 1) / 9;
    }
    return ans;
}

int main(){
    int a, b;
    while (cin >> a >> b) {
        if (a == 0 and b == 0) break;
        int ans[10];

        for (int d = 0; d <= 9; ++d) {
            ans[d] = count(b, d);
            if (a - 1 > 0) ans[d] -= count(a - 1, d);
        }
        
        for (int i = 0; i <= 9; ++i) {
            if (i > 0) printf(" ");
            printf("%d", ans[i]);
        }
        printf("\n");
        
        
    }
    return 0;
}