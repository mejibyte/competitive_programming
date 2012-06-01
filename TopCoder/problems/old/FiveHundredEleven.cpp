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

class FiveHundredEleven {
  public:
  string theWinner(vector <int> cards);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {3, 5, 7, 9, 510}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "Fox Ciel"; verify_case(0, Arg1, theWinner(Arg0)); }
	void test_case_1() { int Arr0[] = {0, 0, 0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "Toastman"; verify_case(1, Arg1, theWinner(Arg0)); }
	void test_case_2() { int Arr0[] = {511}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "Toastman"; verify_case(2, Arg1, theWinner(Arg0)); }
	void test_case_3() { int Arr0[] = {5, 58, 192, 256}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "Fox Ciel"; verify_case(3, Arg1, theWinner(Arg0)); }

// END CUT HERE

};

vector<int> c;

int memo[512][55];

bool can_win(int mask, int played) {
    if (mask == 511) return true;
    
    int &ans = memo[mask][played];
    if (ans != -1) return ans;
    ans = false;
    
    int stay = 0;
    for (int k = 0; k < c.size(); ++k) {
        if ((mask | c[k]) == mask) stay++;
    }
    
    if (played < stay and !can_win(mask, played + 1)) return ans = true;
    for (int k = 0; k < c.size(); ++k) {
        if ((mask | c[k]) != mask) {
            if (!can_win(mask | c[k], played + 1)) return ans = true;
        }
    }
    
    return ans;
}

string FiveHundredEleven::theWinner(vector <int> cards) {
    c = cards;
    memset(memo, -1, sizeof memo);
    if (can_win(0, 0)) {
        return "Fox Ciel";
    } else {
        return "Toastman";
    }
}

// BEGIN CUT HERE
int main(){
    FiveHundredEleven test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
