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

class SwitchesAndLamps {
  public:
  int theMin(vector <string> switches, vector <string> lamps);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"NYNN", "NNYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NNNY", "NNYN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(0, Arg2, theMin(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"YYN", "YNY", "YYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"YNY", "NYY", "YNY"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(1, Arg2, theMin(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"NYYYNYNNYYYNYNNNNY", "NYYYNYNNYYYNYNNNNY"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"YYYNNNYNNYNYNYNYNY", "YYYNNNYNNYNYYNNYNY"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(2, Arg2, theMin(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"YYNNN", "NNYYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NYNNY", "NNNYY"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(3, Arg2, theMin(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"YNNYNNYNYY", "NYNNYNYNYN", "YNYNYYYYYN", "NNYYNYNYNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NYYNYNNYNY", "NYYYNNYNNN", "YYYYNYNNYY", "YNNNNYNYYN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(4, Arg2, theMin(Arg0, Arg1)); }

// END CUT HERE

};

vector<bool> can[55];

int SwitchesAndLamps::theMin(vector <string> switches, vector <string> lamps) {
    int n = switches[0].size();
    
    for (int i = 0; i < n; ++i) can[i].assign(n, true);

    for (int s = 0; s < switches.size(); ++s){
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j) {
                if (switches[s][i] != lamps[s][j]) {
                    can[i][j] = false;
                }
            }
        }
    }
    
    for (int l = 0; l < n; ++l) {
        printf("options for lamp %d: ", l);
        for (int s = 0; s < n; ++s) {
            if (can[s][l]) printf("%d ", s);
        }
        puts("");
    }
    
    for (int s = 0; s < n; ++s) {
        printf("options for switch %d: ", s);
        for (int l = 0; l < n; ++l) {
            if (can[s][l]) {
                printf("%d ", l);
            }
        }
        puts("");
    }
    puts("");
    
    map<long long, int> cnt;
    for (int l = 0; l < n; ++l) {
        long long mask = 0;
        for (int s = 0; s < n; ++s) {
            if (can[s][l]) mask |= (1LL << s);
        }
        if (mask == 0) return -1;
        cnt[mask]++;
    }

    int biggest = 0;
    foreach(p, cnt) {
        int pop = __builtin_popcountll(p->first);
        if (p->second > pop) return -1;
        if (pop > biggest) biggest = pop;
    }
    
    int ans = 0;
    while ((1 << ans) < biggest) ans++;
    return ans;
}

bool solvable(vector <string> switches, vector <string> lamps) {
    int n = switches[0].size();
    assert(n <= 10);
    vector<int> p(n);
    for (int i = 0; i < n; ++i) p[i] = i;
    
    int best = INT_MAX;
    do {
        bool ok = true;
        
        for (int k = 0; k < switches.size(); ++k) {
            string &s = switches[k];
            string &l = lamps[k];
            
            for (int i = 0; i < s.size(); ++i) {
                if (s[i] != l[p[i]]) {
                    ok = false;
                }
            }
        }
        
        if (ok) return true;
    } while (next_permutation(p.begin(), p.end()));
    return false;
}


void check() {
    SwitchesAndLamps test;
    
    
    int n = 4;
    vector<string> s;
    vector<string> l;
    
    for (int i = 0; i < 2; ++i) {
        string ss = "";
        for (int i = 0; i < n; ++i) {
            ss += (rand() % 2 == 0 ? 'Y' : 'N');
        }
        s.push_back(ss);
        random_shuffle(ss.begin(), ss.end());
        l.push_back(ss);
    }
    
        
    int ans = test.theMin(s, l);
    bool sol = solvable(s, l);
    
    puts("Random test:");
    For(i, 0, s.size()) cout << s[i] << " "; puts("");
    For(i, 0, l.size()) cout << l[i] << " "; puts("");
    puts(sol ? "solvable" : "not solvable");
    
    if (ans != -1 and !sol or ans == -1 and sol) {
        printf("FUCK: One solved it and the other one didn't: ans = %d, sol = %d\n", ans, sol);
        
        assert(false);
    }
    
    if (sol) {
        if (ans < 0) {
            printf("Solvable but answer was negative! ans = %d\n", ans);
            assert(false);
        }
    }
}


// BEGIN CUT HERE
int main(){
    
    // for (int i = 0; i < 200; ++i) {
    //      check();
    // }
    
    SwitchesAndLamps ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE

//{{"NYYYNNYYNNYNNNNYYYNYNYNYYYNYNNNYNNYNNNNNNYYNYNN", "NYYYYYYYNNYYYNNYYYNYNYNYYYYYYNNYNNYNNYNYNYYYYYY", "NYNYNNYYNYNNYNYNYYYNYYYNYYNYNNYYYNYYYYYYYNYYYYY", "YYYNNNYNYYYNNYYYYYYYYYYYYNNYNYYYYYYYYNYNYYYNNNN", "NYNNYYNNYNYYNNNNYYNYNYNNNNYNYNNYNYNNNNNNNYNNNNN", "NNYNNNNNNYYNYNYYNNYYYNYYNNNNNNYNYNNYYYYYYYNYNYY", "NNYYYYYYNNYYNNNYNNNYNNNYYYYYYNNNNNYNNNNNNYYNYNN", "NYNYYYNYYYYYYNYNYYYYYYYNNYYNYNYYYYNYYYYYYYNYYYY", "YNNYNNNYNYNNYYYNNNYNYNYNNYNNNYYNYNNYYYYYYNNYYYY", "NNYYYYYYNNYYYNNYNNNYNNNYYYYYYNNNNNYNNYNYNYYYYYY", "NYYYNNYYNYYNYNYYYYYYYYYYYYNYNNYYYNYYYYYYYYYYYYY", "YYNNNNNNYYYNNYYNYYYYYYYNNNNNNYYYYYNYYNYNYYNNNNN", "NYNNNNNNNYYNNNYNYYYYYYYNNNNNNNYYYNNYYNYNYYNNNNN", "YYNNNNNNNYYNNYYNYYYYYYYNNNNNNYYYYNNYYNYNYYNNNNN", "YNYNYYNNNYYYNYYYNNYYYNYYNNYNYYYNYNNYYNYNYYNNNNN"}, {"NNNNNNYYNYNYYYNYYNYNNYNYNNYYYNYNNYNNYYNNNNNNYYN", "NYNNYYYYYYNYYYYYYNYNNYNYNNYYYNYNNYYYYYYYYYNNYYN", "YYYNYNYYYYYYYYNNNYYNYYYNYNNYYYYYYYNYYNYNYNNNYNY", "YNYYNNYNNYYNNYNYYYYYYYYYYYYYYYYYYYNNYYNNNNYYNYY", "NNNYNYNNNNNNNYYNNNNYNYNYNNNYYNYNNNYNNYNYNYNNNYN", "YYYNYNNNYNYNNNNYYYNNYNYYYNYNNYNYYNNYNYYNYNNNNYY", "NNNNNYYYNYNYYNYYYNYNNNNYNNYNNNNNNYYNYYNYNYNNYYN", "YYYYYYNYYNYYYYYNNYNYYYYYYNNYYYYYYNYYNYYYYYNNYYY", "YYYNYNNYYNYYYNNNNYNNYNYNYYNNNYNYYNNYNNYNYNYYYNY", "NYNNYYYYYYNYYNYYYNYNNNNYNNYNNNNNNYYYYYYYYYNNYYN", "YYYNYNYYYYYYYYNYYYYNYYYYYNYYYYYYYYNYYYYNYNNNYYY", "YNYYNNNNNNYNNYNNNYNYYYYYYYNYYYYYYNNNNYNNNNYYNYY", "YNYNNNNNNNYNNYNNNYNNYYYYYNNYYYYYYNNNNYNNNNNNNYY", "YNYNNNNNNNYNNYNNNYNNYYYYYYNYYYYYYNNNNYNNNNYYNYY", "YNYNNYNNNNYNNNYYYYNNYNYYYYYNNYNYYNYNNYNYNYYYNYY"}}