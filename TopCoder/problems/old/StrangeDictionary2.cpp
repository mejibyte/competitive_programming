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

class StrangeDictionary2 {
  public:
  vector <double> getProbabilities(vector <string> words);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <double> &Expected, const vector <double> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"hardesttestever"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arr1[] = {1.0 }; vector <double> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, getProbabilities(Arg0)); }
	void test_case_1() { string Arr0[] = {"ab", "ba"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arr1[] = {0.5, 0.5 }; vector <double> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, getProbabilities(Arg0)); }
	void test_case_2() { string Arr0[] = {"aza", "aab", "bba"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arr1[] = {0.3333333333333333, 0.5, 0.16666666666666666 }; vector <double> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, getProbabilities(Arg0)); }
	void test_case_3() { string Arr0[] = {"abababab", "babababa", "acacacac", "cacacaca", "bcbcbcbc", "cbcbcbcb"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arr1[] = {0.5, 0.5, 0.0, 0.0, 0.0, 0.0 }; vector <double> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, getProbabilities(Arg0)); }

// END CUT HERE

};




// This problem is pretty much like The Hunger Games, except that instead of people killing each other we have strings.





int n, length;
long double dp[16][1 << 16]; // dp[i][mask] = Probability that word i will win if the remaining candidates are the words in mask.
bool been[1 << 16];

vector<string> words;

void solve(int mask) {
    if (__builtin_popcount(mask) == 1) {
        // base case. Only one string remains, so she definitely wins.
        for (int i = 0; i < n; ++i) {
            dp[i][mask] = (mask & 1 << i) ? 1.0 : 0.0;
        }
        return;
    }
    
    if (been[mask]) return;
    
    for (int i = 0; i < n; ++i) {
        dp[i][mask] = 0.0;
    }
    
    int options = 0;
    for (int pos = 0; pos < length; ++pos) {
        // let's try to pick this column next. What opponents would remain?
        int min_char = 'z' + 1;
        for (int i = 0; i < n; ++i) if (mask & 1 << i) {
            min_char = min(min_char, (int)words[i][pos]);
        }
        
        int survivors = 0;
        for (int i = 0; i < n; ++i) if (mask & 1 << i) {
            if (words[i][pos] == min_char) {
                survivors |= 1 << i;
            }
        }
        assert(survivors <= mask);
        
        if (survivors < mask) {
            options++;
            solve(survivors);
            for (int i = 0; i < n; ++i) {
                dp[i][mask] += dp[i][survivors];
            }
        }
    }
    assert(options > 0);
    for (int i = 0; i < n; ++i) {
        dp[i][mask] /= options;
    }
    
    been[mask] = true;
}

vector <double> StrangeDictionary2::getProbabilities(vector <string> words) {
    n = words.size();
    length = words[0].size();
    ::words = words;
    memset(been, false, sizeof been);
    
    solve((1 << n) - 1);
    
    vector<double> ans;
    for (int i = 0; i < n; ++i) ans.push_back( dp[i][(1 << n) - 1] );
    return ans;
}

// BEGIN CUT HERE
int main(){
    StrangeDictionary2 test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
