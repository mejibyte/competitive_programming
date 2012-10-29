// Andrés Mejía
// Accepted
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

struct Box {
   long long x1, y1, z1, x2, y2, z2;
   Box(long long _x1, long long _y1, long long _z1, long long _x2, long long _y2, long long _z2) {
      x1 = min(_x1, _x2);
      x2 = max(_x1, _x2);
      y1 = min(_y1, _y2);
      y2 = max(_y1, _y2);
      z1 = min(_z1, _z2);
      z2 = max(_z1, _z2);
   }
   Box(){}
};

vector<Box> points;
long long X, Y, Z;

void normalize(vector<long long> &v) {
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
}

int compress(long long x, const vector<long long> &v) {
    int ans = lower_bound(v.begin(), v.end(), x) - v.begin();
    assert(ans < v.size() and v[ans] == x);
    return ans;
}

const int MAXN = 105;

bool covered[MAXN][MAXN][MAXN];
int next[MAXN][MAXN][MAXN];

int find(int x, int y, int z){
    if (!covered[x][y][z]) return z;
    int ans = find(x, y, next[x][y][z]);
    next[x][y][z] = ans;
    return ans;
}


bool works(long long side) {
    vector<Box> b;
    vector<long long> all_x, all_y, all_z;
    all_x.push_back(0);
    all_x.push_back(X);
    all_y.push_back(0);
    all_y.push_back(Y);
    all_z.push_back(0);
    all_z.push_back(Z);

    for (int i = 0; i < points.size(); ++i) {
        long long x1 = max(points[i].x1 - side, 0LL);
        long long x2 = min(points[i].x1 + side, X);
        long long y1 = max(points[i].y1 - side, 0LL);
        long long y2 = min(points[i].y1 + side, Y);
        long long z1 = max(points[i].z1 - side, 0LL);
        long long z2 = min(points[i].z1 + side, Z);
        
        b.push_back(Box(x1, y1, z1, x2, y2, z2));
        
        all_x.push_back(x1);
        all_x.push_back(x2);
        all_y.push_back(y1);
        all_y.push_back(y2);
        all_z.push_back(z1);
        all_z.push_back(z2);
    }
    normalize(all_x);
    normalize(all_y);
    normalize(all_z);
    
    int zero_x = compress(0, all_x);
    int last_x = compress(X, all_x);
    int zero_y = compress(0, all_y);
    int last_y = compress(Y, all_y);
    int zero_z = compress(0, all_z);
    int last_z = compress(Z, all_z);

    assert(all_x.size() < MAXN);
    assert(all_y.size() < MAXN);
    assert(all_z.size() < MAXN);
            
    for (int x = 0; x < all_x.size(); ++x) {
        for (int y = 0; y < all_y.size(); ++y) {
            for (int z = 0; z <= all_z.size(); ++z) {
                covered[x][y][z] = false;
                next[x][y][z] = z + 1;
            }
        }
    }
    
    for (int i = 0; i < b.size(); ++i) {
        b[i].x1 = compress(b[i].x1, all_x);
        b[i].x2 = compress(b[i].x2, all_x);
        b[i].y1 = compress(b[i].y1, all_y);
        b[i].y2 = compress(b[i].y2, all_y);
        b[i].z1 = compress(b[i].z1, all_z);
        b[i].z2 = compress(b[i].z2, all_z);
        
        for (int x = b[i].x1; x < b[i].x2; ++x) {
            for (int y = b[i].y1; y < b[i].y2; ++y) {
                for (int z = b[i].z1; z < b[i].z2; z = find(x, y, z)) {
                    covered[x][y][z] = true;
                }
            }
        }
    }
    
    for (int x = zero_x; x < last_x; ++x) {
        for (int y = zero_y; y < last_y; ++y) {
            for (int z = zero_z; z < last_z; ++z) {
                if (!covered[x][y][z]) return false;
            }
        }
    }
    return true;
}

int main(){
    int n, run = 1;
    while (cin >> n >> X >> Y >> Z) {
        if (n == 0 and X == 0 and Y == 0 and Z == 0) break;
        
        X *= 2, Y *= 2, Z *= 2;
        points.resize(n);
        for (int i = 0; i < n; ++i) {
            cin >> points[i].x1 >> points[i].y1 >> points[i].z1;
            points[i].x1 *= 2, points[i].y1 *= 2, points[i].z1 *= 2;
        }
        
        long long low = 0, high = max(X, max(Y, Z)) + 1;
        while (low < high) {
            int mid = (low + high) / 2;
            if (works(mid)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        assert(0 < low and low <= (int)2e9);
        assert(works(low) and !works(low - 1));
        cout << run++ << ". " << low << endl;
    }
    return 0;
}