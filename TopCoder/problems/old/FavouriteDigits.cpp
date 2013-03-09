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

class FavouriteDigits {
  public:
  long long findNext(long long N, int digit1, int count1, int digit2, int count2);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 47LL; int Arg1 = 1; int Arg2 = 0; int Arg3 = 2; int Arg4 = 0; long long Arg5 = 47LL; verify_case(0, Arg5, findNext(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { long long Arg0 = 47LL; int Arg1 = 5; int Arg2 = 0; int Arg3 = 9; int Arg4 = 1; long long Arg5 = 49LL; verify_case(1, Arg5, findNext(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { long long Arg0 = 47LL; int Arg1 = 5; int Arg2 = 0; int Arg3 = 3; int Arg4 = 1; long long Arg5 = 53LL; verify_case(2, Arg5, findNext(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { long long Arg0 = 47LL; int Arg1 = 2; int Arg2 = 1; int Arg3 = 0; int Arg4 = 2; long long Arg5 = 200LL; verify_case(3, Arg5, findNext(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_4() { long long Arg0 = 123456789012345LL; int Arg1 = 1; int Arg2 = 2; int Arg3 = 2; int Arg4 = 4; long long Arg5 = 123456789012422LL; verify_case(4, Arg5, findNext(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_5() { long long Arg0 = 92LL; int Arg1 = 1; int Arg2 = 1; int Arg3 = 0; int Arg4 = 0; long long Arg5 = 100LL; verify_case(5, Arg5, findNext(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE

};


long long memo[55][2][55][55];

const int SHIFT = 25;

int d1, d2;
vector<int> num;

unsigned long long f(int i, bool m, int c1, int c2, unsigned long long built = 0) {
  assert(0 <= c1 + SHIFT and c1 + SHIFT < 55);
  assert(0 <= c2 + SHIFT and c2 + SHIFT < 55);
  assert(0 <= i and i < 55);
  if (memo[i][m][c1 + SHIFT][c2 + SHIFT] != -1) return memo[i][m][c1 + SHIFT][c2 + SHIFT];
    
  if (i < num.size()) { // inside
    int lowest = m ? 0 : num[i];
    unsigned long long best = ULONG_LONG_MAX;
    for (int place = lowest; place <= 9; ++place) {
      best = min(best,
                 f(i + 1, m or place > num[i], c1 - (place == d1), c2 - (place == d2), built * 10 + place));
    }
    return memo[i][m][c1 + SHIFT][c2 + SHIFT] = best;
  } else { // outside
    // Place the smaller digit first, but check for overflow.
    while (c1 > 0) {
      built *= 10, built += d1, c1--;
      if ((long long)built < 0) return LONG_LONG_MAX;
    }
    while (c2 > 0) {
      built *= 10, built += d2, c2--;
      if ((long long)built < 0) return LONG_LONG_MAX;
    }
    return built;
  }
}

long long FavouriteDigits::findNext(long long N, int digit1, int count1, int digit2, int count2) {
  if (digit2 < digit1) {
    swap(digit2, digit1);
    swap(count2, count1);
  }
  
  d1 = digit1;
  d2 = digit2;
  assert(digit1 < digit2);
  memset(memo, -1, sizeof memo);
  num.clear();
  while (N > 0) num.push_back(N % 10), N /= 10;
  reverse(num.begin(), num.end());
  
  long long ans = f(0, false, count1, count2);
  for (int first = 1; first <= 9; ++first) {
    memset(memo, -1, sizeof memo);
    ans = min(ans, (long long)f(0, true, count1 - (first == d1), count2 - (first == d2), first));
  }
  return ans;
}

// BEGIN CUT HERE
int main(){
    FavouriteDigits test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
