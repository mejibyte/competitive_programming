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

class CollectingPostmarks {
public:
  int amountOfMoney(vector <int> prices, vector <int> have, vector <int> values, int K);


// BEGIN CUT HERE
public:
  void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
private:
  template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
  void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
  void test_case_0() { int Arr0[] = {2,15}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2,21}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 13; int Arg4 = 15; verify_case(0, Arg4, amountOfMoney(Arg0, Arg1, Arg2, Arg3)); }
  void test_case_1() { int Arr0[] = {9,18,7,6,18}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {12,27,10,10,25}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 67; int Arg4 = 22; verify_case(1, Arg4, amountOfMoney(Arg0, Arg1, Arg2, Arg3)); }
  void test_case_2() { int Arr0[] = {14,14,12,6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3,2,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {19,23,20,7}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 10; int Arg4 = 0; verify_case(2, Arg4, amountOfMoney(Arg0, Arg1, Arg2, Arg3)); }
  void test_case_3() { int Arr0[] = {43,33,14,31,42,37,17,42,40,20}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {116,71,38,77,87,106,48,107,91,41}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 811; int Arg4 = -1; verify_case(3, Arg4, amountOfMoney(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

const int MAXN = 32;
int price[MAXN];
int have[MAXN];
int value[MAXN];

void generate(int i, int j, vector< pair<int, int> > &ans) {
  int n = j - i + 1;
  ans.push_back( make_pair(0, 0) );
  if (n <= 0) return;
  for (int s = 1; s < (1 << n); ++s) {
    int v = 0, p = 0;
    for (int k = 0; k < n; ++k) {
      if (s & (1 << k)) {
        v += value[k + i];
        p += price[k + i];
      }
    }
    ans.push_back( make_pair(v, p) );
  }
  sort(ans.begin(), ans.end());
}


int CollectingPostmarks::amountOfMoney(vector <int> prices, vector <int> _have, vector <int> values, int K) {
  int N = prices.size();
  for (int i = 0; i < _have.size(); ++i) {
    have[_have[i]] = true;
  }
  for (int i = 0; i < N; ++i) {
    price[i] = prices[i];
    value[i] = values[i];
  }

  int sum = 0;
  for (int i = 0; i < N; ++i) {
    sum += value[i];
  }

  if (sum < K) {
    return -1;
  }

  vector< pair<int, int> > A, B;
  generate(0, N / 2 - 1, A);
  generate(N / 2, N - 1, B);

  for (int i = B.size() - 2; i >= 0; --i) {
    B[i].second = min(B[i].second, B[i + 1].second);
  }
  for (int i = A.size() - 2; i >= 0; --i) {
    A[i].second = min(A[i].second, A[i + 1].second);
  }

  int ans = (1 << 30);
  for (int a = 0, b = B.size() - 1; a < A.size() and b >= 0; ) {
    if (A[a].first + B[b].first >= K) {
      ans = min(A[a].second + B[b].second, ans);
      b--;
    } else {
      a++;
    }
  }

  sum = 0;
  for (int i = 0; i < N; ++i) sum += have[i] * price[i];
  ans = max(0, ans - sum);
  return ans;
}

// BEGIN CUT HERE
int main(){
  CollectingPostmarks ___test;
  ___test.run_test(-1);
  return 0;
}
// END CUT HERE
