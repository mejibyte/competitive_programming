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

class SubFibonacci {
  public:
  int maxElements(vector <int> S);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {8, 1, 20, 3, 10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(0, Arg1, maxElements(Arg0)); }
	void test_case_1() { int Arr0[] = {19, 47, 50, 58, 77, 99}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(1, Arg1, maxElements(Arg0)); }
	void test_case_2() { int Arr0[] = {512}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(2, Arg1, maxElements(Arg0)); }
	void test_case_3() { int Arr0[] = {3, 5, 7, 10, 13, 15, 20, 90}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; verify_case(3, Arg1, maxElements(Arg0)); }
	void test_case_4() { int Arr0[] = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; verify_case(4, Arg1, maxElements(Arg0)); }

// END CUT HERE

};

vector<int> fib;

int best(const vector<int> &s) {
    if (s.size() <= 2) return s.size();
    int ans = 0;
    
    pair<int, int> which;
    
    for (int i = 0; i < s.size(); ++i) {
        for (int j = i + 1; j < s.size(); ++j) {
            int first = s[i], second = s[j];
            assert(first < second);
            
            for (int d = 0; d + 1 < fib.size() and fib[d] < second; ++d) {
                long long z = second - 1LL * first * fib[d];
                if (z < 0) break;
                
                if (z == 0 or z % fib[d + 1] != 0) continue;
                z /= fib[d + 1];
                
                assert(1 <= z and z <= second);
                                
                // Now generate the sequence and count how many are seen
                set<int> seen;
                if (binary_search(s.begin(), s.end(), first)) seen.insert(first);
                if (binary_search(s.begin(), s.end(), z) and first < z) seen.insert(z); 
                
                int a = first, b = z;
                
                while (a < s.back()) {
                    int c = a + b;
                    if (binary_search(s.begin(), s.end(), c)) seen.insert(c);
                    a = b;
                    b = c;
                }
                                
                assert(seen.size() >= 2);
                if (seen.size() > ans) {
                    ans = seen.size();
                    which = make_pair(first, z);
                }
            }
        }
    }
    assert(ans <= s.size());
    
    // printf("se logra asi: ");
    // printf("%d %d ", which.first, which.second); for (int a = which.first, b = which.second; a + b <= s.back(); ) {
    //     int c = a + b;
    //     printf("%d ", c);
    //     a = b;
    //     b = c;
    // } puts("");
    return ans;
}

int SubFibonacci::maxElements(vector <int> s) {
    fib.clear();
    fib.push_back(0);
    fib.push_back(1);
    while (fib.back() < 1000000000) {
        fib.push_back(fib.back() + fib[fib.size() - 2]);
    }

    sort(s.begin(), s.end());
    int ans = 0;
    for (int i = 0; i <= s.size(); ++i) {
        vector<int> left, right;
        for (int j = 0; j < s.size(); ++j) {
            (j < i ? left : right).push_back(s[j]);
        }
        int score = best(left) + best(right);
        if (score > ans) {
            // printf("left: "); foreach(l, left) printf("%d ", *l); puts("");
            // printf("right: "); foreach(l, right) printf("%d ", *l); puts("");            
            ans = score;
        }
    }
    return ans;
}

// BEGIN CUT HERE
int main(){
    SubFibonacci test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
