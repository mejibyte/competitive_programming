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

string A[3], B[3], C[3];

int value(const string &s) {
    return s == "up" ? +1 : s == "down" ? -1 : 0;
}

bool works(char letter, int v) {
    for (int i = 0; i < 3; ++i) {
        int sa = 0, sb = 0;
        for (int k = 0; k < A[i].size(); ++k) sa += v * (A[i][k] == letter);
        for (int k = 0; k < B[i].size(); ++k) sb += v * (B[i][k] == letter);
        if (sa - sb != value(C[i])) return false;
    }
    return true;
}

int main(){
    int cases; cin >> cases;
    while (cases--) {
        for (int i = 0; i < 3; ++i) cin >> A[i] >> B[i] >> C[i];
        for (char c = 'A'; c <= 'Z'; ++c) {
            if (works(c, +1)) {
                printf("%c is the counterfeit coin and it is heavy.\n", c);
                break;
            }
            if (works(c, -1)) {
                printf("%c is the counterfeit coin and it is light.\n", c);
                break;
            }
        }
    }
    return 0;
}