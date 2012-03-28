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

class TurtleSpy {
  public:
  double maxDistance(vector <string> commands);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"forward 100", "backward 100", "left 90" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 141.4213562373095; verify_case(0, Arg1, maxDistance(Arg0)); }
	void test_case_1() { string Arr0[] = {"left 45", "forward 100", "right 45", "forward 100"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 200.0; verify_case(1, Arg1, maxDistance(Arg0)); }
	void test_case_2() { string Arr0[] = {"left 10", "forward 40",  "right 30", "left 10", "backward 4", "forward 4" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 40.58520737741619; verify_case(2, Arg1, maxDistance(Arg0)); }

// END CUT HERE

};

#include <bitset>

bitset<360> canRotate;

const double pi = 2 * acos(0);

double TurtleSpy::maxDistance(vector <string> commands) {
    canRotate.reset();
    double x = 0, y = 0;

    canRotate[0] = true;
    double backward = 0;
    for (int i = 0; i < commands.size(); ++i) {
        char buf[50]; int by;
        sscanf(commands[i].c_str(), "%s %d", buf, &by);
        string s(buf);
        if (s == "forward") {
            x += by;
        } else if (s == "backward") {
            backward += by;
        } else {
            if (s == "left") by = 360 - by;
            
            bitset<360> nextCanRotate;
            for (int a = 0; a < 360; ++a) {
                if (canRotate[a]) {
                    nextCanRotate[a] = true;
                    nextCanRotate[(a + by) % 360] = true;
                }
            }
            canRotate = nextCanRotate;
        }
    }
    
    for (int a = 180; a >= 0; --a) {
        if (canRotate[a] or canRotate[360 - a]) {
            x -= backward * cos(a * pi / 180);
            y += backward * sin(a * pi / 180);
            break;
        }
    }

    return sqrt(x*x + y*y);
}

// BEGIN CUT HERE
int main(){
    TurtleSpy ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
