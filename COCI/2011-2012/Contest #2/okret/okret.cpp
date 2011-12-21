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

const int MAXN = 15;
char town[MAXN][MAXN];

int rows, cols;

int solve() {
    for (int i = 1; i <= rows; ++i) {
        for(int j = 1; j < cols; ++j) {
            if (town[i][j] != '.') continue;
            int count = 0;
            for (int di = -1; di <= 1; ++di) {
                for(int dj = -1; dj <= 1; ++dj) {
                    if (abs(di) + abs(dj) != 1) continue;
                    if (town[i + di][j + dj] == '.') count++;
                }
            }
            if (count <= 1) {
                return 1;
            }
        }
    }
    return 0;
}

int main(){
    cin >> rows >> cols;
    memset(town, 'X', sizeof town);
    for(int i = 1; i <= rows; ++i) {
        for (int j = 1; j <= cols; ++j) {
            cin >> town[i][j];
        }
    }
    cout << solve() << endl;
    return 0;
}