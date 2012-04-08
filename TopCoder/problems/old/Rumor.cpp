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

class Rumor {
  public:
  int getMinimum(string knowledge, vector <string> graph);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "YNN"; string Arr1[] = {"NYN"
,"NNY"
,"NNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(0, Arg2, getMinimum(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "YNNY"; string Arr1[] = {"NYYN"
,"YNNY"
,"YNNY"
,"NYYN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(1, Arg2, getMinimum(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "YYYY"; string Arr1[] = {"NYNN"
,"YNYN"
,"NYNY"
,"NNYN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(2, Arg2, getMinimum(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "YYYYYN"; string Arr1[] = {"NYYYYN"
,"YNYYYN"
,"YYNYYN"
,"YYYNYN"
,"YYYYNN"
,"NNNNNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(3, Arg2, getMinimum(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "NNNY"; string Arr1[] = {"NNNN"
,"YNNN"
,"YNNN"
,"NYYN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(4, Arg2, getMinimum(Arg0, Arg1)); }
	void test_case_5() { string Arg0 =  "NNNNNNNYYY"; string Arr1[] = {"NYNNYNNYNN"
,"NNYNYNNNNY"
,"YYNNNYNNNN"
,"YNNNYNYNNN"
,"NNYNNYNNYN"
,"NNNNYNNNYY"
,"NYNYNYNNNN"
,"NNNNNNYNYY"
,"NNNYNNNYNY"
,"NYYNNNNYNN"}
; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(5, Arg2, getMinimum(Arg0, Arg1)); }

// END CUT HERE

};

string beginning;
vector <string> g;
vector<int> next;

int solve(int first) {
    int n = beginning.size();
    
    int knowA = 0, knowB = 0;
    for (int i = 0; i < n; ++i) {
        if (beginning[i] == 'Y') {
            knowA |= 1 << i;
            knowB |= 1 << i;
        }
    }
    
    int toldA = 0, toldB = 0;
    for (int t = 0; ; t++) {
        if (knowA == (1 << n) - 1 and knowB == (1 << n) - 1) return t;
        int willKnowA = knowA;
        int willKnowB = knowB;
        
        for (int i = 0; i < n; ++i) {
            if (first & (1 << i)) { //tell B first
                if      ( (knowB & 1 << i) && !(toldB & 1 << i) ){ toldB |= 1 << i; willKnowB |= next[i]; }
                else if ( (knowA & 1 << i) && !(toldA & 1 << i) ){ toldA |= 1 << i; willKnowA |= next[i]; }                
            } else { // tell A first
                if      ( (knowA & 1 << i) && !(toldA & 1 << i) ){ toldA |= 1 << i; willKnowA |= next[i]; }                     
                else if ( (knowB & 1 << i) && !(toldB & 1 << i) ){ toldB |= 1 << i; willKnowB |= next[i]; }                
            }
        }

        if (willKnowA == knowA and willKnowB == knowB) return 1 << 30;
        knowA = willKnowA;
        knowB = willKnowB;
    }
}

int Rumor::getMinimum(const string knowledge, const vector <string> graph) {
    beginning = knowledge;
    g = graph;
    int n = knowledge.size();
    next.assign(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (g[i][j] == 'Y') {
                next[i] |= 1 << j;
            }
        }
    }
    
    int ans = 1 << 30;
    for (int first = 0; first < (1 << n); ++first) {
        ans = min(ans, solve(first));
    }
    if (ans >= 1 << 30) return -1;
    return ans;
}

// BEGIN CUT HERE
int main(){
    Rumor ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
