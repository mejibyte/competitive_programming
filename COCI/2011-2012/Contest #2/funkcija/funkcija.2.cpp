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


int toInt(string s) {
    int ans;
    sscanf(s.c_str(), "%d", &ans);
    return ans;
}

const int MAXN = 26;
bool letter[MAXN][2];
int low[MAXN], high[MAXN];
int N;
int cur[MAXN];

const int mod = 1000000007;

long long sum(int i) {
    if (i == N) return 1;
    
    int a;
    if (letter[i][0]) a = cur[low[i]];
    else a = low[i];
    
    int b;
    if (letter[i][1]) b = cur[high[i]];
    else b = high[i];

    long long ans = 0;
    for (int k = a; k <= b; ++k) {
        cur[i] = k;
        ans += sum(i + 1);
        if (ans >= mod) ans -= mod;
    }
    return ans;
}

// I know this will time out, but I don't know how to solve it fast enough :(

int main(){
    int n; cin >> n;
    N = n;
    for (int i = 0; i < n; ++i) {
        string s, t;
        cin >> s >> t;
        
        if (isalpha(s[0])) {
            letter[i][0] = true;
            low[i] = s[0] - 'a';
        } else {
            low[i] = toInt(s);
        }

        if (isalpha(t[0])) {
            letter[i][1] = true;
            high[i] = t[0] - 'a';
        } else {
            high[i] = toInt(t);
        }        
    }

    long long ans = sum(0);
    printf("%lld\n", ans);
    return 0;
}