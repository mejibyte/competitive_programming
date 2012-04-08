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
#include <ext/hash_map>

using namespace __gnu_cxx;

#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl

class AlphabetPaths {
  public:
  long long count(vector <string> letterMaze);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"ABCDEFZHIXKLMNOPQRST",
 "...................V"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 2LL; verify_case(0, Arg1, count(Arg0)); }
	void test_case_1() { string Arr0[] = {".................VT.",
 "....................",
 "ABCDEFZHIXKLMNOPQRS.",
 "..................S.",
 ".................VT."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 0LL; verify_case(1, Arg1, count(Arg0)); }
	void test_case_2() { string Arr0[] = {"TBCDE.PQRSA", 
 "FZHIXKLMNOV"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 50LL; verify_case(2, Arg1, count(Arg0)); }
	void test_case_3() { string Arr0[] = {"ABCDEF.",
 "V....Z.",
 "T....H.",
 "S....I.",
 "R....X.",
 "KLMNOPQ"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 4LL; verify_case(3, Arg1, count(Arg0)); }

// END CUT HERE

};

const int MAXN = 21;

int rows, cols;
int maze[MAXN][MAXN];

int di[] = { -1, +1, +0, +0 };
int dj[] = { +0, +0, -1, +1 };


int freq[1 << MAXN];
vector<int> masks;

void backtrack(int i, int j, int mask, int popcount) {
    if (popcount == 11) {
        freq[mask]++;
        masks.push_back(mask);
        return;
    }

    for (int k = 0; k < 4; ++k) {
        int ni = i + di[k];
        int nj = j + dj[k];
        if (ni < 0 or ni >= rows or nj < 0 or nj >= cols) continue;
        if (maze[ni][nj] < 0) continue;
        if (mask & (1 << maze[ni][nj])) continue;
        
        backtrack(ni, nj, mask | (1 << maze[ni][nj]), popcount + 1);
    }
}


long long AlphabetPaths::count(vector <string> letterMaze) {
    string alphabet = "ABCDEFZHIKLMNOPQRSTVX";
    rows = letterMaze.size(), cols = letterMaze[0].size();
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            char c = letterMaze[i][j];
            maze[i][j] = alphabet.find(c);
            if (c == '.') assert(maze[i][j] == -1);
        }
    }
    
    long long ans = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (maze[i][j] == -1) continue;

            foreach(p, masks) {
                freq[*p] = 0;
            }
            masks.clear();

            backtrack(i, j, 1 << maze[i][j], 1);

            foreach(p, masks) {
                int me = *p;
                int half_orange = (~me & ((1 << 21) - 1)) | (1 << maze[i][j]);

                ans += freq[half_orange];
            }
        }
    }
    return ans;
}

// BEGIN CUT HERE
int main(){
    string s = "ABCDEFZHIKLMNOPQRSTVX";
    for (int i = 0; i < 21; ++i) {
        cout << s << ",";
        rotate(s.begin(), s.begin() + 2, s.end());
    }
    puts("");

    AlphabetPaths ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
