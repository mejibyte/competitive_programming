


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

int minimum_rotation(string s) {
    int n = s.size();
    s = s + s;
    int mini = 0, p = 1, k = 0;
    while (p < n && mini + k + 1 < n) {
        if (s[mini + k] == s[p + k]) {
            k++;
        } else if (s[mini + k] < s[p + k]) {
            p = p + k + 1;
            k = 0;
        } else if (s[mini + k] > s[p + k]){
            mini = max(mini + k + 1, p);
            p = mini + 1;
            k = 0;
        }
    }
    // the actual minimum rotated string is 
    // s.substr(mini, n)
    return mini;
}

int main(){
    string s; cin >> s;
    cout << minimum_rotation(s) << endl;
    return 0;
}