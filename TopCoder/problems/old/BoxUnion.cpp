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

class BoxUnion {
  public:
  int area(vector <string> rectangles);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = { "200 300 203 304" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 12; verify_case(0, Arg1, area(Arg0)); }
	void test_case_1() { string Arr0[] = { "0 0 10 10",
  "20 20 30 30" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 200; verify_case(1, Arg1, area(Arg0)); }
	void test_case_2() { string Arr0[] = { "0 500 20000 501",
  "500 0 501 20000" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 39999; verify_case(2, Arg1, area(Arg0)); }
	void test_case_3() { string Arr0[] = { "4 6 18 24",
  "7 2 12 19",
  "0 0 100 100" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10000; verify_case(3, Arg1, area(Arg0)); }
	void test_case_4() { string Arr0[] = { "1 3 5 6",
  "3 1 7 5",
  "4 4 9 7" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 35; verify_case(4, Arg1, area(Arg0)); }
	void test_case_5() { string Arr0[] = { "0 0 20000 20000",
  "0 0 20000 20000",
  "0 0 20000 20000" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 400000000; verify_case(5, Arg1, area(Arg0)); }

// END CUT HERE

};

// O(n log n) implementation for rectangle union area.
// I know this is an overkill for this problem.

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
    const int MAXN = 1 << 10;
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
long long get_area(const vector<Box> &rectangles) {
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


int BoxUnion::area(vector <string> rectangles) {
    vector<Box> r;
    for (int i = 0; i < rectangles.size(); ++i) {
        int x1, y1, x2, y2;
        stringstream sin(rectangles[i]);
        sin >> x1 >> y1 >> x2 >> y2;
        r.push_back(Box(x1, x2, y1, y2));
    }
    return get_area(r);
}

// BEGIN CUT HERE
int main(){
    BoxUnion test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
