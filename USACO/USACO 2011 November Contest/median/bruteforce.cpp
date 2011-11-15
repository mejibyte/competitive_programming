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

int a[100001];

int main(){
    int n, thres;
    scanf("%d %d", &n, &thres);
    
    a[0] = 0;
    for (int i = 0; i < n; ++i){
        int cow; scanf("%d", &cow);
        a[i] = cow;
    }
    
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        vector<int> b;
        for (int j = i; j < n; ++j) {
            b.push_back( a[j] );
            sort(b.begin(), b.end());
            int median = b[ b.size() / 2 ];
            if (median >= thres) ans++;
        }
    }
    cout << ans << endl;
    return 0;
}