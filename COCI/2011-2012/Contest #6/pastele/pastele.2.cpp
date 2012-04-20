// Andrés Mejía

// It's not working for some reason, but I'm too lazy right now to debug it.

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
int K, x0, y0, z0;

int get_sum(int x0, int x1, int y0, int y1, int z0, int z1) {
    x1 = min(x1, 255);
    y1 = min(y1, 255);
    z1 = min(z1, 255);
    
    int ans = cube[x1][y1][z1];
    if (x0 - 1 >= 0) ans += cube[x0 - 1][y1][z1];
    if (y0 - 1 >= 0) ans += cube[x1][y0 - 1][z1];
    if (z0 - 1 >= 0) ans += cube[x1][y1][z0 - 1];
    if (x0 - 1 >= 0 and y0 - 1 >= 0) ans -= cube[x0 - 1][y0 - 1][z1];
    if (x0 - 1 >= 0 and z0 - 1 >= 0) ans -= cube[x0 - 1][y1][z0 - 1];
    if (y0 - 1 >= 0 and z0 - 1 >= 0) ans -= cube[x1][y0 - 1][z0 - 1];
    if (x0 - 1 >= 0 and y0 - 1 >= 0 and z0 - 1 >= 0) ans += cube[x0 - 1][y0 - 1][z0 - 1];
    return ans;
}

bool check(int S) {
    for (int x = 0; x < 256; ++x) {
        for (int y = 0; y < 256; ++y) {
            for (int z = 0; z < 256; ++z) {
                int sum = get_sum(x, x + S, y, y + S, z, z + S);
                if (sum >= K) {
                    printf("S = %d, sum = %d\n", S, sum);
                    x0 = x + S - 1, y0 = y + S - 1, z0 = z + S - 1;
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
    
    for (int x = 0; x < 256; ++x) {
        for (int y = 0; y < 256; ++y) {
            for (int z = 0; z < 256; ++z) {
                if (x - 1 >= 0) cube[x][y][z] += cube[x - 1][y][z];
                if (y - 1 >= 0) cube[x][y][z] += cube[x][y - 1][z];
                if (z - 1 >= 0) cube[x][y][z] += cube[x][y][z - 1];
                if (x - 1 >= 0 and y - 1 >= 0) cube[x][y][z] -= cube[x - 1][y - 1][z];
                if (x - 1 >= 0 and z - 1 >= 0) cube[x][y][z] -= cube[x - 1][y][z - 1];
                if (y - 1 >= 0 and z - 1 >= 0) cube[x][y][z] -= cube[x][y - 1][z - 1];
                if (x - 1 >= 0 and y - 1 >= 0 and z - 1 >= 0) cube[x][y][z] += cube[x - 1][y - 1][z - 1];
            }
        }
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