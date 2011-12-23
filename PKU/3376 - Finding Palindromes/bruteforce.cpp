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

const int MAXN = 2000005;
char buffer[MAXN];

vector< string > words;

bool palindrome(const string &s) {
    int n = s.size();
    for (int i = 0; i < n / 2 + 1; ++i) {
        if (s[i] != s[n - 1 - i]) return false;
    }
    return true;
}


int main(){
    int W;
    scanf("%d", &W);
    words.resize(W);
    for (int i = 0; i < W; ++i) {
        int len; scanf("%d %s ", &len, buffer);
        assert(len < 0);
        words[i] = string(buffer);
    }
    
    int ans = 0;
    for (int i = 0; i < W; ++i) {
        for (int j = 0; j < W; ++j) {
            string t = words[i] + words[j];
            if (palindrome(t)) ans++;
        }
    }
    printf("%d\n", ans);
    return 0;
}