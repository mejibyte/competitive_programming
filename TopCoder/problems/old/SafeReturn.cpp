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

class SafeReturn {
  public:
  int minRisk(int N, vector <string> streets);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; string Arr1[] = {"-234",
 "2---",
 "3---",
 "4---"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(0, Arg2, minRisk(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 2; string Arr1[] = {"-12",
 "1-1",
 "21-"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(1, Arg2, minRisk(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 3; string Arr1[] = {"-----7",
 "--1---",
 "-1-5--",
 "--5-1-",
 "---1-3",
 "7---3-"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(2, Arg2, minRisk(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 2; string Arr1[] = {"-11",
 "1-1",
 "11-"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(3, Arg2, minRisk(Arg0, Arg1)); }

// END CUT HERE

};

const int MAXN = 2 * 55;

int d[MAXN][MAXN];
const int oo = (1 << 29);

int S;

bool g[MAXN][MAXN];

bool seen[MAXN];
int matchL[MAXN], matchR[MAXN];

bool bpm(int u) {
    for (int v = 1; v <= S; v++ ) if(g[u][v]) {
        if(seen[v]) continue;
        seen[v] = true;

        if(matchR[v] < 0 || bpm(matchR[v])) {
            matchL[u] = v;
            matchR[v] = u;
            return true;
        }
    }
    return false;
}

int getBpm() {
    memset(matchL, -1, sizeof(matchL));
    memset(matchR, -1, sizeof(matchR));
    int ans = 0;
    for(int i = 1; i <= S; i++) {
        memset(seen, 0, sizeof(seen));
        if(bpm(i)) ans++;
    }
    return ans;
}

void addEdge(int u, int v) {
    g[u][v] = true;
}

int SafeReturn::minRisk(int _S, vector <string> streets) {
    S = _S;
    
    memset(g, 0, sizeof g);
    
    int n = streets.size();
    
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            d[i][j] = oo;
            if (streets[i][j] != '-') d[i][j] = streets[i][j] - '0';
        }
        d[i][i] = 0;
    }
    
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }

    for (int a = 1; a <= S; ++a) {
        for (int b = 1; b <= S; ++b) {
            if (a == b) continue;
            if (d[0][b] == d[0][a] + d[a][b]) {
                addEdge(a, b);
            }
        }
    }
    int ans = getBpm();
    return S - ans;

}

// BEGIN CUT HERE
int main(){
    SafeReturn ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
