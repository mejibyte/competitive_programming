#include<iostream>
#include<queue>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
#include<string>
#include<cstring>
#include<map>
#include<numeric>
#include<sstream>
#include<cmath>
using namespace std;
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define pb push_back
#define f(i,x,y) for(int i = x; i<y; i++)
#define FOR(it,A) for(typeof A.begin() it = A.begin(); it!= A.end(); it++)
#define quad(x) (x) * (x)
#define mp make_pair
#define clr(x, y) memset(x, y, sizeof x)
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, ll> pii;
typedef long double ld;
#define N 50
#define M 102
int n;
ll X[N], Y[N], Z[N], xx, yy, zz;
ll x[N][2], y[N][2], z[N][2];
pii allx[M], ally[M], allz[M];
void compress(pii p[], int& tot, ll a[][2], ll T){
    p[tot++] = mp(0, -1);
    p[tot++] = mp(T, -1);
    sort(p, p + tot);
    int sz = 0;
    f(i, 0, tot){
        if(i == 0 || p[i].fst != p[i - 1].fst) sz++;
        if(p[i].snd >= 0)
            a[p[i].snd / 2][p[i].snd % 2] = sz - 1;
    }
    tot = sz - 1;
}
int sum[M][M][M];
bool sirve(int len){
    int totx = 0, toty = 0, totz = 0;
    f(i, 0, n){
        x[i][0] = max(0LL, X[i] - len);
        x[i][1] = min(xx, X[i] + len);
        allx[totx++] = mp(x[i][0], i * 2);
        allx[totx++] = mp(x[i][1], i * 2 + 1);
        
        y[i][0] = max(0LL, Y[i] - len);
        y[i][1] = min(yy, Y[i] + len);
        ally[toty++] = mp(y[i][0], i * 2);
        ally[toty++] = mp(y[i][1], i * 2 + 1);
        
        z[i][0] = max(0LL, Z[i] - len);
        z[i][1] = min(zz, Z[i] + len);
        allz[totz++] = mp(z[i][0], i * 2);
        allz[totz++] = mp(z[i][1], i * 2 + 1);
    }
    compress(allx, totx, x, xx);
    compress(ally, toty, y, yy);
    compress(allz, totz, z, zz);
    f(i, 0, totx) f(j, 0, toty) f(k, 0, totz) sum[i][j][k] = 0;
    f(it, 0, n)
        f(i, x[it][0], x[it][1])
        f(j, y[it][0], y[it][1])
            sum[i][j][z[it][0]]++,
            sum[i][j][z[it][1]]--;

    f(i, 0, totx) f(j, 0, toty){
        int s = 0;
        f(k, 0, totz){
            s += sum[i][j][k];
            if(s <= 0) return false;
        }
    }
    return true;
}
int main(){
    int caso = 1;
    while(scanf("%d %lld %lld %lld", &n, &xx, &yy, &zz) && n){
        xx *= 2;
        yy *= 2;
        zz *= 2;
        f(i, 0, n) scanf("%lld %lld %lld", X + i, Y + i, Z + i),
            X[i] *= 2, Y[i] *= 2, Z[i] *= 2;
        ll le = 0, ri = max(xx, max(yy, zz));
        while(le < ri){
            ll me = (le + ri) / 2;
            if(sirve(me)) ri = me;
            else le = me + 1;
        }
        cout << caso++ << ". " << le  << endl;
    }
}
