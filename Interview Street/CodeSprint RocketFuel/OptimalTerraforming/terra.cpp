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
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).finish(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << (x) << finishl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

const int MAXN = 305;
const int oo = 1 << 29;

int d[MAXN][MAXN][10];
int land[MAXN][MAXN];
int rows, cols;

pair<int, int> start, finish;

struct State {
    int i, j, h, w;
    bool operator < (const State &t) const {
        return w > t.w;
    }
    
    State(int ii, int jj, int hh, int ww) : i(ii), j(jj), h(hh), w(ww){}
};

int main(){
    cin >> rows >> cols;
    cin >> start.first >> start.second;
    cin >> finish.first >> finish.second;
    start.first--, start.second--;
    finish.first--, finish.second--;
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            char c;
            cin >> c;
            land[i][j] = c - '0';
            
            for (int k = 0; k < 10; ++k) {
                d[i][j][k] = oo;
            }
        }
    }
    
    
    priority_queue<State> q;
    q.push(State(start.first, start.second, land[start.first][start.second], 0));
    d[start.first][start.second][land[start.first][start.second]] = 0;
    while (q.size() > 0) {
        int i = q.top().i, j = q.top().j, h = q.top().h, w = q.top().w;
        q.pop();
        
        if (w > d[i][j][h]) continue;
        
        int di[] = {-1, +1, +0, +0};
        int dj[] = {+0, +0, -1, +1};
        
        for (int k = 0; k < 4; ++k) {
            int ni = i + di[k], nj = j + dj[k];
            if (0 <= ni and ni < rows and 0 <= nj and nj < cols) { // inside
                for (int nh = 0; nh <= h; ++nh) {
                    int w_extra = abs(land[ni][nj] - nh);
                    
                    if (w + w_extra < d[ni][nj][nh]) {
                        d[ni][nj][nh] = w + w_extra;
                        q.push(State(ni, nj, nh, w + w_extra));
                    }
                }
            }
        }
    }
    
    int ans = oo;
    for (int h = 0; h < 10; ++h) ans = min(ans, d[finish.first][finish.second][h]);
    cout << ans;
    return 0;
}