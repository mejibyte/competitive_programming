// https://codeforces.com/contest/1567/submission/127972338
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <ctype.h>
#include <deque>
#include <cstring>
#include <set>
#include <bitset>
#include <map>
#include <chrono>
#include <random>
#include <unordered_map>
#include <stdio.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef std::vector<int> vi;
typedef std::vector<bool> vb;
typedef std::vector<string> vs;
typedef std::vector<double> vd;
typedef std::vector<long long> vll;
typedef std::vector<std::vector<int> > vvi;
typedef vector<vll> vvll;
typedef std::vector<std::pair<int, int> > vpi;
typedef vector<vpi> vvpi;
typedef std::pair<int, int> pi;
typedef std::pair<ll, ll> pll;
typedef std::vector<pll> vpll;

const long long mod = 1000000007;
const unsigned gen_seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937_64 gen(gen_seed);

#define all(c) (c).begin(),(c).end()
#define srt(c) sort(all(c))
#define srtrev(c) sort(all(c)); reverse(all(c))
#define forn(i, a, b) for(int i = a; i < b; i++)
#define read(x) scanf("%d", &x)
#define readv(x, n) vi x(n); forn(i,0,n) scanf("%d", &x[i])

#define pb push_back
#define mp make_pair

struct sega {
    sega(int l = 0, int r = 0, int lval = 0, int rval = 0,  int fr = 0, ll w = 1) : l(l), r(r), lval(lval), rval(rval), fr(fr), w(w) {};
    int l, r, fr, lval, rval;
    ll w;
};

sega combine(sega l, sega r) {
    if(l.l == 0) return r;
    else if(r.l == 0) return l;
    else if(l.fr) {
        if(l.rval <= r.lval) {
            r.w += l.w+ll(r.l) * ll(l.r);
            r.l += l.r;
            if(r.fr) r.r += l.r;
            r.lval = l.lval;
            return r;
        }
        else {
            r.l = l.r;
            r.fr = 0;
            r.w += l.w;
            r.lval = l.lval;
            return r;
        }
    }
    else if(r.fr) {
        if(l.rval <= r.lval) {
            l.w += r.w+ll(l.r) * ll(r.l);
            l.r += r.l;
            l.rval = r.rval;
            return l;
        }
        else {
            l.r = r.l;
            l.fr = 0;
            l.w += r.w;
            l.rval = r.rval;
            return l;
        }
    }
    else {
        if(l.rval <= r.lval) {
            return sega(l.l, r.r, l.lval, r.rval, 0, l.w+r.w +ll(l.r)*r.l);
        }
        else {
            return sega(l.l, r.r, l.lval, r.rval, 0, l.w+r.w);
        }
    }
}

const sega em(0,0,0,0,0,0);

class stree {
public:
    vector<sega> t;
    void build (const vi & a, int v, int tl, int tr) {
        if(v==1) {
            t.resize(a.size() * 4);
        }
        if (tl == tr)
            t[v] = sega(1, 1, a[tl], a[tl], 1, 1);
        else {
            int tm = (tl + tr) / 2;
            build (a, v*2, tl, tm);
            build (a, v*2+1, tm+1, tr);
            t[v] = combine(t[v*2], t[v*2+1]);
        }
    }

    sega get (int v, int tl, int tr, int l, int r) {
        if (l > r)
            return em;
        if (l == tl && r == tr)
            return t[v];
        int tm = (tl + tr) / 2;
        return  combine(
                        get (v*2, tl, tm, l, min(r,tm)),
                        get (v*2+1, tm+1, tr, max(l,tm+1), r)
                        );
    }

    void set (int v, int tl, int tr, int pos, int val) {
        if (tl == tr)
            t[v] = sega(1, 1, val, val, 1, 1);
        else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                set (v*2, tl, tm, pos, val);
            else
                set (v*2+1, tm+1, tr, pos, val);
            t[v] =  combine(t[v*2], t[v*2+1]);
        }
    }
};

int main()
{
// #ifdef LOCAL
//     freopen("input.txt", "rt", stdin);
//     freopen("output.txt", "wt", stdout);
// #endif
    int n,q;
    scanf("%d %d", &n, &q);
    readv(a,n);
    stree st;
    st.build(a, 1, 0, n-1);
    forn(i,0,q) {
        int tp,l,r;
        scanf("%d %d %d", &tp, &l, &r);
        if(tp == 1) {
            l--;
            st.set(1, 0, n-1, l, r);
        }
        else {
            l--; r--;
            printf("%lld\n", st.get(1, 0, n-1, l, r).w);
        }
    }


}
