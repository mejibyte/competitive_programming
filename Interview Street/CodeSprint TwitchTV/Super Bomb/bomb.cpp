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

int rows, cols, best, bound;

bool row[MAXN], col[MAXN]; // if this row is taken or not

bool bomb[MAXN][MAXN];

void search(int i, int j, int score) {
//    printf("i = %d, j = %d, score = %d\n", i, j, score);
    
    if (score > best) best = score;
    
    if (score == bound) return;

    
    if (j == cols) {
        search(i + 1, 0, score);
        return;
    }
    if (i == rows) return;
    
    if (!bomb[i][j]) {
        search(i, j + 1, score);
        return;
    }
    
    if (!row[i] and !col[j]) {
        row[i] = true;
        col[j] = true;
        search(i + 1, 0, score + 1);
        row[i] = false;
        col[j] = false;
        search(i, j + 1, score);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin >> rows >> cols;
    bound = min(rows, cols);
    
    int total_bombs = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int k; cin >> k;
            bomb[i][j] = k;
            total_bombs += k;
        }
    }
    bound = min(bound, total_bombs);
    
    best = 0;
    search(0, 0, 0);
    cout << best << endl;
    return 0;
}