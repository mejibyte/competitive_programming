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

char building[505][505];

int main(){
    int rows, cols;
    cin >> rows >> cols;
    
    int ans[5] = {0};
    for (int i = 0; i < 5 * rows + 1; ++i) {
        for (int j = 0; j < 5 * cols + 1; ++j) {
            cin >> building[i][j];
        }
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int size = 0;
            int r = i * 5 + 1;
            int c = j * 5 + 1;
            while (building[r + size][c] == '*') size++;
            ans[size]++;
        }
    }
    for (int i = 0; i < 5; ++i) cout << ans[i] << " ";
    cout << endl;
    return 0;
}