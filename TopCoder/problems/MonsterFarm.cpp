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

class MonsterFarm {
  public:
  int numMonsters(vector <string> transforms);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, numMonsters(Arg0)); }
	void test_case_1() { string Arr0[] = {"1 1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(1, Arg1, numMonsters(Arg0)); }
	void test_case_2() { string Arr0[] = {"2", "3", "1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(2, Arg1, numMonsters(Arg0)); }
	void test_case_3() { string Arr0[] = {"1", "3 4", "2", "2"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(3, Arg1, numMonsters(Arg0)); }
	void test_case_4() { string Arr0[] = {"2 2", "3", "4 4 4", "5", "6", "7 7 7 7", "7"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 24; verify_case(4, Arg1, numMonsters(Arg0)); }
	void test_case_5() { string Arr0[] = {"2 3","5 7","2 4","5","6","4","7"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(5, Arg1, numMonsters(Arg0)); }

// END CUT HERE

};

const int MAXN = 55;

map<int, int> g[MAXN];

const int mod = 1000000007;

int get(int n, int iterations, int m) {
    
    vector<long long> have(n, 0);
    have[0] = 1LL;
    for (int q = 0; q < iterations; ++q) {
        vector<long long> next(n, 0);
        for (int i = 0; i < n; ++i) {
            foreach(out, g[i]) {
                next[out->first] += (have[i] * out->second) % m;
                next[out->first] %= m;
            }
        }
        have = next;
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += have[i];
        ans %= m;
    }
    return ans;
}

int MonsterFarm::numMonsters(vector <string> transforms) {
    int n = transforms.size();
    for (int i = 0; i < n; ++i) {
        g[i].clear();
    }

    for (int i = 0; i < n; ++i) {
        stringstream sin(transforms[i]);
        for (int x; sin >> x; ) {
            g[i][x - 1]++;
        }
    }
    
    int primes[11] = {
        999999739,
        999999751,
        999999757,
        999999761,
        999999797,
        999999883,
        999999893,
        999999929,
        999999937,
        1000000007,
        1000000009
    };
    
    
    set<int> seen;
    for (int i = 0; i < 11; ++i) {
        int a = get(n, n, primes[i]);
        int b = get(n, 2*n, primes[i]);
        if (a != b) return -1;
    }
    return get(n, 2*n, mod);
}

// BEGIN CUT HERE
int main(){
    MonsterFarm ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
