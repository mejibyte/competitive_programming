#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <cstring>
#include <numeric>
using namespace std;
typedef long long ll;
#define F0(i,n) for (int i = 0; i < n; i++)
#define F1(i,n) for (int i = 1; i <= n; i++)
#define CL(a,x) memset(x, a, sizeof(x));
#define SZ(x) ((int)x.size())
const double eps = 1e-10;
const int inf = 1000000009;
int an, i, j, k, m, n, l, t[1600][1600], f[4][1600][1600], used[10001];
int ans;
int dx[]={-1,-1,1,1};
int dy[]={-1,1,1,-1};
int id[100000];
vector<int> curr, a[100000];

int cc(int x, int y)
{
    return SZ(a[x]) > SZ(a[y]);
}

void go(int k, int x, int y)
{
    while (!f[k][x][y])
    {
        f[k][x][y] = 1;
        if (t[x][y] && !used[t[x][y]])
        {
            curr.push_back(t[x][y]);
            used[t[x][y]] = 1;
        }
        int x2 = x + dx[k];
        int y2 = y + dy[k];
        int gx = (x2 >= 0 && x2 < m);
        int gy = (y2 >= 0 && y2 < n);
        if (gx && gy)
        {
            x = x2;
            y = y2;
            continue;
        }
        if (!gx && !gy)
        {
            k = (k + 2) % 4;
        }
        else if (gx && !gy)
        {
            k = 1 ^ k;
        } else
        {
            k = 3 - k;
        }
    }
    F0(sz,SZ(curr)) used[curr[sz]] = 0;
}

void solve(int par)
{
    an = 0;
    F0(i,m) F0(j,n) if ((i+j)%2 == par)
    {
        F0(k,4) if (!f[k][i][j])
        {
            curr.clear();
            go(k,i,j);
            if (curr.empty()) continue;
            ans = max(ans, SZ(curr));
            sort(curr.begin(), curr.end());
            a[an++] = curr;
        }
    }
    F0(i,an) id[i] = i; sort(id, id+an, cc);
    for (int ii = 0; ii < an; ii++)
        for (int jj = ii+1; jj < an; jj++)
        {
            int i = id[ii];
            int j = id[jj];
            int ni = SZ(a[i]);
            int nj = SZ(a[j]);
            if (ni + nj < ans) break;
            int x = 0, y = 0, cnt = 0;
            while (x < ni || y < nj)
            {
                cnt++;
                if (x < ni && y < nj && a[i][x] == a[j][y])
                {
                    x++;
                    y++;
                }
                else if (y == nj || (x < ni && a[i][x] < a[j][y])) x++;
                else y++;

            }
            ans = max(ans, cnt);
        }
}

int main() {
    // freopen("input04.txt", "r", stdin);
    CL(0,t);
    cin >> m >> n >> k;
    for (l = 1; l <= k; l++)
    {
        cin >> i >> j;
        t[i][j] = l;
    }
    if (m == 1 || n == 1) ans = min(k, 1);
    else
    {
        solve(0);
        solve(1);
    }
    cout << ans << endl;
    return 0;
} 
// END CUT HERE
