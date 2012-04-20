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

struct Triplet {
    int s[3];
    Triplet(int a, int b, int c) {
        s[0] = a, s[1] = b, s[2] = c;
    }
    Triplet() {}
    
    void rotateRight() {
        int t = s[2];
        s[2] = s[1]; s[1] = s[0]; s[0] = t;
    }
    
    void rotateLeft() {
        rotateRight();
        rotateRight();
    }
    
    void print() {
        printf("(%d, %d, %d)\n", s[0], s[1], s[2]);
    }
};

vector<int> primes;

const int MAXP = 200005;
bool composite[MAXP];

bool isPrime(int n) {
    return binary_search(primes.begin(), primes.end(), n);
}

#include <bitset>

Triplet memo[MAXP];
bitset<MAXP> been;

Triplet f(int n) {
    assert(n > 1);
    
    if (been[n]) return memo[n];
    
    if (isPrime(n)) {
        been[n] = true;
        return memo[n] = Triplet(1, INT_MAX, INT_MAX);
    }
    
    int bestScore = INT_MAX; Triplet ans;
    
    //aumentar
    Triplet t = f(n + 1);
    int score = min(n + 1, t.s[2]);
    if (score < bestScore) {
        ans = t; ans.rotateRight();
        ans.s[0] = score;
        bestScore = score;
    }
    
    // dividir por un primo
    for (int i = 0; i < primes.size() and primes[i] < n; ++i) {
        int p = primes[i];
        if (n % p != 0) continue;
        Triplet t = f(n / p);
        int score = min(n / p, t.s[2]);
        if (score <= bestScore) {
            ans = t; ans.rotateRight();
            ans.s[0] = score;
            bestScore = score;
        }
    }
    been[n] = true;
    return memo[n] = ans;
}

int main(){
    for (int i = 2; i < MAXP; ++i) {
        if (!composite[i]) primes.push_back(i);
        for (long long j = 1LL * i * i; j < MAXP; j += i) composite[j] = true;
    }
    been.reset();
    assert(primes.back() > 10000);
    
    int rounds; cin >> rounds;
    
    Triplet ans(0, 0, 0);
    while (rounds--) {
        char c;
        int n; cin >> c >> n;
        int who;
        if (c == 'O') who = 0;
        if (c == 'E') who = 1;
        if (c == 'I') who = 2;
        
        Triplet t;
        if (n == 1) {
            t = Triplet(1, 1, 1);
        } else {
            t = f(n);
        }
        while (who--) t.rotateRight();
       
        for (int i = 0; i < 3; ++i) {
            if (t.s[i] == INT_MAX) t.s[i] = n;
            ans.s[i] += t.s[i];
        }
    }
    cout << ans.s[0] << " " << ans.s[1] << " " << ans.s[2] << endl;

    return 0;
}
