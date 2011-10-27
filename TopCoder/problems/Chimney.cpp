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

class Chimney {
  public:
  int countWays(long long n);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 1LL; int Arg1 = 24; verify_case(0, Arg1, countWays(Arg0)); }
	void test_case_1() { long long Arg0 = 2LL; int Arg1 = 1088; verify_case(1, Arg1, countWays(Arg0)); }
	void test_case_2() { long long Arg0 = 5LL; int Arg1 = 110198784; verify_case(2, Arg1, countWays(Arg0)); }
	void test_case_3() { long long Arg0 = 6LL; int Arg1 = 138284509; verify_case(3, Arg1, countWays(Arg0)); }
	void test_case_4() { long long Arg0 = 100000LL; int Arg1 = 19900327; verify_case(4, Arg1, countWays(Arg0)); }

// END CUT HERE

};

const int mod = 1000000007;

struct Matrix {
    int m[10][10];
};

Matrix operator * (Matrix left, Matrix right) {
    Matrix ans;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            ans.m[i][j] = 0;
            for (int k = 0; k < 10; ++k) {
                ans.m[i][j] += (1LL * left.m[i][k] * right.m[k][j]) % mod;
                ans.m[i][j] %= mod;
            }
        }
    }
    return ans;
}

Matrix pow(Matrix a, long long n) {
    if (n == 1) return a;
    if (n == 2) return a * a;
    if (n % 2 == 0) {
        Matrix half = pow(a, n / 2);
        return half * half;
    } else {
        return a * pow(a, n - 1);
    }
}

// Possible states are:
// 0: 00000000
// 1: 00000011
// 2: 00001111
// 3: 00110011
// 4: 00111111
// 5: 00001221
// 6: 00122111
// 7: 00111221
// 8: 00122221
// 9: 00123321


// Returns the lexicographically smallest equivalent representation of state v
// e.g. for "00122100" returns "00001221".
vector<int> minimumRotation(vector<int> v){
    vector<int> ans = v;
    for (int i = 0; i < v.size(); i++) {
        rotate(v.begin(), v.begin() + 2, v.end());
        if (v < ans) ans = v;
    }
    return ans;
}

// If we already advanced to next floor, makes it look like we hadn't but returns 1
// to indicate we did.
// e.g. converts "11123321" into "00001221" and returns 1 to indicate we did advance one floor.
int normalize(vector<int> &v) {
    int remove = *min_element(v.begin(), v.end());
    for (int i = 0; i < v.size(); ++i) {
        v[i] -= remove;
    }
    if (remove > 0) rotate(v.begin(), v.begin() + 1, v.end()); // move to next floor
    v = minimumRotation(v);
    return remove;
}

// g[0][i][j] = In how many ways I can place a single brick to go from state i to state j without forming a complete new level.
// g[1][i][j] = In how many ways I can place a single brick to go from state i to state j forming a complete new level.
int g[2][10][10];

void generateTransitions() {
    memset(g, 0, sizeof g);
    
    queue< vector< int > > q;
    map < vector< int >, int > seen;
    int last = 0;
    seen[ vector<int>(8, 0) ] = last++;
    q.push( vector<int>(8, 0) ); // Start with an empty floor, i.e "00000000"
    
    while (q.size() > 0) {
        vector<int> current = q.front(); q.pop();
        for (int k = 0; k < 8; ++k) {
            if (current[k] == current[(k + 1) % 8] and (k % 2) == (current[k] % 2) ) {
                vector<int> next = current;
                next[k]++; next[(k + 1) % 8]++;
                int level = normalize(next);
                
                if (seen.count(next) == 0) {
                    seen[next] = last++;
                    q.push(next);
                }
                
                g[level][seen[current]][seen[next]]++;
            }
        }
    }
}

int Chimney::countWays(long long n) {
    generateTransitions();
    
    Matrix theMatrix;
    // theMatrix.m[i][j] = In how many ways I can go from state i to state j forming a complete new level.
    for (int i = 9; i >= 0; --i) {
        for (int j = 0; j < 10; ++j) {

            theMatrix.m[i][j] = g[1][i][j];
            for (int k = i + 1; k < 10; ++k) {
                // First, reach a state with more bricks (k) and from k, reach the next level recursively.
                theMatrix.m[i][j] += g[0][i][k] * theMatrix.m[k][j];
            }
        }
    }
    
    
    theMatrix = pow(theMatrix, n); // I should have taken the blue pill
    return theMatrix.m[0][0];
}

// BEGIN CUT HERE
int main(){
    Chimney ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
