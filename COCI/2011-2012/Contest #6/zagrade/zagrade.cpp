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

const int MAXN = 205;

set<string> ans;
string s, built;
bool erased[MAXN];
int closing_match[MAXN];

void recurse(int i) {
    if (i == s.size()) {
        ans.insert(built);
        return;
    }
    if (erased[i]) {
        recurse(i + 1);
        return;
    }
    
    built += s[i];
    recurse(i + 1);
    built.resize(built.size() - 1);
    
    if (s[i] == '(') {
        erased[closing_match[i]] = true;
        recurse(i + 1);
        erased[closing_match[i]] = false;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin >> s;
    vector<int> opening;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '(') opening.push_back(i);
        else if (s[i] == ')') {
            closing_match[opening.back()] = i;
            opening.pop_back();
        }
    }
    recurse(0);
    ans.erase(s);
    foreach(k, ans) cout << *k << endl;
    return 0;
}