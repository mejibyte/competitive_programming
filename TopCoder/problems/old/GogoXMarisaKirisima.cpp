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

class GogoXMarisaKirisima {
  public:
  int solve(vector <string> choices);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"NYN"
,"YNY"
,"NNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(0, Arg1, solve(Arg0)); }
	void test_case_1() { string Arr0[] = {"NNY"
,"YNY"
,"YNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(1, Arg1, solve(Arg0)); }
	void test_case_2() { string Arr0[] = {"NN"
,"NN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, solve(Arg0)); }
	void test_case_3() { string Arr0[] = {"NYYY"
,"NNNY"
,"NNNY"
,"NNNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(3, Arg1, solve(Arg0)); }

// END CUT HERE

};


#include <bitset>

const int MAXN = 55;
bitset<MAXN> reach, end;
vector<string> choices;
bool used[MAXN][MAXN];

void forward(int u) {
    if (reach[u]) return;
    reach[u] = true;
    for (int v = 0; v < choices.size(); ++v) {
        if (choices[u][v] == 'Y' and !reach[v]) {
            used[u][v] = true;
            forward(v);
        }
    }
}

void backward(int u) {
    if (end[u]) return;
    end[u] = true;
    for (int v = 0; v < choices.size(); ++v) {
        if (choices[v][u] == 'Y') backward(v);
    }
}
 
int GogoXMarisaKirisima::solve(vector <string> c) {
    reach.reset(), end.reset();
    memset(used, 0, sizeof used);
    
    choices = c;
    int n = choices.size();
    
    forward(0);
    if (!reach[n - 1]) return 0;
    backward(n - 1);
    
    int ans = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j and choices[i][j] == 'Y' and !used[i][j] and reach[i] and end[j]) {
                ans++;
            }
        }
    }
    return ans;
}

// BEGIN CUT HERE
int main(){
    GogoXMarisaKirisima ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
