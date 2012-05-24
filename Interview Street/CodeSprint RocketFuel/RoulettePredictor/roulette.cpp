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

typedef unsigned long long Int;

long long limit = 1000000000000005LL; //10^15

int main(){
    vector<Int> list;
    priority_queue<Int, vector<Int>, greater<Int> > q;
    q.push(1);
    while (list.size() == 0 or list.back() < limit) {
        Int next = q.top(); q.pop();
        list.push_back(next);
        if (next * 3LL < limit) {
            q.push(next * 3LL);
        }
        if (next % 3 != 0 and next * 2LL < limit) {
            q.push(next * 2LL);
        }
    }

    int k, mod;
    cin >> k >> mod;
    if (k > list.size()) return 0;
    
    int sum = 0;
    for (int i = 0; i < k; ++i) {
        sum += list[i] % mod;
        sum %= mod;
    }
    cout << sum;
    return 0;
}