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

class RoughStrings {
  public:
  int minRoughness(string s, int n);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "aaaaabbc"; int Arg1 = 1; int Arg2 = 3; verify_case(0, Arg2, minRoughness(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "aaaabbbbc"; int Arg1 = 5; int Arg2 = 0; verify_case(1, Arg2, minRoughness(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "veryeviltestcase"; int Arg1 = 1; int Arg2 = 2; verify_case(2, Arg2, minRoughness(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "gggggggooooooodddddddllllllluuuuuuuccckkk"; int Arg1 = 5; int Arg2 = 3; verify_case(3, Arg2, minRoughness(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz"; int Arg1 = 17; int Arg2 = 0; verify_case(4, Arg2, minRoughness(Arg0, Arg1)); }
	void test_case_5() { string Arg0 = "bbbccca"; int Arg1 = 2; int Arg2 = 0; verify_case(5, Arg2, minRoughness(Arg0, Arg1)); }

// END CUT HERE

};

int RoughStrings::minRoughness(string s, int n) {
  map<char, int> times;
  for (int i = 0; i < s.size(); ++i) times[s[i]]++;
  vector<int> v;
  foreach(t, times) v.push_back(t->second);
  sort(v.begin(), v.end());
  int ans = (1 << 30);
  for (int least = 1; least <= 50; ++least) {
    int need = 0;
    vector<int> alive;
    for (int i = 0; i < v.size(); ++i) {
      if (v[i] < least) need += v[i];
      else alive.push_back(v[i]);
    }
    if (need > n) continue;
    assert(alive.size() > 0);
    assert(alive[0] >= least);
    need += (alive[0] - least);
    alive[0] = least;
    if (need > n) continue;
    while (need < n) {
      if (alive.back() == least) break;
      alive.back()--;
      need++;
      sort(alive.begin(), alive.end());
    }
    ans = min(ans, alive.back() - alive[0]);
  }
  return ans;
}

// BEGIN CUT HERE
int main(){
    RoughStrings test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
