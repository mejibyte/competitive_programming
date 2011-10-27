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

vector<int> num;


void print(const vector<int> &v) {
    for (int i = 0; i < v.size(); ++i) {
        if (i > 0) printf(" ");
        printf("%d", v[i]);
    }
    printf("\n");
}

int ten(int e) {
    assert(e >= 0);
    int ans = 1;
    while (e--) ans *= 10;
    return ans;
}

int assemble(int i) {
    assert(i >= -1);
    int ans = 0;
    for (int k = i; k >= 0; --k) {
        ans = 10 * ans + num[k];
    }
    return ans;
}

vector<int> memo[10][2];

vector<int> f(int i, bool m) {
    if (i < 0) {
        return vector<int>(10, 0);
    }
    
    if (memo[i][m].size() > 0) return memo[i][m];
    
    vector<int> ans(10, 0);
    
    int limit = (m ? 9 : num[i] - 1);
    for (int k = 0; k <= limit; ++k) {
        vector<int> s = f(i - 1, true);
        s[k] += ten(i);
        for (int j = 0; j < 10; ++j) ans[j] += s[j];
    }
    
    if (!m) {
        vector<int> s = f(i - 1, false);
        s[num[i]] += assemble(i - 1) + 1;
        for (int j = 0; j < 10; ++j) ans[j] += s[j];
    }
    memo[i][m] = ans;
    return ans;
}

vector<int> f(int x) {
    num.clear();
    while (x > 0) num.push_back(x % 10), x /= 10;
    for (int i = 0; i <= 10; ++i) {
        memo[i][0].clear(), memo[i][1].clear();
    }
    vector<int> ans = f(num.size() - 1, false);
    ans[0] -= (ten(num.size()) - 1) / 9;
    // for (int i = num.size() - 1; i >= 0; --i) {
    //     assert(ans[0] >= ten(i));
    //     ans[0] -= ten(i);
    // }
    return ans;
}

void bruteforce(int a) {
    vector<int> ans(10, 0);
    for (int i = 1; i <= a; ++i){
        int x = i;
        while (x > 0) ans[x % 10]++, x /= 10;
    }
    printf("Bruteforced answer for i=%d: ", a);
    print(ans);
}

int main(){
    // vector<int> a = f(1);
    // print(a);
    // for (int i = 1; i <= 100; ++i) {
    //     printf("i = %d: ", i);
    //     print(f(i));
    // }
    int a, b;
    while (cin >> a >> b) {
        if (a == 0 and b == 0) break;
        vector<int> ans = f(b);
        if (a - 1 > 0) {
            vector<int> remove = f(a - 1);
            for (int i = 0; i < 10; ++i) ans[i] -= remove[i];
        }
        //if (a - 1 > 0) { printf("f(%d) = ", a - 1); print(f(a - 1)); }
        //printf("f(%d) = ", b); print(f(b));
        //bruteforce(b);
        print(ans);
    }
    return 0;
}