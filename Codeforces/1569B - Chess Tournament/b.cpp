// Andrés Mejía
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
using namespace std;

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cerr << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

const int MAXN = 55;

char games[MAXN][MAXN];

void solve(const string &s) {
    int n = s.size();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            games[i][j] = '=';
        }
        games[i][i] = 'X';
    }

    vector<int> no_losses;
    vector<int> one_win;

    for (int i = 0; i < n; ++i) {
        if (s[i] == '1') no_losses.push_back(i);
        else one_win.push_back(i);
    }

    if (1 <= one_win.size() and one_win.size() <= 2) {
        cout << "NO" << endl;
        return;
    }

    for (int i : no_losses) {
        for (int j = i + 1; j < n; ++j) {
            games[i][j] = games[j][i] = '=';
        }
    }

    for (int k = 0; k < one_win.size(); ++k) {
        int a = one_win[k];
        int b = one_win[(k+1)%one_win.size()];
        games[a][b] = '+';
        games[b][a] = '-';
    }

    cout << "YES" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << games[i][j];
        }
        cout << endl;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        solve(s);
    }
    return 0;
}
