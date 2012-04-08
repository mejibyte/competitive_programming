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

class MultiplesWithLimit {
  public:
  string minMultiples(int N, vector <int> forbiddenDigits);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 8; int Arr1[] = {2,3,4,5,6,7,8,9}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "1000"; verify_case(0, Arg2, minMultiples(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 9; int Arr1[] = {1,3,4,5,6,7,8,9}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "222...222(9 digits)"; verify_case(1, Arg2, minMultiples(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 524; int Arr1[] = {5,2,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "3668"; verify_case(2, Arg2, minMultiples(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 10000; int Arr1[] = {0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "IMPOSSIBLE"; verify_case(3, Arg2, minMultiples(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 1; int Arr1[] = {0,1,2,3,4,5,6,7,8,9}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "IMPOSSIBLE"; verify_case(4, Arg2, minMultiples(Arg0, Arg1)); }

// END CUT HERE

};

string format(string digits, int len) {
    if (len < 9) return digits;
    string trimmed = digits.substr(0, 3) + "..." + digits.substr(digits.size() - 3, 3);
    
    stringstream t; t << len;
    string size; t >> size;
    
    return trimmed + "("+size+" digits)";
}

string MultiplesWithLimit::minMultiples(int N, vector <int> forbiddenDigits) {
  vector<bool> valid(10, true);
  foreach(x, forbiddenDigits) valid[*x] = false;

  vector<int> dist(N + 1, -1);
  vector<string> path(N + 1, "");

  queue<int> q;
  for(int i = 1; i < 10; ++i) {
      if (valid[i] and dist[i % N] == -1) {
          dist[i % N] = 1;
          path[i % N] += char('0' + i);
          q.push(i % N);
      }
  }
  
  while (q.size() > 0) {
      int cur = q.front(); q.pop();
      if (cur == 0) return format(path[0], dist[0]);
      
      for (int i = 0; i < 10; ++i) {
          if (!valid[i]) continue;
          
          int next = (cur * 10 + i) % N;
          if (dist[next] != -1) continue;
          
          dist[next] = dist[cur] + 1;
          path[next] = path[cur] + char('0' + i);
          if (path[next].size() > 9) path[next] = path[next].substr(0, 3) + path[next].substr(path[next].size() - 3, 3);
          q.push(next);
      }
  }
  
  return "IMPOSSIBLE";
}

// BEGIN CUT HERE
int main(){
    MultiplesWithLimit ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
