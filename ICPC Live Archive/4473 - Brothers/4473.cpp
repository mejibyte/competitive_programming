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

const int MAXN = 105;

int field[2][MAXN][MAXN];

int di[] = {+0, +0, -1, +1};
int dj[] = {-1, +1, +0, +0};

int main(){
    int N, R, C, K;
    while (cin >> N >> R >> C >> K) {
        if (N == 0) break;
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                cin >> field[0][i][j];
            }
        }
        int cur = 0;
        while (K--) {
            int next = cur ^ 1;
            for (int i = 0; i < R; ++i) {
                for (int j = 0; j < C; ++j) {
                    int here = field[cur][i][j];
                    bool hated = false;
                    for (int d = 0; d < 4; ++d) {
                        int ni = i + di[d];
                        int nj = j + dj[d];
                        if (0 <= ni and ni < R and 0 <= nj and nj < C) {
                            int there = field[cur][ni][nj];
                            if ((there + 1) % N == here) hated = true;
                        }
                    }
                    field[next][i][j] = hated ? (here + N - 1) % N : here;
                }
            }
            cur = next;
        }
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                if (j > 0) cout << " ";
                cout << field[cur][i][j];
            }
            cout << endl;
        }
    }
    return 0;
}