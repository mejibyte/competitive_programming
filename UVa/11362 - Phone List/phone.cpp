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

const int MAXS = 10005 * 10;

int g[MAXS][10];
bitset<MAXS> finish;

int main(){
    int runs; cin >> runs;
    while (runs--) {
        int m; cin >> m;
        memset(g[0], -1, sizeof g[0]);
        int states = 1;
        finish.reset();
        bool valid = true;
        while (m--) {
            string s; cin >> s;
            int cur = 0; // root
            for (int i = 0; i < s.size(); ++i) {
                int next = (s[i] - '0');
                if (g[cur][next] == -1) {
                    g[cur][next] = states;
                    memset(g[states], -1, sizeof g[states]);
                    states++;
                }
                cur = g[cur][next];
                if (finish[cur]) valid = false;
            }
            if (cur != states - 1) valid = false;
            finish[cur] = true;
        }
        cout << (valid ? "YES" : "NO") << endl;
    }
    return 0;
}