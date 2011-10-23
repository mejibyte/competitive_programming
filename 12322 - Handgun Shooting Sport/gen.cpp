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

#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl

bool point_in_box(double x, double y,
                  double x0, double y0,
                  double x1, double y1){
  return
    min(x0, x1) <= x && x <= max(x0, x1) &&
    min(y0, y1) <= y && y <= max(y0, y1);
}

int direction(int x1, int y1, int x2, int y2, int x3, int y3) {
    return (x3 - x1) * (y2 - y1) - (y3 - y1) * (x2 - x1);
}

bool segment_segment_intersection(int x1, int y1,
                                  int x2, int y2,
                                  
                                  int x3, int y3,
                                  int x4, int y4){
                                      
    int d1 = direction(x3, y3,   x4, y4,   x1, y1);
    int d2 = direction(x3, y3,   x4, y4,   x2, y2);
    int d3 = direction(x1, y1,   x2, y2,   x3, y3);
    int d4 = direction(x1, y1,   x2, y2,   x4, y4);
    bool b1 = d1 > 0 and d2 < 0 or d1 < 0 and d2 > 0;
    bool b2 = d3 > 0 and d4 < 0 or d3 < 0 and d4 > 0;
    if (b1 and b2) return true;
    if (d1 == 0 and point_in_box(x1, y1,     x3, y3, x4, y4))
        return true;

    if (d2 == 0 and point_in_box(x2, y2,     x3, y3, x4, y4))
        return true;

    if (d3 == 0 and point_in_box(x3, y3,     x1, y1, x2, y2))
        return true;

    if (d4 == 0 and point_in_box(x4, y4,     x1, y1, x2, y2))
        return true;

    return false;
}

int main(){    
    int times = 100;
    const int MAXCOORD = 1000;
    while (times--) {
        int B = rand() % 100 + 1;
        vector< pair< pair<int, int>, pair<int, int> > > segments;
        for (int i = 0; i < B; ++i) {
            while (true) {
                int x0 = (rand() % MAXCOORD) * (rand() % 2 == 0 ? 1 : -1);
                int y0 = (rand() % MAXCOORD) + 1;
                int x1 = (rand() % MAXCOORD) * (rand() % 2 == 0 ? 1 : -1);
                int y1 = (rand() % MAXCOORD) + 1;
                if (x0 * y1 - x1 * y0 == 0) continue;
                bool intersect = false;
                for (int i = 0; i < segments.size() and !intersect; ++i) {
                    intersect |= segment_segment_intersection(x0, y0, x1, y1,     segments[i].first.first, segments[i].first.second, segments[i].second.first, segments[i].second.second);
                }
                if (intersect) continue;
                segments.push_back(make_pair( make_pair(x0, y0),  make_pair(x1, y1)   ));
                break;
            }
        }
        assert(segments.size() == B);
        printf("%d\n", B);
        for (int i = 0; i < B; ++i) {
            printf("%d %d %d %d\n", segments[i].first.first, segments[i].first.second, segments[i].second.first, segments[i].second.second);
        }
    }
    puts("0");
    return 0;
}