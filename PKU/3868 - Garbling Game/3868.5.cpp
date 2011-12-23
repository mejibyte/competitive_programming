// Andrés Mejía
// Gives correct answers, but times out on PKU.
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

const int MAXN = 305;

int R, C;
char garbling[MAXN][MAXN];
char buf[MAXN];
          
int board[MAXN][MAXN];

int cur[MAXN * MAXN];
int next[MAXN * MAXN];
int add[MAXN * MAXN];

int newCur[MAXN * MAXN];
int newAdd[MAXN * MAXN];

int step[MAXN * MAXN];
int newStep[MAXN * MAXN];

int ans[MAXN * MAXN];

const int mod = 100000;

struct BigInt {
    int D[MAXN];
    int len;
    
    BigInt(char * s) {
        len = strlen(s);
        for (int i = 0; i < len; ++i) {
            D[i] = s[len - 1 - i] - '0';
        }
    }
    
    int mod(int x) const {
        int res = 0;
        for (int i = len-1; i >= 0; --i)
            res = (res * 10 + D[i]) % x;    
        return res;
    }

    void div(int x) {
        int left = 0, will;
        for (int i = len-1; i >= 0; --i) {
            will = (left * 10 + D[i]) % x;    
            D[i] = (left * 10 + D[i]) / x;    
            left = will;
        }
        while (len > 1 && D[len-1] == 0) len--;
    }
    
    bool odd() const {
        return (D[0] & 1);
    }
    
    bool operator > (int what) const {
        for (int i = 0; i < len; ++i) {
            int digit = what % 10;
            if (D[i] != digit) return D[i] > digit;
            what /= 10;
        }
        return false;
    }
    
    void print() const {
        for (int i = len - 1; i >= 0; --i) {
            printf("%d", D[i]);
        }
        puts("");
    }
};

void rotateLeft(int i, int j) {
    int a = board[i][j];
    int b = board[i][j+1];
    int c = board[i+1][j];
    int d = board[i+1][j+1];
    
    board[i][j] = b;
    board[i][j+1] = d;
    board[i+1][j] = a;
    board[i+1][j+1] = c;
}

void rotateRight(int i, int j) {
    int a = board[i][j];
    int b = board[i][j+1];
    int c = board[i+1][j];
    int d = board[i+1][j+1];
    
    board[i][j] = c;
    board[i][j+1] = a;
    board[i+1][j] = d;
    board[i+1][j+1] = b;
}

void nextStep() {
    int n = R * C;
    // permute once
    for (int i = 0; i < n; ++i) {
        step[ next[i] ] = i;
        newAdd[i] = add[i];
    }
    for (int i = 0; i < n; ++i) {
        newAdd[ step[i] ] += add[i];
        if (newAdd[ step[i] ] >= mod) newAdd[ step[i] ] -= mod;
        
        newStep[ next[i] ] = step[i];        
    }
    for (int i = 0; i < n; ++i) {
        next[ newStep[i] ] = i;
    }
    memcpy(add, newAdd, n * sizeof(int));
}

inline void garbleOnce(int i, int j) {
    if (garbling[i][j] == 'R') {
        rotateRight(i, j);
    } else if (garbling[i][j] == 'L') {
        rotateLeft(i, j);
    }    
}

inline void firstGarble() {
    for (int i = 0; i < R - 1; ++i) {
        for (int j = 0; j < C - 1; ++j) {
            add[ board[i][j] ]++;
            garbleOnce(i, j);
        }
    }
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            next[ board[i][j] ] = i * C + j;
        }
    }
}

inline void addAndPermute() {
    int n = R * C;
    for (int i = 0; i < n; ++i) {
        ans[ cur[i] ] += add[i];
        if (ans[ cur[i] ] >= mod) ans[ cur[i] ] -= mod;
        
        newCur[ next[i] ] = cur[i];
    }
    memcpy(cur, newCur, n * sizeof(int));
}

int main(){
    scanf("%d %d %s", &R, &C, buf);
    BigInt turns(buf);
    
    for (int i = 0; i < R - 1; ++i) {
        scanf("%s", garbling[i]);
    }

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            board[i][j] = i * C + j;
            cur[ i * C + j ] = i * C + j;
        }
    }
    
    int S = (R - 1) * (C - 1);
    int extra = turns.mod(S);
    turns.div(S);
    if (turns > 0) {
        firstGarble();
        if (turns.odd()) {
            addAndPermute();
        } 
        
        turns.div(2);
        while (turns > 0) {
            nextStep();
            if (turns.odd()) {
                addAndPermute();
            }
            turns.div(2);
        }
    }
  
    int n = R * C;
    for (int i = 0; i < n; ++i) {
        int r = i / C;
        int c = i % C;
        board[r][c] = cur[i];
    }

    for (int i = 0, t = 0; i < R - 1 and t < extra; ++i) {
        for (int j = 0; j < C - 1 and t < extra; ++t, ++j) {
            ans[ board[i][j] ]++;
            if (ans[ board[i][j] ] >= mod) ans[ board[i][j] ] -= mod;
            garbleOnce(i, j);
        }
    }
    
    for (int i = 0; i < n; ++i) {
        printf("%d\n", ans[i]);
    }
    return 0;
}