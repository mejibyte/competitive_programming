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

vector<int> text, pattern, prev, border;

bool canAdd(int pos, int len) {
    if (len == 0) return true;
    if (prev[len] == -1) return prev[pos] < pos - len;
    else return prev[pos] != -1 and len - prev[len] == pos - prev[pos];
}

void precomputeBorder(int n) {
    border.resize(n);
    border[0] = 0;
    for (int i = 1; i < n; ++i) {
        border[i] = border[i - 1];
        while (!canAdd(i, border[i])) border[i] = border[border[i] - 1];
        border[i]++;
    }
}

void solve() {
    int n = pattern.size();
    
    vector<int> lastSeen(n, -1);
    prev.resize(n);
    
    for (int i = 0; i < n; ++i) {
        prev[i] = lastSeen[pattern[i]];
        lastSeen[pattern[i]] = i;
    }
    precomputeBorder(n);
    
    int m = text.size();
    lastSeen.assign(m, -1);
    prev.resize(n + m);
    for (int i = 0; i < m; ++i) {
        prev[n + i] = lastSeen[text[i]];
        lastSeen[text[i]] = n + i;
    }
    
    int seen = 0;
    for (int i = 0; i < m; ++i) {
        while (!canAdd(n + i, seen)) seen = border[seen - 1];
        seen++;
        if (seen == n) {
            printf("%d\n", i - n + 2);
            return;
        }
    }
    
}

int main(){
    map<string, int> id;
    int nextId = 0;

    for (string s; cin >> s and s != "$"; ) {
        int k = id.count(s) ? id[s] : id[s] = nextId++;
        text.push_back(k);
    }

    id.clear();
    nextId = 0;
    for (string s; cin >> s and s != "$"; ) {
        int k = id.count(s) ? id[s] : id[s] = nextId++;
        pattern.push_back(k);
    }

    solve();
    return 0;
}