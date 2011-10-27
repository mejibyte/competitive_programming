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
    int m[2][2];
};

Matrix operator * (Matrix left, Matrix right) {
    Matrix ans;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            ans.m[i][j] = 0;
            for (int k = 0; k < 2; ++k) {
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


vector<int> minimumRotation(vector<int> v){
    vector<int> ans = v;
    for (int i = 0; i < v.size(); i++) {
        rotate(v.begin(), v.begin() + 2, v.end());
        if (v < ans) ans = v;
    }
    return ans;
}

int normalize(vector<int> &v) {
    int remove = *min_element(v.begin(), v.end());
    for (int i = 0; i < v.size(); ++i) {
        v[i] -= remove;
    }
    if (remove > 0) rotate(v.begin(), v.begin() + 1, v.end());
    v = minimumRotation(v);
    return remove;
}

void print(vector<int> v) {
    For(i, 0, v.size()) printf("%d ", v[i]);
}

int g[2][10][10];

void generateTransitions() {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            g[0][i][j] = g[1][i][j] = 0;
        }
    }
    
    queue< vector< int > > q;
    map < vector< int >, int > seen;
    int last = 0;
    seen[ vector<int>(8, 0) ] = last++;
    q.push( vector<int>(8, 0) );
    
    while (q.size() > 0) {
        vector<int> current = q.front(); q.pop();
        for (int k = 0; k < 8; ++k) {
            if (current[k] == current[(k + 1) % 8] and (k % 2) == (current[k] % 2) ) {
                vector<int> next = current;
                next[k]++; next[(k + 1) % 8]++;
                int level = normalize(next);
                
                printf("From "); print(current); printf("can reach "); print(next); printf(" in this level + %d\n", level);
                
                if (seen.count(next) == 0) {
                    seen[next] = last++;
                    printf("Index of "); print(next); printf("is %d\n", last - 1);
                    q.push(next);
                }
                
                g[level][seen[current]][seen[next]]++;
            }
        }
    }
    printf("There are %d possibilites\n", seen.size());
    For(p, 0, 2) {
        printf("g[%d]:\n", p);
        For(i, 0, 10) {
            For(j, 0, 10) {
                printf("%d ", g[p][i][j]);
            }
            printf("\n");
        }
    }
}

int dp[100001][10];

int Chimney::countWays(long long n) {
    generateTransitions();
    
    memset(dp, 0, sizeof dp);
    dp[0][0] = 1;
    for (int i = 0; i < 7; ++i) {
        printf("i = %d\n", i);
        printf("row i = %d and row i + 1 = %d are:\n", i, i + 1);
        for (int j = 0; j < 10; ++j) printf("%d ", dp[i][j]); puts("");
        for (int j = 0; j < 10; ++j) printf("%d ", dp[i+1][j]); puts("");
        
        for (int j = 0; j < 10; ++j) {
            if (dp[i][j] == 0) continue;
            for (int p = 0; p < 2; ++p) {
                for (int k = 0; k < 10; ++k) {
                    dp[i + p][k] += ((long long)dp[i][j] * g[p][j][k]) % mod;
                    dp[i + p][k] %= mod;
                }
            }
        }
        
        printf("i = %d\n", i);
        printf("row i = %d and row i + 1 = %d are:\n", i, i + 1);
        for (int j = 0; j < 10; ++j) printf("%d ", dp[i][j]); puts("");
        for (int j = 0; j < 10; ++j) printf("%d ", dp[i+1][j]); puts("");
    }
    
    For(i, 0, 7) {
        For(j, 0, 10) {
            printf("%10d ", dp[i][j] % mod);
        }
        puts("");
    }
    
    return dp[n][0];
}

// BEGIN CUT HERE
int main(){
    Chimney ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
