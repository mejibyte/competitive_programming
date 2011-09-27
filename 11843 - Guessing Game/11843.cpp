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

int main(){
    int C;
    cin >> C;
    while (C--) {
        int n, s;
        cin >> n >> s;
        int ans = 0;
        while (n > 0) {
            if (s > 1) {
                n /= 2;
                s--;
            } else {
                n--;
            }
            ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}