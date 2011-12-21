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

map< char, int > ans;

struct score {
    char party;
    int num, denum;
    
    bool operator < (const score &t)  const {
        // num / denum < t.num / t.denum
        return 1LL * num * t.denum < 1LL * t.num * denum;
    }
};

int main(){
    int votes; cin >> votes;
    int parties; cin >> parties;
    
    vector< score > scores;
    set< char > show;
    
    for (int i = 0; i < parties; ++i) {
        char name; int v; cin >> name >> v;
        // v > votes * 5 / 100
        if (100 * v >= votes * 5) {
            show.insert(name);
            for (int d = 1; d <= 14; ++d) {
                score s;
                s.party = name;
                s.num = v;
                s.denum = d;
                scores.push_back( s );
            }
        }
    }
    sort(scores.begin(), scores.end());
    reverse(scores.begin(), scores.end());
    
    for (int i = 0; i < 14; ++i) {
        ans[ scores[i].party ]++;
    }
    foreach(c, show) {
        printf("%c %d\n", *c, ans[*c]);
    }
    
    return 0;
}