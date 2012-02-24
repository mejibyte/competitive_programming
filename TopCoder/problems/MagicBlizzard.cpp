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

class MagicBlizzard {
  public:
  double expectation(vector <int> range, vector <int> amount);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 2.2222222222222223; verify_case(0, Arg2, expectation(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 3.666666666666667; verify_case(1, Arg2, expectation(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {5,2,6,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,2,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 8.46525111252384; verify_case(2, Arg2, expectation(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {7,11,2,13,3,19,5,17}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {16,8,4,15,12,9,10,6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 98.55659436211914; verify_case(3, Arg2, expectation(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {0,0,0,0,0,0,0,0,0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10000,10000,10000,10000,10000,10000,10000,10000,10000,10000}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 1.0E10; verify_case(4, Arg2, expectation(Arg0, Arg1)); }

// END CUT HERE

};

vector<int> R, A;

double inside(int count, int k, int r) {
    if (A[k] < count) return 0.0;
    
    if (R[k] < r) { // outside
        return count == 0 ? 1.0 : 0.0;
    }
    
    int size = R[k] + 1;
    size *= size;
    
    return pow( 1.0 / size, count );
}

double f(int x, int k, int r) {
    printf("f(x=%d, k=%d, r=%d)\n", x, k, r);
    if (k < 0) {
        if (x == 0) return 1.0;
        return 0.0;
    }
    
    double ans = 0.0;
    for (int take = 0; take <= x; ++take) {
        printf("inside(take = %d, k = %d, r = %d) = %lf\n", take, k, r, inside(take, k, r));
        ans += f(x - take, k - 1, r) * inside(take, k, r);
    }
    return ans;
}

double probability(int x, int r) {
    return f(x, A.size() - 1, r);
}

double MagicBlizzard::expectation(vector <int> range, vector <int> amount) {
    R = range, A = amount;
    vector< int > targets = range;
    sort(targets.begin(), targets.end());
    targets.resize( unique(targets.begin(), targets.end()) - targets.begin() );
    
    int allBalls = accumulate(amount.begin(), amount.end(), 0);
    
    double ans = 0.0;
    for (int k = 0; k < targets.size(); ++k) {
        int r = targets[k] + 1;
        int size = r * r;
        if (k > 0) size -= (targets[k - 1] + 1) * (targets[k - 1] + 1);
        for (int x = 0; x <= allBalls; ++x) {
            D(probability(x, r));
            D(x * x);
            D(size);
            ans += x * x * size * probability(x, r);
        }
    }
    return ans;
}

// BEGIN CUT HERE
int main(){
    MagicBlizzard ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
