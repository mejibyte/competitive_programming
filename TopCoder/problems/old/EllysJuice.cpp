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

class EllysJuice {
  public:
  vector <string> getWinners(vector <string> players);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = { "elly", "kriss", "stancho", "elly", "stancho" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"elly", "stancho" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, getWinners(Arg0)); }
	void test_case_1() { string Arr0[] = {"torb", "elly", "stancho", "kriss"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = { }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, getWinners(Arg0)); }
	void test_case_2() { string Arr0[] = {"elly", "elly", "elly", "elly", "elly"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"elly" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, getWinners(Arg0)); }
	void test_case_3() { string Arr0[] = { "ariadne", "elly", "ariadne", "stancho", "stancho", "kriss", "stancho", "elly" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"ariadne", "elly", "stancho" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, getWinners(Arg0)); }

// END CUT HERE

};

vector <string> EllysJuice::getWinners(vector <string> players) {
    sort(players.begin(), players.end());
    set<string> winners;
    do {
        map<string, int> drunk;
        int apple = 512, orange = 512;
        for (int i = 0; i < players.size(); ++i) {
            string p = players[i];
            if (i % 2 == 0) {
                drunk[p] += apple;
                apple /= 2;
            } else {
                drunk[p] += orange;
                orange /= 2;
            }
        }
        
        int best = -1, count = -1;
        string who;
        foreach(s, players) {
            if (drunk[*s] > best) {
                best = drunk[*s];
                count = 1;
                who = *s;
            } else if (drunk[*s] == best and *s != who) {
                count++;
            }
        }
        if (count == 1) winners.insert(who);
    } while (next_permutation(players.begin(), players.end()));
    
    vector<string> ans;
    foreach(s, winners) ans.push_back(*s);
    return ans;
}


vector <string> bad(vector <string> players) {
    sort(players.begin(), players.end());
    set<string> winners;
    do {
        map<string, double> drunk;
        double apple = 1.0, orange = 1.0;
        for (int i = 0; i < players.size(); ++i) {
            string p = players[i];
            if (i % 2 == 0) {
                drunk[p] += apple;
                apple /= 2.0;
            } else {
                drunk[p] += orange;
                orange /= 2.0;
            }
        }
        
        double best = -1;
        int count = -1;
        string who;
        foreach(s, players) {
            if (drunk[*s] > best) {
                best = drunk[*s];
                count = 1;
                who = *s;
            } else if (drunk[*s] == best and *s != who) {
                count++;
            }
        }
        if (count == 1) winners.insert(who);
    } while (next_permutation(players.begin(), players.end()));
    
    vector<string> ans;
    foreach(s, winners) ans.push_back(*s);
    return ans;
}

// BEGIN CUT HERE
int main(){
    
    EllysJuice ___test;
    
    for (int casos = 0; casos < 100; ++casos) {
        int n = 8;
        vector<string> ppl;
        for (int i = 0; i < n; ++i) {
            string s = "";
            s += char(rand() % 4 + 'a');
            ppl.push_back(s);
        }
        printf(".");

        if (___test.getWinners(ppl) != bad(ppl)) {
            for (int i = 0; i < ppl.size(); ++i) printf("%s,", ppl[i].c_str());
            exit(0);
        }
    }
    

    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
