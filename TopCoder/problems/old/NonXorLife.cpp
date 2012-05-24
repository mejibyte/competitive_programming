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

class NonXorLife {
  public:
  int countAliveCells(vector <string> field, int K);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"oo"
,"o."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 36; verify_case(0, Arg2, countAliveCells(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {".."
,".."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 23; int Arg2 = 0; verify_case(1, Arg2, countAliveCells(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"o"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1000; int Arg2 = 2002001; verify_case(2, Arg2, countAliveCells(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"o.oo.ooo"
,"o.o.o.oo"
,"ooo.oooo"
,"o.o..o.o"
,"o.o..o.o"
,"o..oooo."
,"..o.o.oo"
,"oo.ooo.o"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1234; int Arg2 = 3082590; verify_case(3, Arg2, countAliveCells(Arg0, Arg1)); }

// END CUT HERE

};

const int MAXN = 3105;
const int SHIFT = 1505;

int d[MAXN][MAXN];

int NonXorLife::countAliveCells(vector <string> field, int K) {
    memset(d, -1, sizeof d);
    
    int ans = 0;
    
    queue<int> q;
    for (int i = 0; i < field.size(); ++i) {
        for (int j = 0; j < field[i].size(); ++j) {
            if (field[i][j] == 'o') {
                d[i + SHIFT][j + SHIFT] = 0;
                q.push(i + SHIFT); q.push(j + SHIFT);
                ans++;
            }
        }
    }
    
    while (q.size() > 0) {
        int i = q.front(); q.pop();
        int j = q.front(); q.pop();
        if (d[i][j] == K) continue;
        for (int di = -1; di <= +1; ++di) {
            for (int dj = -1; dj <= +1; ++dj) {
                if ((di != 0) ^ (dj != 0)) {
                    int ni = i + di, nj = j + dj;
                    assert(0 <= ni and ni < MAXN and 0 <= nj and nj < MAXN);
                    if (d[ni][nj] == -1) {
                        ans++;
                        d[ni][nj] = d[i][j] + 1;
                        q.push(ni);
                        q.push(nj);
                    }
                }
            }
        }
    }
    
    return ans;
}

// BEGIN CUT HERE
int main(){
    NonXorLife test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
