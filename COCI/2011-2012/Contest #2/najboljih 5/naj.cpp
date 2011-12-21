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

int a[8];
int b[8];

int compare(int i, int j) {
    return a[i] < a[j];
}

int main(){
    int sum = 0;
    for(int i = 0; i < 8; ++i) {
        cin >> a[i];
        b[i] = i;
        sum += a[i];
    }
    sort(b, b + 8, compare);
    printf("%d\n", sum - a[b[0]] - a[b[1]] - a[b[2]]);
    set<int> ans;
    for (int i = 3; i < 8; ++i) ans.insert(b[i] + 1);
    for(int i = 3; i < 8; ++i) {
        if (i > 3) printf(" ");
        printf("%d", *ans.begin());
        ans.erase(ans.begin());
    }
    printf("\n");
    return 0;
}