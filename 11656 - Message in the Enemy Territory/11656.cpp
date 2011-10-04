// Wrong Answer
// Just to make sure the input is well formed and there are no three
// consecutive collineal points in the border of the resulting polygon.
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

typedef pair< int, int > point;
typedef pair< point, point > side;

vector< int > YgivenX[MAXC], XgivenY[MAXC];
vector< side > sides;

bool isSimpleClosedPolygon() {
    point start = sides[0].first;
    
    set<point> seen;
    point cur = start;
    
    do {
        seen.insert(cur);
        point next;
        
        printf("Inserted <%d, %d>\n", cur.first, cur.second);
        for (int i = 0; i < sides.size(); ++i) {
            if (sides[i].first == cur or sides[i].second == cur) {
                next = sides[i].first == cur ? sides[i].second : sides[i].first;
                assert(next != cur);
                if (seen.count(next) == 0) {
                    break;
                }
            }
        }
        printf("next = <%d, %d>\n", next.first, next.second);
        cur = next;
    } while (cur != start);
    
    return seen.size() == sides.size();
}

int main(){
    int n, m;
    while (cin >> n >> m) {
        if (n == 0 and m == 0) break;
        
        assert(n % 2 == 0);
        
        For(i, 0, MAXC) YgivenX[i].clear(), XgivenY[i].clear();
        
        For(i, 0, n) {
            int x, y; cin >> x >> y;
            XgivenY[y].push_back( x );
            YgivenX[x].push_back( y );
        }        
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        
        sides.clear();

        For(x, 0, MAXC) {
            sort(YgivenX[x].begin(), YgivenX[x].end());
            assert(YgivenX[x].size() % 2 == 0);
            for (int k = 0; k < YgivenX[x].size(); k += 2) {
                int y = YgivenX[x][k];
                int nextY = YgivenX[x][k+1];
                
                sides.push_back(  side(point(x, y), point(x, nextY))  );
            }
        }
        
        For(y, 0, MAXC) {
            sort(XgivenY[y].begin(), XgivenY[y].end());
            assert(XgivenY[y].size() % 2 == 0);
            for (int k = 0; k < XgivenY[y].size(); k += 2) {
                int x = XgivenY[y][k];
                int nextX = XgivenY[y][k+1];
                
                sides.push_back(  side(point(x, y), point(nextX, y))  );
            }
        }
        
        assert(sides.size() == n);
        for (int i = 0; i < sides.size(); ++i) {
            printf("There's a side from <%d, %d> to <%d, %d>\n", sides[i].first.first, sides[i].first.second, sides[i].second.first, sides[i].second.second);
        }
        assert(isSimpleClosedPolygon());
        puts("NO");
    }
    return 0;
}