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

vector<bool> stay;

int main(){
    ios::sync_with_stdio(false);
    int N, K; cin >> N >> K;
    string s; cin >> s;
    assert(s.size() == N);
    stay.assign(N, false);

    K = N - K; // numbers that must remain, instead of numbers that must be removed
    for (int i = 9; i >= 0 and K > 0; --i) {
        for (int j = N - 1; j >= 0 and K > 0; --j) {
            if (s[j] - '0' == i) {
                stay[j] = true;
                K--;
            }
        }
    }
    for (int i = 0; i < N; ++i){
        if (stay[i]) cout << s[i];
    }
    cout << endl;
    
    return 0;
}