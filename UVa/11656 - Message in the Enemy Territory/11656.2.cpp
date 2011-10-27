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

const int MAXC = 1035;

bool blocked[MAXC][MAXC];

vector< int > YgivenX[MAXC], XgivenY[MAXC];

inline bool inside(int x, int y) {
    return (0 <= x and x < MAXC and 0 <= y and y < MAXC);
}


void markCorner(int x, int y, int m) {
    for (int xx = x - m; xx <= x + m; ++xx) {
        for (int yy = y - m; yy <= y + m; ++yy) {
            if (!inside(xx, yy)) continue;
            if ( (xx - x) * (xx - x) + (yy - y) * (yy - y) <= m * m ) { // very close to the border, or ON the border
                blocked[xx][yy] = true;
            }
        }
    }
}

void markHorizontalLine(int x0,  int x1,  int y,    int m) {
    for (int xx = x0; xx <= x1; ++xx) {
        for (int yy = y - m; yy <= y + m; ++yy) {
            if (!inside(xx, yy)) continue;
            blocked[xx][yy] = true;
        }
    }
}

void markVerticalLine(int y0, int y1,    int x,     int m) {
    for (int yy = y0; yy <= y1; ++yy) {
        for (int xx = x - m; xx <= x + m; ++xx) {
            if (!inside(xx, yy)) continue;
            blocked[xx][yy] = true;
        }
    }
}


bool canReach(int sx, int sy,   int fx,  int fy) {
    assert(inside(sx, sy) and (fx, fy));
    assert(!blocked[sx][sy]);
    assert(!blocked[fx][fy]);
    queue< pair< int, int > > q;
    blocked[sx][sy] = true;
    q.push( make_pair(sx, sy) );
    while (q.size()) {
        int cx = q.front().first, cy = q.front().second;
        if (cx == fx and cy == fy) return true;
        q.pop();
        assert(blocked[cx][cy]);
        for (int dx = -1; dx <= +1; dx++) {
            for (int dy = -1; dy <= +1; dy++) {
                int nx = cx + dx;
                int ny = cy + dy;
                if (!inside(nx, ny)) continue;
                if (blocked[nx][ny]) continue;
                blocked[nx][ny] = true;
                q.push(  make_pair(nx, ny)  );
            }
        }
    }
    return false;
}


int main(){
    int n, m;
    while (cin >> n >> m) {
        if (n == 0 and m == 0) break;
        
        assert(n % 2 == 0);
        
        For(i, 0, MAXC) YgivenX[i].clear(), XgivenY[i].clear();
        memset(blocked, 0, sizeof blocked);
        
        For(i, 0, n) {
            int x, y; cin >> x >> y;
            XgivenY[y].push_back( x );
            YgivenX[x].push_back( y );
        }        
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        For(x, 0, MAXC) {
            sort(YgivenX[x].begin(), YgivenX[x].end());
            assert(YgivenX[x].size() % 2 == 0);
            for (int k = 0; k < YgivenX[x].size(); k += 2) {
                int y = YgivenX[x][k];
                int nextY = YgivenX[x][k+1];
                
                markVerticalLine(y, nextY,   x,   m);
                markCorner(x, y, m);
                markCorner(x, nextY, m);
            }
        }
        
        For(y, 0, MAXC) {
            sort(XgivenY[y].begin(), XgivenY[y].end());
            assert(XgivenY[y].size() % 2 == 0);
            for (int k = 0; k < XgivenY[y].size(); k += 2) {
                int x = XgivenY[y][k];
                int nextX = XgivenY[y][k+1];
                
                markHorizontalLine(x, nextX,  y,  m);
                markCorner(x, y, m);
                markCorner(nextX, y, m);
            }
        }
        if (canReach(x1, y1,  x2, y2)) {
            puts("Yes");
        } else {
            puts("No");
        }
    }
    return 0;
}