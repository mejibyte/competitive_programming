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

class ThreePoints {
  public:
  long long countColoring(int N, int xzero, int xmul, int xadd, int xmod, int yzero, int ymul, int yadd, int ymod);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 9; int Arg1 = 3; int Arg2 = 8; int Arg3 = 6; int Arg4 = 11; int Arg5 = 5; int Arg6 = 7; int Arg7 = 8; int Arg8 = 11; long long Arg9 = 8LL; verify_case(0, Arg9, countColoring(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
	void test_case_1() { int Arg0 = 4; int Arg1 = 9; int Arg2 = 6; int Arg3 = 8; int Arg4 = 10; int Arg5 = 4; int Arg6 = 8; int Arg7 = 5; int Arg8 = 10; long long Arg9 = 2LL; verify_case(1, Arg9, countColoring(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
	void test_case_2() { int Arg0 = 20; int Arg1 = 30; int Arg2 = 3; int Arg3 = 71; int Arg4 = 100; int Arg5 = 78; int Arg6 = 12; int Arg7 = 50; int Arg8 = 100; long long Arg9 = 263LL; verify_case(2, Arg9, countColoring(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
	void test_case_3() { int Arg0 = 300000; int Arg1 = 99097861; int Arg2 = 102766912; int Arg3 = 95284952; int Arg4 = 123456789; int Arg5 = 443104491; int Arg6 = 971853214; int Arg7 = 569775557; int Arg8 = 987654321; long long Arg9 = 749410681185726LL; verify_case(3, Arg9, countColoring(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }

// END CUT HERE

};

const int MAXN = 300005;

struct FenwickTree {
  long long data[MAXN+1];

  void clear() {
    memset(data, 0, sizeof data);
  }
  
  long long get(int at) const {
    long long ans = 0;
    for (at++; at > 0; at -= at & -at) {
      ans += data[at];
    }
    return ans;
  }
  
  void add(int at, long long what) {
    for (at++; at < MAXN; at += at & -at) {
      data[at] += what;
    }
  }
  
  long long get(int from, int to) const {
    long long ans = get(to);
    if (from - 1 >= 0) ans -= get(from - 1);
    return ans;
  }
};

FenwickTree at, pairs;

long long ThreePoints::countColoring(int N, int xzero, int xmul, int xadd, int xmod, int yzero, int ymul, int yadd, int ymod) {
    vector<pair<int, int> > points(N);
    points[0].first = xzero;
    points[0].second = yzero;
    for (int i = 1; i < N; ++i) {
      points[i].first = (1LL * points[i - 1].first * xmul + xadd) % xmod;
      points[i].second = (1LL * points[i - 1].second * ymul + yadd) % ymod;
    }
    sort(points.begin(), points.end());
    vector<int> y(N), rank(N);
    for (int i = 0; i < N; ++i) {
      y[i] = rank[i] = points[i].second;
    }
    sort(rank.begin(), rank.end());
    for (int i = 0; i < N; ++i) {
      y[i] = lower_bound(rank.begin(), rank.end(), y[i]) - rank.begin();
    }
    
    at.clear();
    pairs.clear();
    
    long long ans = 0;
    for (int i = N - 1; i >= 0; --i) {
      long long t = at.get(y[i] + 1, MAXN - 1);
      t = t * (t - 1) / 2;
      t -= pairs.get(y[i] + 1, MAXN - 1);
      ans += t;
      at.add(y[i], +1);
      pairs.add(y[i], at.get(y[i] + 1, MAXN - 1));
    }
    return ans;
}

// BEGIN CUT HERE
int main(){
    ThreePoints test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
