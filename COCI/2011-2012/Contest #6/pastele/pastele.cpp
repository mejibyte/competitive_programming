// Andrés Mejía

// Passed all test cases. Complexity: O(n^3 log n) where n = 256.
// Algorithm: Binary search for the answer. To check if some answer is possible,
// sweep on Z to create a 2D area with points, then sweep on Y to create a single row of points,
// and then sweep on X to find the sum of consecutive elements to see if it's >= K.

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
//#include <cmath>
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

const int MAXN = 256;
int cube[MAXN][MAXN][MAXN];
int square[MAXN][MAXN];
int row[MAXN];
int K, x0, y0, z0;

bool check(int S) {
    memset(square, 0, sizeof square);
        
    for (int z = 0; z < 256; ++z) {
        
        for (int x = 0; x < 256; ++x) {
            for (int y = 0; y < 256; ++y) {
                square[x][y] += cube[x][y][z];
                if (z - S >= 0) square[x][y] -= cube[x][y][z - S];
            }
        }

        // aquí tengo el cuadrado
        memset(row, 0, sizeof row);
        for (int y = 0; y < 256; ++y) {

            for (int x = 0; x < 256; ++x) {
                row[x] += square[x][y];
                if (y - S >= 0) row[x] -= square[x][y - S];
            }

            int sum = 0;
            for (int x = 0; x < 256; ++x) {
                sum += row[x];
                if (x - S >= 0) sum -= row[x - S];
                assert(sum >= 0);
                if (sum >= K) {
                    x0 = x, y0 = y, z0 = z;
                    return true;
                }
            }
        }
    }
    return false;
}

int main(){
    int n; cin >> n >> K;
    for (int i = 0; i < n; ++i) {
        int x, y, z; cin >> x >> y >> z;
        cube[x][y][z]++;
    }
    
    int low = 0, high = 256;
    while (low < high){
        int m = (low + high) / 2;
        if (check(m)) {
            high = m;
        } else {
            low = m + 1;
        }
    }
    cout << low - 1 << endl;
    for (int x = 0; x < 256; ++x) {
        for (int y = 0; y < 256; ++y) {
            for (int z = 0; z < 256; ++z) {
                if (x0 - low < x and x <= x0 and 
                    y0 - low < y and y <= y0 and
                    z0 - low < z and z <= z0) {
                        while (K > 0 and cube[x][y][z] > 0) {
                            printf("%d %d %d\n", x, y, z);
                            cube[x][y][z]--;
                            K--;
                        }
                }
            }
        }
    }
    return 0;
}