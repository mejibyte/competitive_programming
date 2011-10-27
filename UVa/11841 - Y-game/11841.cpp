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

const int MAXN = 25;

bool visited[MAXN][MAXN][MAXN];

bool black[MAXN][MAXN][MAXN];

int dx[] = { -1, +0, +1, +1, +0, -1 };
int dy[] = { +0, -1, -1, +0, +1, +1 };
int dz[] = { +1, +1, +0, -1, -1, +0 };

bool inside(int x, int y, int z) {
    return x >= 0 and y >= 0 and z >= 0;
}

bool blackCanWin(int sx, int sy, int sz, int n) {
    memset(visited, 0, sizeof visited);
    assert(inside(sx, sy, sz) and black[sx][sy][sz]);
    queue<int> q;
    visited[sx][sy][sz] = true;
    q.push(sx); q.push(sy); q.push(sz);
    while (q.size() > 0) {
        int x = q.front(); q.pop();
        int y = q.front(); q.pop();
        int z = q.front(); q.pop();
        //printf("popped %d, %d, %d\n", x, y, z);
        for (int k = 0; k < 6; ++k) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            int nz = z + dz[k];
            if (!inside(nx, ny, nz)) continue;
            if (!black[nx][ny][nz]) continue;
            if (visited[nx][ny][nz]) continue;
            q.push(nx); q.push(ny); q.push(nz);
            visited[nx][ny][nz] = true;
        }
    }
    bool seenX = false, seenY = false, seenZ = false;
    for (int x = 0; x <= n; ++x) {
        for (int y = 0; y <= n; ++y) {
            for (int z = 0; z <= n; ++z) {
                if (!black[x][y][z]) continue;
                if (!visited[x][y][z]) continue;
                seenX |= (x == 0);
                seenY |= (y == 0);
                seenZ |= (z == 0);
                //printf("saw black cell (%d, %d, %d)\n", x, y, z);
            }
        }
    }
    //printf("seenX = %d, seenY = %d, seenZ = %d\n", seenX, seenY, seenZ);
    return seenX and seenY and seenZ;
}

int main(){
    int n, m;
    while (cin >> n >> m) {
        if (n == 0 and m == 0) break;
        memset(visited, 0, sizeof visited);
        memset(black, 0, sizeof black);
       
        for (int k = 0; k < m; ++k) {
            int x, y, z;
            cin >> x >> y >> z;
            black[x][y][z] = true;
        }

        bool blackWins = false;
        for (int x = 0; x <= n; ++x) {
            for (int y = 0; y <= n; ++y) {
                for (int z = 0; z <= n; ++z) {
                    if (!black[x][y][z]) continue;
                    if (visited[x][y][z]) continue;
                    if (x != 0 and y != 0 and z != 0) continue;
                    
                    assert(black[x][y][z]);
                    blackWins |= blackCanWin(x, y, z, n);
                    if (blackWins) {
                        x = y = z = n; // ultra break
                    }
                }
            }
        }
        printf("%s\n", blackWins ? "Benny" : "Willy");
    }
    return 0;
}