// Andrés Mejía

// Accepted

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

const int MAXS = 55;
int grundy[MAXS];

// backtrack to generate all possible movements
void split(int sum, int required, vector<int> &built, vector<int> &options) {
    assert(sum <= required);
    
    if (sum == required) {
        int nim_sum = 0;
        for (int i = 0; i < built.size(); ++i) {
            nim_sum ^= grundy[built[i]];
        }
        options.push_back(nim_sum);
    } else {
        for (int first = built.back() + 1; sum + first <= required; ++first) {
            built.push_back(first);
            split(sum + first, required, built, options);
            built.pop_back();
        }
    }
}

int mex(vector<int> &options) {
    if (options.size() == 0) return 0;
    sort(options.begin(), options.end());
    if (options[0] > 0) return 0;
    for (int i = 1; i < options.size(); ++i) {
        if (options[i] > options[i - 1] + 1) return options[i - 1] + 1;
    }
    return options.back() + 1;
}

int main(){
    grundy[1] = 0;
    for (int i = 2; i <= 50; ++i) {
        vector<int> options;
        vector<int> built;
        
        // try all possible splits of a tower of i stones
        for (int first = 1; first < i; ++first) {
            built.push_back(first);
            split(first, i, built, options);
            built.pop_back();
        }
        
        // and get the mex of all the possibles moves
        grundy[i] = mex(options);
    }
    
    int T; cin >> T;
    while (T--){
        int n; cin >> n;
        int nim_sum = 0;
        for (int i = 0; i < n; ++i) {
            int x; cin >> x;
            nim_sum ^= grundy[x];
        }
        cout << (nim_sum == 0 ? "BOB" : "ALICE") << endl;
    }
    
    return 0;
}