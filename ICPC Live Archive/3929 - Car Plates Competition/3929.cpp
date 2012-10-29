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

bool is_letter(char c) {
    return 'A' <= c and c <= 'Z';
}

long long str_to_int(const string &s) {
    stringstream sin(s);
    long long ans;
    sin >> ans;
    return ans;
}

long long old_scheme(const string &s) {
    long long p = 1, ans = 0;
    for (int i = 2; i >= 0; --i) {
        int value = s[i] - 'A';
        ans += value * p;
        p *= 26;
    }
    ans *= 10000LL;
    ans += str_to_int(s.substr(3));
    return ans;
}

long long new_scheme(const string &s) {
    assert(is_letter(s[3]) and is_letter(s[4]));
    
    const static string bad = "ACMIP";
    long long p = 1, ans = 0;
    for (int i = 4; i >= 0; --i) {
        int value = s[i] - 'A';
        for (int b = 0; b < bad.size(); ++b) {
            if (s[i] == bad[b]) return (1LL << 60);
            if (bad[b] < s[i]) value--;
        }
        ans += value * p;
        p *= (26 - bad.size());
    }
    ans *= 100LL;
    ans += str_to_int(s.substr(5));
    ans += 26LL*26*26*10000; // old scheme
    return ans;
}

long long position(const string &s) {
    if (is_letter(s[3])) return new_scheme(s);
    else return old_scheme(s);
}

bool valid(const string &a, const string &b, long long c) {
    if (a == b) return false;
    if (is_letter(b[3]) != is_letter(b[4])) return false;
    long long aa = position(a);
    long long bb = position(b);
    return aa < bb and bb <= aa + c;
}

int main(){
    string martin, isa;
    long long c;
    while (cin >> martin >> isa >> c) {
        if (c == 0) break;
        if (valid(martin, isa, c)) cout << "Y" << endl;
        else cout << "N" << endl;
    }
    return 0;
}