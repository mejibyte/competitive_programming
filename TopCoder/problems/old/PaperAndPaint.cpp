// I copied some code from blueblimp because
// I just wanted to test my implementation of
// finding the area of the union of rectangles.

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
#include <bitset>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>

#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << (x) << endl

#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <complex>
#include <setjmp.h>
#include <ext/hash_map>
#include <queue>
using namespace std;
 
#define FR(i,a,b) for(int i=a;i<b;i++)
#define FOR(i,n) FR(i,0,n)
#define FORI(i,v) FOR(i,(int)v.size())
#define FORALL(i,v) for(typeof(v.end())i=v.begin();i!=v.end();++i)
#define BEND(v) v.begin(),v.end()
#define dump(x) cerr << #x << " = " << (x) << endl;
#define PB push_back
typedef long long ll; typedef long double ld;


struct Rect {
  ll x1,y1,x2,y2;
  Rect(ll x1, ll y1, ll x2, ll y2) : x1(x1),y1(y1),x2(x2),y2(y2) {} 
};
struct Evt {
  ll y;
  int what;
  ll x1,x2;
};
bool operator<(Evt a, Evt b) {
  return a.y < b.y;
}


// Here's my algorithm, the one I want to test:

struct Box {
    int x1, x2, y1, y2, z1, z2;

    Box(){}
    Box(int _x1, int _x2, int _y1, int _y2, int _z1 = 0, int _z2 = 0) {
        x1 = min(_x1, _x2);
        x2 = max(_x1, _x2);
        y1 = min(_y1, _y2);
        y2 = max(_y1, _y2);
        z1 = min(_z1, _z2);
        z2 = max(_z1, _z2);
    }
};


struct Event {
    enum { OUT, IN };
    int at, y1, y2, type;

    Event(){}
    Event(int at, int y1, int y2, int type) : at(at), y1(y1), y2(y2), type(type) {}

    bool operator < (const Event &t) const {
        if (at != t.at) return at < t.at;
        return type < t.type;
    }
};

vector<int> y;

namespace SegmentTree {
    const int MAXN = 1 << 20;
    long long sum[MAXN];
    int add[MAXN];
    
    void clear() {
        memset(sum, 0, sizeof sum);
        memset(add, 0, sizeof add);
    }
    
    void refresh(int u, int l, int r) {
        sum[u] = 0;
        if (add[u] > 0) {
            sum[u] = y[r + 1] - y[l];
        } else {
            if (l < r) sum[u] = sum[2*u+1] + sum[2*u+2];
        }
    }
    
    void update(int u, int l, int r,  int p, int q, int what) {
        if (q < l or r < p) return; // outside
        p = max(p, l);
        q = min(q, r);
        if (l == p and q == r) {
            add[u] += what;
        } else {
            int m = (l + r) / 2;
            update(2*u+1, l, m,  p, q, what);
            update(2*u+2, m+1, r, p, q, what);
        }
        refresh(u, l, r);
    }
};

// Returns the area covered by the given rectangles.
// All z values are ignored. This returns the area of
// the rectangles formed by the x and y values on the
// z = 0 plane.
long long area(const vector<Box> &rectangles) {
    y.clear();
    for (int i = 0; i < rectangles.size(); ++i) {
        y.push_back(rectangles[i].y1);
        y.push_back(rectangles[i].y2);
    }
    sort(y.begin(), y.end());
    y.resize(unique(y.begin(), y.end()) - y.begin());
    
    vector<Event> events;
    for (int i = 0; i < rectangles.size(); ++i) {
        events.push_back( Event(rectangles[i].x1, rectangles[i].y1, rectangles[i].y2, Event::IN) );
        events.push_back( Event(rectangles[i].x2, rectangles[i].y1, rectangles[i].y2, Event::OUT) );
    }
    sort(events.begin(), events.end());

    SegmentTree::clear();
    
    long long previous_length = 0, ans = 0;
    for (int i = 0; i < events.size(); ++i) {
        if (i > 0) {
            int advanced = events[i].at - events[i - 1].at;
            ans += previous_length * advanced;
        }
        
        int p = lower_bound(y.begin(), y.end(), events[i].y1) - y.begin();
        int q = lower_bound(y.begin(), y.end(), events[i].y2) - y.begin();
        assert(p < q);
        
        if (events[i].type == Event::IN) {
            SegmentTree::update(0, 0, y.size() - 2,  p, q-1, +1);
        } else {
            SegmentTree::update(0, 0, y.size() - 2,  p, q-1, -1);
        }
        previous_length = SegmentTree::sum[0]; // update to new value
    }
    return ans;
}



class PaperAndPaint {
  public:

  vector<Rect> all;
  vector<ll> xs;

  ll doit() {
      vector<Box> r;
      for (int i = 0; i < all.size(); ++i) {
          r.push_back( Box(all[i].x1, all[i].x2, all[i].y1, all[i].y2) );
      }
      return area(r);
  }

  long long computeArea(int width, int height, vector <int> xfold, vector <int> cnt, vector <int> x1, vector <int> y1, vector <int> x2, vector <int> y2) {
    all.clear();
    xs.clear();

    int n = xfold.size();
    FOR(i,n) {
      ll incy = height / (cnt[i]+1);
      FOR(j,cnt[i]+1) {
        ll y0 = j * incy;
        bool flipy = j%2;

        FOR(flipx,2) {
    ll m = 1-2*flipx;
    ll x0 = xfold[i];

    ll xa = min((ll)width,max(0LL, x0 + m*x1[i]));
    ll xb = min((ll)width,max(0LL, x0 + m*x2[i]));
    if (xb<xa) swap(xa,xb);

    ll ya,yb;
    if (flipy) {
      ya = y0+incy-y2[i];
      yb = y0+incy-y1[i];
    } else {
      ya = y0+y1[i];
      yb = y0+y2[i];
    }
    assert(ya<=yb);

    all.PB(Rect(xa,ya,xb,yb));
        }
      }
    }

    FORALL(i,all) xs.PB(i->x1), xs.PB(i->x2);
    sort(BEND(xs));
    xs.resize(unique(BEND(xs)) - xs.begin());

    return ll(width)*height - doit();
  }


  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 5; int Arg1 = 6; int Arr2[] = {2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {2}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {1}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {1}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {3}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); int Arr7[] = {2}; vector <int> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); long long Arg8 = 21LL; verify_case(0, Arg8, computeArea(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 4; int Arr2[] = {0, 0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1, 0}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {0, 0}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {1, 1}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {2, 1}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); int Arr7[] = {2, 4}; vector <int> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); long long Arg8 = 3LL; verify_case(1, Arg8, computeArea(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)); }
	void test_case_2() { int Arg0 = 6; int Arg1 = 6; int Arr2[] = {2, 5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1, 2}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {1, 2}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {2, 0}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {3, 4}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); int Arr7[] = {3, 2}; vector <int> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); long long Arg8 = 18LL; verify_case(2, Arg8, computeArea(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)); }
	void test_case_3() { int Arg0 = 21; int Arg1 = 30; int Arr2[] = {3,21,7,11,13}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {4,14,9,5,4}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {4,0,2,5,9}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {2,0,1,2,3}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {7,19,6,11,12}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); int Arr7[] = {5,2,2,4,5}; vector <int> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); long long Arg8 = 27LL; verify_case(3, Arg8, computeArea(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)); }
	void test_case_4() { int Arg0 = 30; int Arg1 = 42; int Arr2[] = {16, 24, 25, 21, 4}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {5, 1, 6, 13, 20}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {3, 1, 5, 8, 9}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {0, 1, 0, 0, 1}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {14, 22, 12, 18, 13}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); int Arr7[] = {2, 15, 1, 1, 2}; vector <int> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); long long Arg8 = 336LL; verify_case(4, Arg8, computeArea(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)); }
	void test_case_5() { int Arg0 = 26; int Arg1 = 60; int Arr2[] = {17, 17, 24, 4, 21}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {4, 1, 11, 0, 2}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {9, 1, 20, 18, 7}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {1, 3, 0, 45, 12}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {13, 4, 23, 19, 13}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); int Arr7[] = {3, 14, 1, 46, 14}; vector <int> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); long long Arg8 = 1319LL; verify_case(5, Arg8, computeArea(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)); }
	void test_case_6() { int Arg0 = 17; int Arg1 = 3; int Arr2[] = {17, 2, 10, 2, 10, 13}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {2, 0, 0, 2, 0, 0}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {7, 6, 4, 11, 0, 5}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {0, 0, 1, 0, 1, 1}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {12, 10, 6, 12, 4, 12}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); int Arr7[] = {1, 3, 2, 1, 2, 2}; vector <int> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); long long Arg8 = 20LL; verify_case(6, Arg8, computeArea(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)); }

// END CUT HERE

};

 
// BEGIN CUT HERE
int main(){
    PaperAndPaint test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
