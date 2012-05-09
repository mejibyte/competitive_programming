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

class ContextFreeGrammars {
  public:
  int countParsingTrees(vector <string> rules, char seed, string word);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"A ::= BD",
 "B ::= bB | b | Bb",
 "D ::= dD",
 "D ::= d"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); char Arg1 = 'A'; string Arg2 = "bdd"; int Arg3 = 1; verify_case(0, Arg3, countParsingTrees(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"A ::= BD",
 "B ::= bB | b | Bb",
 "D ::= dD",
 "D ::= d"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); char Arg1 = 'A'; string Arg2 = "bbd"; int Arg3 = 2; verify_case(1, Arg3, countParsingTrees(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"A ::= BD",
 "B ::= bB | b | Bb",
 "D ::= dD",
 "D ::= d"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); char Arg1 = 'A'; string Arg2 = "ddbb"; int Arg3 = 0; verify_case(2, Arg3, countParsingTrees(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"B ::= topcoder | topcoder",
 "B ::= topcoder"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); char Arg1 = 'B'; string Arg2 = "topcoder"; int Arg3 = 3; verify_case(3, Arg3, countParsingTrees(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arr0[] = {"A ::= BCD",
 "Z ::= z",
 "B ::= Cz | Dz | Zz",
 "C ::= Bz | Dz",
 "D ::= Cz | Bz"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); char Arg1 = 'X'; string Arg2 = "zzz"; int Arg3 = 0; verify_case(4, Arg3, countParsingTrees(Arg0, Arg1, Arg2)); }
	void test_case_5() { string Arr0[] = {"B ::= bB | bB | bB | bB | b" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); char Arg1 = 'B'; string Arg2 = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"; int Arg3 = -1; verify_case(5, Arg3, countParsingTrees(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

int ContextFreeGrammars::countParsingTrees(vector <string> rules, char seed, string word) {
  
}

// BEGIN CUT HERE
int main(){
    ContextFreeGrammars ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
