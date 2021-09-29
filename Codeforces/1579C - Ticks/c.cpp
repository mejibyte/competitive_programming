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
using namespace std;

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cerr << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////


bool black[25][25];
char board[25][25];
int rows, cols;

bool inside(int r, int c) {
    return 0 <= r and r < rows and 0 <= c and c < cols;
}

int max_length(int r, int c) {
    assert(board[r][c] == '*');
    int length = 0;

    int c1, c2;
    c1 = c;
    c2 = c;

    while (true) {
        r--;
        c1--;
        c2++;
        if (!inside(r, c1) or !inside(r, c2)) break;
        if (board[r][c1] != '*' or board[r][c2] != '*') break;
        length++;
    }
    return length;
}

void paint(int r, int c) {
    assert(board[r][c] == '*');
    black[r][c] = true;
    int c1, c2;
    c1 = c;
    c2 = c;

    while (true) {
        r--;
        c1--;
        c2++;
        if (!inside(r, c1) or !inside(r, c2)) break;
        if (board[r][c1] != '*' or board[r][c2] != '*') break;
        black[r][c1] = true;
        black[r][c2] = true;
    }
}

void solve() {
    int k;
    cin >> rows >> cols >> k;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            cin >> board[r][c];
            black[r][c] = false;
            //cout << board[r][c];
        }
        //cout << endl;
    }

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (board[r][c] == '.') continue;
            int d = max_length(r, c);
            if (d >= k) {
                //printf("painting at (%d, %d) length=%d\n", r, c, d);
                paint(r, c);
            }
        }
    }

    bool good = true;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (board[r][c] == '*' and !black[r][c]) {
                good = false;
                break;
            }
        }
    }
    cout << (good ? "YES" : "NO") << endl;

}

int main(){
    #ifndef LOCAL
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    #endif

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
