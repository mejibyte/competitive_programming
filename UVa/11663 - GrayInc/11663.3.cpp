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

#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl

bool zeros[1005];

void prevify(string &s, int i);

void nextify(string &s, int i) {
    int n = s.size() - i;
    if (n == 0) return;
    if (n == 1) s[i] = s[i] == '0' ? '1' : '0';
    else {
        assert(n >= 2);
        if (s[i] == '1' and zeros[i+1]) s[i] = '0'; // 100000000
        else if (s[i] == '0' and s[i+1] == '1' and zeros[i+2]) s[i] = '1'; // 010000000
        else if (s[i] == '0') nextify(s, i + 1);
        else if (s[i] == '1') prevify(s, i + 1);
        else assert(false);
    }
}

void prevify(string &s, int i) {
    int n = s.size() - i;
    if (n == 0) return;
    if (n == 1) s[i] = s[i] == '0' ? '1' : '0';
    else {
        assert(n >= 2);
        if (zeros[i]) s[i] = '1'; // 0000000000
        else if (s[i] == '1' and s[i+1] == '1' and zeros[i+2]) s[i] = '0'; // 11000000
        else if (s[i] == '0') prevify(s, i + 1);
        else if (s[i] == '1') nextify(s, i + 1);
        else assert(false);
    }
}

int main(){
    int m;
    string s;
    while (cin >> m >> s) {
        if (m == 0 and s == "0") break;
        int n = s.size();
        while (m--) {
            zeros[n] = true;
            for (int i = n - 1; i >= 0; --i) {
                zeros[i] = zeros[i + 1] and s[i] == '0';
            }
            nextify(s, 0);
        }
        cout << s << endl;
    }
    
    return 0;
}