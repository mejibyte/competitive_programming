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

string s;

int main(){
    getline(cin, s);
    int ones = 0, zeros = 0, any = 0;
    int n = s.size();
    for (int i = 0; i < n; ++i) {
        ones += (s[i] == '1');
        zeros += (s[i] == '0');
        any += (s[i] == '?');
    }
    
    if (any == n) {
        printf("00\n01\n10\n11\n");
        return 0;
    }
    
    if (zeros == n) {
        puts("00");
        return 0;
    }
    
    if (ones == n) {
        puts("11");
        return 0;
    }

    
    if (zeros + any > ones) {
        puts("00");
    }
    
    if (s[n - 1] == '1' or s[n - 1] == '?') {
        int z = zeros, o = ones, a = any;
        
        if (a > 0) a--;
        else o--;
        
        if (a > 0) a--;
        else z--;
        
        if (a + o - z >= 0) {
            puts("01");
        }
    }
    
    if (s[n - 1] == '0' or s[n - 1] == '?') {
        int z = zeros, o = ones, a = any;
        
        if (a > 0) a--;
        else z--;
        
        if (a > 0) a--;
        else z--;
        
        if (a + o - z >= 0) {
            puts("10");
        }
    }
    
    
    if (ones + any - zeros > 1) {
        puts("11");
    }
    
    return 0;
}