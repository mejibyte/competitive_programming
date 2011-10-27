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

#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

struct point {
    long double x, y;
    point(){}
    point(long double x, long double y) : x(x), y(y) {}
};

typedef pair<point, point> segment;
typedef pair<long double, long double> interval;

struct circle {
    point center;
    int radius;
};

const int MAXB = 1005;
circle columns[MAXB];
point bulbs[MAXB];

inline long double length(const segment &s) {
    long double dx = s.first.x - s.second.x;
    long double dy = s.first.y - s.second.y;
    return hypotl(dx, dy);
}

pair< bool, long double > segmentIntersection(const segment& s1, const segment& s2) {
    point p1 = s1.first;
    point p2 = s1.second;
    point p3 = s2.first;
    point p4 = s2.second;

    long double den = (p4.y-p3.y)*(p2.x-p1.x) - (p4.x-p3.x)*(p2.y-p1.y);
    long double ua_num = (p4.x-p3.x)*(p1.y-p3.y) - (p4.y-p3.y)*(p1.x-p3.x);
    long double ub_num = (p2.x-p1.x)*(p1.y-p3.y) - (p2.y-p1.y)*(p1.x-p3.x);

    if (cmp(den, 0) == 0) {
        // Caso en que los segmentos son paralelos
        if (cmp(ua_num - ub_num, 0) == 0 && cmp(ub_num, 0) == 0) {
            // Las rectas son coincidentes, esto no deberia ocurrir
            assert(false);
        }
        return make_pair(false, 0);
    }

    if (cmp(ub_num/den, 0) >= 0) {
        return make_pair(true, ua_num/den);
    }
    return make_pair(false, 0);
}


interval findShadow(const segment &wall, const point &light, const circle &column) {
    long double dx = 1.0L * column.center.x - light.x;
    long double dy = 1.0L * column.center.y - light.y;
    long double h = sqrt(dx * dx + dy * dy);
    long double beta = atan2(dy, dx);
    long double alpha = asin(column.radius / h);
    
    //printf("Radius = %d, h = %Lf, r / h = %Lf\n", column.radius, h, column.radius / h);
    //printf("beta = %Lf\n", beta);
    //printf("alpha = %Lf\n", alpha);
    
    long double d = sqrt(h * h - column.radius * column.radius);
    point a(light.x + d * cos(beta + alpha), light.y + d * sin(beta + alpha));
    point b(light.x + d * cos(beta - alpha), light.y + d * sin(beta - alpha));
    
    // printf("Must intersect segment that starts at (%Lf, %Lf) and advances up to (%Lf, %Lf)\n", light.x, light.y, light.x + d * cos(beta + alpha), light.y + d * sin(beta + alpha));
    // printf("Must intersect segment that starts at (%Lf, %Lf) and advances up to (%Lf, %Lf)\n", light.x, light.y, light.x + d * cos(beta - alpha), light.y + d * sin(beta - alpha));
    
    pair<bool, long double> p1 = segmentIntersection(wall, segment(light, a) );
    pair<bool, long double> p2 = segmentIntersection(wall, segment(light, b) );
            
    interval shadow;
    long double length = hypotl(wall.first.x - wall.second.x, wall.first.y - wall.second.y);
    
    if (!p1.first) {
        if (!p2.first) {
            // Everything's lit, no shadow.
            return interval(0, 0);
        } else {
            shadow = interval(0, p2.second);
        }
    } else {
        if (!p2.first) {
            shadow = interval(p1.second, 1);
        } else {
            shadow = interval(p1.second, p2.second);
        }
    }
    shadow.first = max(0.0L, min(1.0L, shadow.first) );
    shadow.second = max(0.0L, min(1.0L, shadow.second) );
        
    shadow.first *= length;
    shadow.second *= length;
    //printf("Shadow: [%Lf, %Lf]\n", shadow.first, shadow.second);
    return shadow;
}

vector< interval > merge(vector<interval> &v) {
    sort(v.begin(), v.end());
    vector< interval > ans;
    if (v.size() <= 1) return v;
    long double left = v[0].first, right = v[0].second;
    for (int i = 0; i < v.size(); ++i) {
        if (i + 1 < v.size() and cmp(left, v[i+1].first) <= 0 and cmp(v[i+1].first, right) <= 0 ) {
            right = max(right, v[i+1].second);
        } else {
            if (cmp(right - left, 0) > 0) {
                ans.push_back( interval(left, right) );
            }
            if (i + 1 < v.size()) {
                left = v[i + 1].first;
                right = v[i + 1].second;
            }
        }
    }
    return ans;
}

vector< interval > invert(const vector<interval> v, long double length) {
    if (v.size() == 0) { 
        return vector<interval>(1, interval(0, length) ); // Everything
    }
    
    vector< interval > ans;
    // Before the beginning
    if (cmp(0, v[0].first) < 0) {
        ans.push_back(interval(0, v[0].first));
    }
    
    // between
    for (int i = 0; i < v.size() - 1; ++i) {
        ans.push_back(interval(v[i].second, v[i + 1].first) );
    }
    
    // After the end
    if (cmp(v.back().second, length) < 0) {
        ans.push_back(interval(v.back().second, length));
    }
    return ans;
}

int main(){
    int L, C, X, Y;
    while (scanf("%d %d %d %d", &L, &C, &X, &Y) == 4) {
        if (L == 0 and C == 0 and X == 0 and Y == 0) break;
        for (int i = 0; i < L; ++i) {
            int x, y;
            scanf("%d %d", &x, &y);
            bulbs[i].x = x;
            bulbs[i].y = y;
        }
        for (int i = 0; i < C; ++i){
            int x, y, r;
            scanf("%d %d %d", &x, &y, &r);
            columns[i].center.x = x;
            columns[i].center.y = y;
            columns[i].radius = r;
        }

        vector< segment > walls;
        walls.push_back(  segment(point(0, 0), point(0, Y))   );
        walls.push_back(  segment(point(0, Y), point(X, Y))   );
        walls.push_back(  segment(point(X, Y), point(X, 0))   );
        walls.push_back(  segment(point(X, 0), point(0, 0))   );
        
        long double ans = 0;
        for (int i = 0; i < walls.size(); ++i) {
            vector< interval > allLights; // lights on this wall caused by all different lightbulbs
            for (int j = 0; j < L; ++j) {
                vector< interval > shadows; // shadows on this wall caused only by this light
                for (int k = 0; k < C; ++k) {
                    shadows.push_back( findShadow(walls[i], bulbs[j], columns[k]) );
                }
                
                // printf("Shadows on wall (%.0Lf, %.0Lf) to (%.0Lf, %.0Lf) caused by light at (%.0Lf, %.0Lf):\n",
                //     walls[i].first.x, walls[i].first.y, walls[i].second.x, walls[i].second.y, bulbs[j].x, bulbs[j].y);
                // printf("Before merging:\n");
                // for (int k = 0; k < shadows.size(); ++k) { printf("[%Lf, %Lf] ", shadows[k].first, shadows[k].second); } puts("");
                
                shadows = merge(shadows); // Merge overlapping shadows
                
                // printf("After merging:\n");
                // for (int k = 0; k < shadows.size(); ++k) { printf("[%Lf, %Lf] ", shadows[k].first, shadows[k].second); } puts("");                
                
                // Everything that's not a shadow caused by this light, is certainly lit.
                vector<interval> lights = invert(shadows, length(walls[i]) );
                
                // printf("Sections I know to be lit on wall (%.0Lf, %.0Lf) to (%.0Lf, %.0Lf) caused by light at (%.0Lf, %.0Lf):\n",
                //                                          walls[i].first.x, walls[i].first.y, walls[i].second.x, walls[i].second.y, bulbs[j].x, bulbs[j].y);
                //                                 for (int k = 0; k < lights.size(); ++k) { printf("[%Lf, %Lf] ", lights[k].first, lights[k].second); } puts("");
                allLights.insert(allLights.end(), lights.begin(), lights.end());
            }
            allLights = merge(allLights); // Merge overlapping lit zones
            for (int i = 0; i < allLights.size(); ++i) {
                //printf("Lit: [%Lf, %Lf]\n", allLights[i].first, allLights[i].second);
                ans += allLights[i].second - allLights[i].first;
            }
        }
        printf("%.4Lf\n", ans);
        
    }
    return 0;
}