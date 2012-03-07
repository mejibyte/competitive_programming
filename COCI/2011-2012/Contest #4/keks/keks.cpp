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

vector<int> where[10];

int main(){
    ios::sync_with_stdio(false);
    int N, K; cin >> N >> K;
    string s; cin >> s;
    assert(s.size() == N);
    for (int i = 0; i < N; ++i) {
        where[ s[i] - '0' ].push_back(i);
    }

    K = N - K; // numbers that must remain, instead of numbers that must be removed
    int from = 0, to = N - K;
    while (K > 0) {
        for (int i = 9; i >= 0; --i) {
            vector<int>::iterator p = lower_bound(where[i].begin(), where[i].end(), from);
            if (p != where[i].end() and *p <= to) {
                cout << i;
                from = *p + 1;
                to++;
                K--;
                break;
            }
        }
    }
    cout << endl;
    
    return 0;
}