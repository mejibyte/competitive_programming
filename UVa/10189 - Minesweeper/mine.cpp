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

const int MAXN = 105;

char board[MAXN][MAXN];

int rows, cols;

bool inside(int i, int j) {
    return 0 <= i and i < rows and 0 <= j and j < cols;
}

int main(){
    int run = 1;
    while (cin >> rows >> cols) {
        if (rows == 0 and cols == 0) break;
        if (run > 1) cout << endl;
        
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cin >> board[i][j];
            }
        }
        
        cout << "Field #" << run++ << ":" << endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (board[i][j] == '*') cout << '*';
                else {
                    int count = 0;
                    for (int di = -1; di <= +1; ++di) {
                        for (int dj = -1; dj <= +1; ++dj) {
                            if ((di != 0 or dj != 0) and inside(i + di, j + dj) and board[i + di][j + dj] == '*') {
                                count++;
                            }
                        }
                    }
                    cout << count;
                }
            }
            cout << endl;
        }
    }
    
    return 0;
}