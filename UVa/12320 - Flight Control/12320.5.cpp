// Ternary search and binary search. Accepted.
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

template <class T> string toStr(const T &x) { stringstream s; s << x; return s.str(); }
template <class T> int toInt(const T &x) { stringstream s; s << x; int r; s >> r; return r; }

#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
#define D(x) cout << #x " = " << (x) << endl

namespace IO {
#define MAXBUFF (1<<20)
   char buffer[MAXBUFF], *p = buffer+MAXBUFF;
   char buffer2[MAXBUFF], *p2 = buffer2;
   
   inline char read_char() {
      if( p == buffer+MAXBUFF ) {
         fread( buffer, 1, MAXBUFF, stdin );
         p = buffer;
      }
      return *p++;
   }

   inline int read_int() {
      char c = read_char();
      while( !isdigit(c) and c != '-' ) c = read_char();
      int sign = c == '-' ? -1 : +1;
      if (c == '-') c = read_char();
      int ret = c-'0';
      while( isdigit(c = read_char()) ) ret = ret * 10 + c-'0';
      return ret * sign;
   }

   void flush() {
      fwrite( buffer2, 1, p2-buffer2, stdout );
      p2 = buffer2;
   }

   inline void write( char c ) {
      if( p2 == buffer2+MAXBUFF ) {
         fwrite( buffer2, 1, MAXBUFF, stdout );
         p2 = buffer2;
      }
      *p2++ = c;
   }
}

const double EPS = 1e-10;

int cmp(double x, double y = 0, double tol = EPS){
    return( x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

struct point {
    double x, y, z;
    point(){} point(double x, double y, double z) : x(x), y(y), z(z) {}
};

int R[2], V[2];
vector< point > P[2];
double D[2][105];

inline double dist(const point &a, const point &b) {
    double dx = b.x - a.x, dy = b.y - a.y, dz = b.z - a.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

point positionAt(int p, double t) {
    double d = V[p] * t;
    
    int i = upper_bound(D[p], D[p] + P[p].size(), d) - D[p] - 1;
    assert(i >= 0);
    double s = D[p][i];
    double distance = dist(P[p][i], P[p][i+1]);
    //assert(cmp(s + distance, d) >= 0);        
    point ans = P[p][i];
    if (cmp(distance, 0.0) > 0) {
        double dx = P[p][i+1].x - P[p][i].x;
        double dy = P[p][i+1].y - P[p][i].y;
        double dz = P[p][i+1].z - P[p][i].z;
        ans.x += (d - s) * dx / distance;
        ans.y += (d - s) * dy / distance;
        ans.z += (d - s) * dz / distance;
    }
    //assert(cmp(s + dist(P[p][i], ans), d) == 0);
    return ans;
}

double distanceAtTime(double t) {
    point p0 = positionAt(0, t);
    point p1 = positionAt(1, t);
    return dist(p0, p1);
}

double touchAtTime(double t) {
    return cmp(distanceAtTime(t), 0.0 + R[0] + R[1]) <= 0;
}

double findClosestTime(double left, double right) {
    // double bestTime = -1, bestDistance = 1e200;    
    // for (double t = left; t <= right; t += 0.5) {
    //     double d = distanceAtTime(t);
    //     printf("At time %lf, distance is %lf\n", t, d);
    //     if (cmp(d, bestDistance) < 0) {
    //         bestDistance = d;
    //         bestTime = t;
    //     }
    // }

    while (cmp(left, right) < 0) {
        double t1 = (2 * left + right) / 3;
        double t2 = (2 * right + left) / 3;
        double d1 = distanceAtTime(t1);
        double d2 = distanceAtTime(t2);
        if (d1 > d2) {
            left = t1;
        } else {
            right = t2;
        }
    }
    double ans = (left + right) / 2;
    //printf("Best is at time %lf, where distance is %lf\n", ans, distanceAtTime(ans));
    return ans;
}

int main(){
    int casos = IO::read_int(); while (casos--) {
        for (int p = 0; p < 2; ++p) {
            int k; 
            R[p] = IO::read_int(), V[p] = IO::read_int(), k = IO::read_int();
            P[p].resize(k);
            for (int i = 0; i < k; ++i) {
                P[p][i].x = IO::read_int(), P[p][i].y = IO::read_int(), P[p][i].z = IO::read_int();
            }
            P[p].push_back( point(0, 0, 0) );
        }
        
        double totalTime = 1e100;
        for (int p = 0; p < 2; ++p) {
            D[p][0] = 0.0;
            for (int i = 1; i < P[p].size(); ++i) {
                D[p][i] = D[p][i-1] + dist(P[p][i-1], P[p][i]);
            }
            totalTime = min(totalTime, D[p][P[p].size() - 1] / V[p]);
        }
        // D(totalTime);
        // point p1 = positionAt(0, totalTime);
        // point p2 = positionAt(1, totalTime);
        // printf("<%lf, %lf, %lf>\n", p1.x, p1.y, p1.z);
        // printf("<%lf, %lf, %lf>\n", p2.x, p2.y, p2.z);
        vector<double> times;
        for (int p = 0; p < 2; ++p) {
            double d = 0;
            times.push_back(0.0);
            for (int i = 0; i < P[p].size() - 1; ++i) {
                d += dist(P[p][i], P[p][i+1]);
                double t = d / V[p];
                if (cmp(t, totalTime) <= 0) times.push_back(d / V[p]);
            }
        }
        sort(times.begin(), times.end());
        //For(i, 0, times.size() - 1) assert(cmp(times[i], times[i + 1]) <= 0);
        // for (int i = 0; i < times.size(); ++i) {
        //     printf("%lf ", times[i]);
        // }
        // puts("");
        
        int ans = 0;
        for (int i = 0; i < times.size() - 1; ++i) {
            //printf("\nInterval from time (%lf, %lf):\n", times[i], times[i+1]);
            const double &t = times[i];
            if (touchAtTime(t)) {
                //printf("They touch at time %lf, continuing.\n", t);
                continue;
            }
            double closestTime = findClosestTime(t, times[i+1]);
            if (touchAtTime(closestTime)) {
                ans++;
            }
        }
        if (touchAtTime(0.0)) ans++;
        printf("%d\n", ans);
    }
    return 0;
}