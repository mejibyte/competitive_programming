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


int main(){
    string first;
    string second;
    cin >> first;
    cin >> second;
    For(i, 0, second.size()) first = "#" + first + "#";
    int ans = (1 << 30);
    for (int i = 0; i < (first.length() - second.length() +1); ++i) {
        int count = 0;
        for (int j = 0; j < second.length(); ++j) {
            if (first.at(i + j) == second.at(j)) {
                count++;
            }
        }
        ans = min(ans, (int)second.length() - count);
    }
    cout << ans << endl;
    return 0;
}