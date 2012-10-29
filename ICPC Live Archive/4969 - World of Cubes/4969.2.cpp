// Andrés Mejía
// This gives WA and TLE :)
// I think the algorithm is correct though, so there's probably a bug somewhere.

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
    long long x1, x2, y1, y2, z1, z2;

    Box(){}
    Box(long long _x1, long long _x2, long long _y1, long long _y2, long long _z1 = 0, long long _z2 = 0) {
        x1 = min(_x1, _x2);
        x2 = max(_x1, _x2);
        y1 = min(_y1, _y2);
        y2 = max(_y1, _y2);
        z1 = min(_z1, _z2);
        z2 = max(_z1, _z2);
    }
};


vector<Box> points;
long long X, Y, Z;

const int MAXN = 8 * 55;

bool covered[MAXN][MAXN][MAXN];

int compress(const vector<int> &all, int what) {
   return lower_bound(all.begin(), all.end(), what) - all.begin();
}

bool works(long long side) {
    vector<Box> boxes;
    vector<int> all;
    all.push_back(0);
    all.push_back(X);
    all.push_back(Y);
    all.push_back(Z);

    for (int i = 0; i < points.size(); ++i) {
        int x = points[i].x2;
        int y = points[i].y2;
        int z = points[i].z2;

        Box b(x - side, x + side, y - side, y + side, z - side, z + side);
        b.x1 = max(b.x1, 0LL);
        b.x2 = min(b.x2, X);
        b.y1 = max(b.y1, 0LL);
        b.y2 = min(b.y2, Y);
        b.z1 = max(b.z1, 0LL);
        b.z2 = min(b.z2, Z);
        boxes.push_back(b);

        all.push_back(b.x1);
        all.push_back(b.x2);
        all.push_back(b.y1);
        all.push_back(b.y2);
        all.push_back(b.z1);
        all.push_back(b.z2);
    }
    


    memset(covered, false, sizeof covered);
    for (int i = 0; i < boxes.size(); ++i) {
       Box &b = boxes[i];
       b.x1 = compress(all, b.x1);
       b.x2 = compress(all, b.x2);
       b.y1 = compress(all, b.y1);
       b.y2 = compress(all, b.y2);
       b.z1 = compress(all, b.z1);
       b.z2 = compress(all, b.z2);
       
       for (int x = b.x1; x < b.x2; ++x) {
          for (int y = b.y1; y < b.y2; ++y) {
             for (int z = b.z1; z < b.z2; ++z) {
                assert(x < MAXN);
                assert(y < MAXN);
                assert(z < MAXN);
                
                covered[x][y][z] = true;
             }
          }
       }
    }
    
    int zero = compress(all, 0);
    int max_x = compress(all, X);
    int max_y = compress(all, Y);
    int max_z = compress(all, Z);
     
    assert(max_x < MAXN);
    assert(max_y < MAXN);
    assert(max_z < MAXN);
     
     
    for (int x = zero; x < max_x; ++x) {
       for (int y = zero; y < max_y; ++y) {
          for (int z = zero; z < max_z; ++z) {
             if (!covered[x][y][z]) return false;
          }
       }
    }
    return true;
}

int main(){
    int run = 1;
    int n;
    while (cin >> n >> X >> Y >> Z) {
        if (n == 0) break;
        X *= 2, Y *= 2, Z *= 2;
        points.clear();
        for (int i = 0; i < n; ++i) {
            int x, y, z;
            cin >> x >> y >> z;
            x *= 2, y *= 2, z *= 2;
            points.push_back(Box(0, x, 0, y, 0, z));
        }

        long long low = 0, high = max(X, max(Y, Z));
        while (low < high) {
            long long mid = (high - low) / 2 + low;
            if (works(mid)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
//        D(get(low));
//        D(hall_volume);
        
        printf("%d. %lld\n", run++, low);
    }
    return 0;
}