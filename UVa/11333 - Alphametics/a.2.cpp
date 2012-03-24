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

const int MAXN = 19;
long long power[MAXN];
char canBeZero[256];
long long coef[256];
set<char> digits;

bool bruteforce() {
    
    char assign[11];
    
    int k = 0;
    for (; k < 10 - digits.size(); ++k) assign[k] = '*';
    foreach(c, digits) assign[k++] = *c;
    assign[10] = 0;
    do {
        if (!canBeZero[assign[0]]) continue;
        
        int primes[3] = {
            999999937,
            1000000007,
            1000000009
        };
        
        bool valid = true;
        for (int p = 0; p < 2; ++p) {
            int mod = primes[p];
        
            int sum = 0;
            for (int i = 0; i < 10; ++i) {
                char digit = assign[i];
                int value = i;
            
                sum += (1LL * (coef[digit] % mod) * value) % mod;
                if (sum > mod or sum < -mod) sum %= mod;
            }
            
            if (sum != 0) valid = false;
        }
        
        if (valid) {
            puts(assign);
            return true;
        }

    } while (next_permutation(assign, assign + 10));
    
    return false;
}

int main(){
    power[0] = 1;
    for (int i = 1; i < MAXN; ++i) power[i] = power[i - 1] * 10LL;
    
    string s;
    while (getline(cin, s)) {
        
        for (char c = 'A'; c <= 'Z'; ++c) {
            canBeZero[c] = true;
            coef[c] = 0;
        }
        
        digits.clear();
        
        stringstream sin(s);

        int sign = +1;
        bool invert = false;
        
        while (sin >> s){
            assert(s.size() <= 17);
            
            if (s == "+") {
                sign = +1;
                if (invert) sign = -1;
            }
            else if (s == "-") {
                sign = -1;
                if (invert) sign = +1;
            }
            else if (s == "=") {
                invert = true;
                sign = -1;
            } else {
                if (s.size() >= 2) canBeZero[s[0]] = false;
                reverse(s.begin(), s.end());
                for (int i = 0; i < s.size(); ++i) {
                    coef[s[i]] += power[i] * sign;
                    digits.insert(s[i]);
                }
            }
        }
        
        if (!bruteforce()) {
            for (int k = 0; k < 10; ++k) printf("*");
            puts("");
        }

    }
    return 0;
}