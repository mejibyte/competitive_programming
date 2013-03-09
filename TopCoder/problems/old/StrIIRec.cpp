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

class StrIIRec {
  public:
  string recovstr(int n, int minInv, string minStr);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 1; string Arg2 = "ab"; string Arg3 = "ba"; verify_case(0, Arg3, recovstr(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 9; int Arg1 = 1; string Arg2 = "efcdgab"; string Arg3 = "efcdgabhi"; verify_case(1, Arg3, recovstr(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 11; int Arg1 = 55; string Arg2 = "debgikjfc"; string Arg3 = "kjihgfedcba"; verify_case(2, Arg3, recovstr(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 15; int Arg1 = 0; string Arg2 = "e"; string Arg3 = "eabcdfghijklmno"; verify_case(3, Arg3, recovstr(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 9; int Arg1 = 20; string Arg2 = "fcdebiha"; string Arg3 = "fcdehigba"; verify_case(4, Arg3, recovstr(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

int inversions(const string &s) {
    int ans = 0;
    for (int i = 0; i < s.size(); ++i) {
        for (int j = i + 1; j < s.size(); ++j) {
            ans += s[i] > s[j];
        }
    }
    return ans;
}

string StrIIRec::recovstr(int n, int minInv, string minStr) {
    while (minStr.size() < n) {
        char next = 'a';
        while (minStr.find(next) != -1) next++;
        minStr += next;
    }
    
    set<char> avail;
    for (int i = 0; i < n; ++i) avail.insert('a' + i);
    
    string ans = "";
    for (int i = 0; i < n; ++i) {
        // add one character to ans
        for (int c = 0; c < n; ++c) {
            char next_char = 'a' + c;
            if (avail.count(next_char) == 0) continue;
            if (ans + next_char < minStr.substr(0, i + 1)) continue;
            // now count how many inversions can be built, at most
            string s = ans + next_char;
            for (set<char>::reverse_iterator k = avail.rbegin(); k != avail.rend(); ++k) {
                if (*k != next_char) s += *k;
            }
            if (inversions(s) >= minInv) {
                ans += next_char;
                avail.erase(next_char);
                break;
            }
        }
    }
    return ans;
}

// BEGIN CUT HERE
int main(){
    StrIIRec test;
    test.run_test(-1);
    return 0;
}
// END CUT HERE
