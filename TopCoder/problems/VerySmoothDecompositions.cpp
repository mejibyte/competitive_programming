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

class VerySmoothDecompositions {
  public:
  int solve(vector <string> digits);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"47"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(0, Arg1, solve(Arg0)); }
	void test_case_1() { string Arr0[] = {"2"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(1, Arg1, solve(Arg0)); }
	void test_case_2() { string Arr0[] = {"10"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, solve(Arg0)); }
	void test_case_3() { string Arr0[] = {"36"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; verify_case(3, Arg1, solve(Arg0)); }
	void test_case_4() { string Arr0[] = {"1","21"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(4, Arg1, solve(Arg0)); }
	void test_case_5() { string Arr0[] = {"1024"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 23; verify_case(5, Arg1, solve(Arg0)); }

// END CUT HERE

};

int MOD = 1000000009;
int primes[] = {2,3,5,7,11,13};
int options[8][2] = {{1,0},{0,1},{2,0},{1,1},{3,0},{0,2},{2,1},{4,0}}; // decomps of 2,3,4,6,8,9,12,16 into 2^s 3^t

vector<int> X, P;
vector< vector<int> > C;

void divide(vector<int> &num, int den, vector<int> &out, int &rem) {
    rem = 0;
    out = vector<int>(num.size(),0);
    for (int i=num.size()-1; i>=0; --i) { int tmp=10*rem+num[i]; out[i]=tmp/den; rem=tmp%den; }
    while (num.back()==0) num.pop_back();
}


int VerySmoothDecompositions::solve(vector <string> digits) {
    // change the input into a vector of digits D
    string tmp = ""; for (unsigned i=0; i<digits.size(); ++i) tmp += digits[i];
    reverse( tmp.begin(), tmp.end() );
    vector<int> D; for (unsigned i=0; i<tmp.size(); ++i) D.push_back( tmp[i]-'0' );

    // partially factorize D
    X.assign(14, 0);
    
    for (int p=0; p<6; ++p) {
        while (true) {
            vector<int> nD; int rem;
            divide(D, primes[p], nD, rem);
            if (rem > 0) break;
            ++X[primes[p]];
            D=nD;
        }
    }
    if (D.size() > 1u || D[0] > 1) return 0; // has a large prime factor

    // compute the array C, counting the decompositions for numbers of the form 2^p 3^q
    C.assign(X[2] + 1, vector<int>(X[3] + 1, 0) );
    C[0][0] = 1;
    for (int k = 0; k < 8; ++k) {    
        for (int p = 0; p <= X[2]; ++p) {
            for (int q = 0; q <= X[3]; ++q) {
                int smallerP = p - options[k][0];
                int smallerQ = q - options[k][1];
                if (smallerP >= 0 and smallerQ >= 0) {
                    C[p][q] += C[smallerP][smallerQ];
                    if (C[p][q] >= MOD) C[p][q] -= MOD;
                }
            }
        }
    }
    
    
    int x2 = X[2], x3 = X[3], x5 = X[5], x7 = X[7]; 
    long long answer = 0;
    for (int a15 = 0; a15 <= min(x3, x5); ++a15) {
        int q = x3 - a15;
        assert(q >= 0);
        P.assign(x2 + 1, 0);
        for (int i = 0; i <= x2; ++i) {
            P[i] = C[i][q];
            if (i - 1 >= 0) P[i] += P[i-1];
            if (P[i] >= MOD) P[i] -= MOD;
        }
        
        for (int a10 = 0; a10 <= min(x2, x5 - a15); ++a10) {
            assert(x2 - a10 >= 0);
            answer += P[x2 - a10];
            int k = x2 - a10 - min(x2 - a10, x7) - 1;
            if (k >= 0) answer -= P[k];
            answer %= MOD;
            if (answer < 0) {
                answer += MOD;
                answer %= MOD;
            }
        }
    }
    
    return answer;
}


// BEGIN CUT HERE
int main(){
    VerySmoothDecompositions ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
