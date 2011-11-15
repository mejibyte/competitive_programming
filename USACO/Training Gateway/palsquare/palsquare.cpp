/*
  LANG: C++
  PROB: palsquare
*/
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

string toBase(int x, int b) {
    string ans = "";
    do {
        int digit = x % b;
        if (digit < 10) ans = char('0' + digit) + ans;
        else ans = char('A' + digit - 10) + ans;
        x /= b;
    } while (x > 0);
    return ans;
}

int main(){
    freopen("palsquare.in", "r", stdin);
    freopen("palsquare.out", "w", stdout);
    
    int B;
    cin >> B;
    
    for (int i = 1; i <= 300; ++i) {
        string s = toBase(i * i, B);
        string t = s; reverse(t.begin(), t.end());
        if (s == t) {
            cout << toBase(i, B) << " " << s << endl;
        }
    }
    
    return 0;
}