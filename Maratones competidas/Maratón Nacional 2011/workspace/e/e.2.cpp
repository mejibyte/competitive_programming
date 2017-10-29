// Equipo Poncho, Carriel y Ruana
using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
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
#include <stack>
#include <list>
#include <map>
#include <set>

template <class T> string toStr(const T &x)
{ stringstream s; s << x; return s.str(); }
template <class T> int toInt(const T &x)
{ stringstream s; s << x; int r; s >> r; return r; }

#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
#define D(x) cout << #x " = " << (x) << endl;

const double EPS = 1e-9;

int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

#define INPUT_FILE "edgetown"

const int MAXN = 105;
const int oo = 1<<28;

int g1[MAXN][MAXN];
int g2[MAXN][MAXN];
int n;

void floyd(){
    For(k, 0, n) {
        For(i, 0, n) {
            For(j, 0, n) {
                g1[i][j] = min(g1[i][j], g1[i][k] + g1[k][j]);
                g2[i][j] = min(g2[i][j], g2[i][k] + g2[k][j]);                
            }
        }
    }    
}

vector<int> gg1[MAXN], gg2[MAXN];

int dist[MAXN];
void bfs(int start, vector<int> g[MAXN]) {
    For(i, 0, n) dist[i] = oo;
    queue<int> q;
    dist[start] = 0;
    q.push(start);
    while (q.size()) {
        int u = q.front();
        q.pop();

        for (int k = 0; k < g[u].size(); ++k) {
            int v = g[u][k];
            
            if (dist[v] < oo) continue;
            dist[v] = dist[u] + 1;
            q.push(v);            
        }
    }
}

bool equal(long long a, long long b) {
    For(i, 0, n) {
        For(j, 0, n) {
            if (g2[i][j] >= oo) return false;
            long long now = g2[i][j];
            long long cota = g1[i][j] * a + b;
            if (now > cota) {
                //printf("From %d to %d: now = %d, cota = %d, old = %d\n", i, j, (int)now, (int)cota, g1[i][j]);
                return false;
            }
        }
    }
    return true;
}

int main(){
    freopen(INPUT_FILE ".in", "r", stdin);
    while (cin >> n) {
        if (n == 0) break;
        string s; getline(cin, s);
        
        For (i, 0, n) For(j, 0, n) g1[i][j] = g2[i][j] = oo;
        For (i, 0, n) gg1[i].clear(), gg2[i].clear();
        
        for (int i = 0; i < n; ++i) {
            getline(cin, s);
            stringstream sin(s);
            int first; sin >> first; first--;
            int other;
            while (sin >> other) {
                other--;
                g1[first][other] = 1;
                gg1[first].push_back(other);
            }
        }
        
        for (int i = 0; i < n; ++i) {
            getline(cin, s);
            stringstream sin(s);
            int first; sin >> first; first--;
            int other;
            while (sin >> other) {
                other--;
                g2[first][other] = 1;
                gg2[first].push_back(other);
            }
        }
        For(i, 0, n) g1[i][i] = g2[i][i] = 0;
        
        int a, b;
        cin >> a >> b;
        if (a == 0 and b == 0 and n > 1) {
            puts("No");
            continue;
        }
        
        //puts("G1"); For(i, 0, n){  For(j, 0, n) { printf("%10d", g1[i][j]); } puts(""); } puts("");
        //puts("G2"); For(i, 0, n){  For(j, 0, n) { printf("%10d", g2[i][j]); } puts(""); } puts("");
        
        //floyd();
        
        For(i, 0, n) {
            bfs(i, gg1);
            For(j, 0, n) {
                g1[i][j] = dist[j];
            }
            bfs(i, gg2);
            For(j, 0, n) {
                g2[i][j] = dist[j];
            }            
        }
        
        if (equal(a, b)) {
            puts("Yes");
        } else {
            puts("No");
        }
    }
    return 0;

}
