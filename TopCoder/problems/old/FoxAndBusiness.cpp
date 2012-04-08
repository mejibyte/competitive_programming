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
#define D(x) cout << #x " is " << (x) << endl

class FoxAndBusiness {
  public:
  double minimumCost(int K, int totalWork, vector <int> a, vector <int> p);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 10; int Arr2[] = {10}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {20}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); double Arg4 = 3800.0; verify_case(0, Arg4, minimumCost(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 100; int Arr2[] = {50, 60}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1000, 2000}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); double Arg4 = 107200.0; verify_case(1, Arg4, minimumCost(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 2; int Arg1 = 300; int Arr2[] = {10, 20, 47}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {15, 20, 98765}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); double Arg4 = 77500.0; verify_case(2, Arg4, minimumCost(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 4; int Arg1 = 1000; int Arr2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {20, 30, 40, 58, 60, 70, 80, 90, 100, 150}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); double Arg4 = 531764.705882353; verify_case(3, Arg4, minimumCost(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

double FoxAndBusiness::minimumCost(int K, int totalWork, vector <int> a, vector <int> p) {
    long double low = 0.0, high = 5e10;
    for (int e = 0; e < 500; ++e) {
        long double mid = (low + high) / 2;
        vector< long double > v;
        for (int i = 0; i < a.size(); ++i)
            v.push_back( a[i] * (1LL * totalWork * p[i] - mid) );
        sort(v.begin(), v.end());
        long double sum = 3600.0 * K * totalWork;
        for (int i = 0; i < K; ++i) sum += v[i];
        if (sum <= 0) high = mid;
        else low = mid;
    }
    return low;
}

// BEGIN CUT HERE
int main(){
    FoxAndBusiness ___test;
    ___test.run_test(-1);

    int k = 6;
    int w = 67912;
    
    int a[] = {7709, 3113, 92326, 69614, 95130, 45300, 12602, 238, 16845, 84775, 75506, 18193, 6120, 46282, 80855, 25739, 60296, 77976, 96432, 16787, 47275, 64070};
    int b[] = {62288, 56493, 36263, 88552, 47554, 32158, 2979, 90737, 37796, 59443, 46203, 65800, 94253, 66035, 43812, 34279, 88481, 54658, 62960, 73968, 40700, 95202};
    int n = sizeof(a) / sizeof(a[0]);
    vector<int> aa(a, a + n);
    vector<int> bb(b, b + n);
    
    D( ___test.minimumCost(k, w, aa, bb) );
    return 0;
}
// END CUT HERE
