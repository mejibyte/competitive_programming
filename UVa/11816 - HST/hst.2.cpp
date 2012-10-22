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

const long double EPS = 1e-9;
int cmp(long double x, long double y = 0, long double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

map<string, long double> tax1;
map<string, long double> tax2;
map<string, long double> tax3;

long double round_cents(long double d) {
    return floorl(d * 100 + 0.5 + 1e-10) / 100.0;
}

void solve() {
    int C, P;
    cin >> C >> P;
    tax1.clear(); tax2.clear(); tax3.clear();
    
    for (int i = 0; i < C; ++i) {
        string category; cin >> category;
        long double t1, t2, t3;
        scanf("%Lf%% %Lf%% %Lf%%", &t1, &t2, &t3);
        
        tax1[category] = t1 / 100.0;
        tax2[category] = t2 / 100.0;
        tax3[category] = t3 / 100.0;
    }
    
    long double before = 0, now = 0;
    
    for (int i = 0; i < P; ++i) {
        string c; cin >> c;
        long double t1 = tax1[c], t2 = tax2[c], t3 = tax3[c];
        
        long double price; scanf(" $%Lf", &price);

        before += round_cents(price * t1);
        before += round_cents(price * t2);
        now += round_cents(price * t3);
    }
    long double ans = now - before;
    printf("%.2Lf\n", ans);
}

int main(){
    int runs; cin >> runs;
    while (runs--) solve();
    return 0;
}