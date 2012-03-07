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

const int MAXN = 100005;

int said[MAXN];
int was[MAXN], wasnt[MAXN];

int n, m;
int sumWasnt;

bool canTrue[MAXN], canFalse[MAXN];

bool canBe(int i) {
    return was[i] + sumWasnt - wasnt[i] == m;
}

int main(){
    sumWasnt = 0;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> said[i];
        if (said[i] > 0) was[said[i]]++;
        else {
            wasnt[-said[i]]++;
            sumWasnt++;
        }
    }
    
    set<int> maybeGuilty;
    for (int i = 1; i <= n; ++i) {
        if (canBe(i)) {
            maybeGuilty.insert(i);
        }
    }
    assert(maybeGuilty.size() > 0);
    
    memset(canTrue, true, sizeof canTrue);
    memset(canFalse, true, sizeof canFalse);
    
    for (int i = 1; i <= n; ++i) {
        int finger = said[i];
        if (finger > 0) {
            if (!maybeGuilty.count(finger)) canTrue[i] = false;
        } else {
            finger = -finger;
            if (maybeGuilty.count(finger)) canFalse[i] = false;
        }
    }
    
    
    for (int i = 1; i <= n; ++i) {
        if (!canTrue[i]) {
            if (maybeGuilty.size() > 1) puts("Lie");
            else puts("Not defined");
        } else {
            if (maybeGuilty.size() > 1) puts("Not defined");
            else puts("Truth");
        }
    }

    return 0;
}