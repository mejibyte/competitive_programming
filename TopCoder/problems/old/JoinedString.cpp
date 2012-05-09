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

class JoinedString {
  public:
  string joinWords(vector <string> words);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"BAB", "ABA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "ABAB"; verify_case(0, Arg1, joinWords(Arg0)); }
	void test_case_1() { string Arr0[] = {"ABABA", "AKAKA", "AKABAS", "ABAKA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "ABABAKAKABAS"; verify_case(1, Arg1, joinWords(Arg0)); }
	void test_case_2() { string Arr0[] = {"AAA","BBB", "CCC", "ABC", "BCA", "CAB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "AAABBBCABCCC"; verify_case(2, Arg1, joinWords(Arg0)); }
	void test_case_3() { string Arr0[] = {"OFG", "SDOFGJTILM", "KBWNF", "YAAPO", "AWX", "VSEAWX", "DOFGJTIL", "YAA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "KBWNFSDOFGJTILMVSEAWXYAAPO"; verify_case(3, Arg1, joinWords(Arg0)); }
	void test_case_4() { string Arr0[] = {"NVCSKFLNVS", "HUFSPMRI", "FLNV", "KMQD", "RPJK", "NVSQORP", "UFSPMR", "AIHUFSPMRI"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "AIHUFSPMRINVCSKFLNVSQORPJKMQD"; verify_case(4, Arg1, joinWords(Arg0)); }
	void test_case_5() { string Arr0[] = {"STRING", "RING"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "STRING"; verify_case(5, Arg1, joinWords(Arg0)); }

// END CUT HERE

};

string JoinedString::joinWords(vector <string> words) {
  
}

// BEGIN CUT HERE
int main(){
    JoinedString test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
