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

class PointErasing {
public:
    vector <int> getOutcomes(vector <int> y);


// BEGIN CUT HERE
public:
    void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); }
private:
    template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
    void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
    void test_case_0() { int Arr0[] = { 1, 2, 1, 1, 0, 4, 3 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4, 6 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, getOutcomes(Arg0)); }
    void test_case_1() { int Arr0[] = { 0, 0, 4, 4, 8, 8, 4, 4 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {6 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, getOutcomes(Arg0)); }
    void test_case_2() { int Arr0[] = { 522 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, getOutcomes(Arg0)); }
    void test_case_3() { int Arr0[] = { 19, 19, 19, 19, 19, 19 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {6 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, getOutcomes(Arg0)); }
    void test_case_4() { int Arr0[] = { 0, 1, 2, 3, 4 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, getOutcomes(Arg0)); }
    void test_case_5() { int Arr0[] = { 7, 8, 8, 7, 6, 7, 9, 3, 5, 0 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3, 4, 5 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(5, Arg1, getOutcomes(Arg0)); }
    void test_case_6() { int Arr0[] = { 3, 2, 3, 3, 4, 3, 4, 3, 3, 1, 5, 3 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4, 5, 6, 7, 9 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(6, Arg1, getOutcomes(Arg0)); }
    void test_case_7() { int Arr0[] = { 5, 5, 4, 4, 5, 8, 5, 5, 5, 5, 5, 9, 2, 0, 9, 4, 5, 5, 3, 4, 4, 4, 4, 7, 4 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {6, 7, 8, 10, 11, 12, 13, 15, 16, 17 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(7, Arg1, getOutcomes(Arg0)); }

// END CUT HERE

};

bool dp[55][55];

vector<int> solve(const vector<int> &a) {
    int n = a.size();
    
    memset(dp, 0, sizeof dp);
    dp[n][0] = true;
    
    for (int i = n - 1; i >= 0; --i) {
        for (int j = 0; j <= n; ++j) {
            if (a[i] == 0) {
                if (j - 1 >= 0) dp[i][j] = dp[i + 1][j - 1];
            } else {
                dp[i][j] |= dp[i + 1][j];
                for (int k = i; k < n; ++k) {
                    if (a[i] * a[k] < 0) {
                        dp[i][j] |= dp[k][j];
                    }
                }
            }
        }
    }
    
    vector<int> ans;
    for (int j = 0; j <= n; ++j) {
        if (dp[0][j]) ans.push_back(j);
    }
    return ans;
}


vector <int> PointErasing::getOutcomes(vector <int> y) { 
    int n = y.size(); 
    int small = *min_element(y.begin(), y.end());
    int big = *max_element(y.begin(), y.end());

    vector<int> a, b;
    for (int i = 0; y[i] != small and y[i] != big; ++i) {
        int d = y[i] - y[0];
        a.push_back(d);
        if (a.back() != 0) a.back() /= abs(a.back());
    }
    a.push_back(1); a.push_back(-1);
    
    for (int i = n - 1; y[i] != small and y[i] != big; --i) {
        int d = y[i] - y[n - 1];
        b.push_back(d);
        if (b.back() != 0) b.back() /= abs(b.back());
    }
    b.push_back(1); b.push_back(-1);

    a = solve(a);
    b = solve(b);

    set<int> ans;

    int constant = 0;
    for (int i = 0; i < n; ++i) {
        if (y[i] == small or y[i] == big) constant++;
    }

    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < b.size(); ++j) {
            ans.insert(constant + a[i] + b[j]);
        }
    }
    
    vector<int> ret;
    foreach(i, ans) ret.push_back(*i);
    return ret;
}

// BEGIN CUT HERE
int main(){
    PointErasing ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
