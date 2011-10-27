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

int f(unsigned int n) {
    int ans = 0;
    while (n > 1) {
        ans++;
        if (n % 2 == 0) n = n / 2;
        else n = 3 * n + 1;
    }
    return ans + 1;
}

int main(){
    unsigned int a, b;
    while (cin >> a >> b) {
        int ans = -1;        
        for (int i = min(a, b); i <= max(a, b); ++i) {
            ans = max(ans, f(i));
        }
        printf("%d %d %d\n", a, b, ans);        
    }
    return 0;
}