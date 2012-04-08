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

map < vector< int >, int > seen;

int nextLevel[10][10];

void generateStates() {
    queue< vector< int > > q;
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

                if (seen.count(next) == 0) {
                    seen[next] = last++;
                    q.push(next);
                }
                
                if (level > 0) {
                    nextLevel[seen[current]][seen[next]]++;
                }
            }
        }
    }
}

int g[10][10];

int ways(vector<int> current, vector<int> objective) {
    if (*min_element(current.begin(), current.end()) > 0) {
        normalize(current);
        normalize(objective);
        return current == objective;
    }
    
    normalize(current);
    normalize(objective);    
    int ans = 0;

    for (int k = 0; k < 8; ++k) {
        if (current[k] == current[(k + 1) % 8] and (k % 2) == (current[k] % 2) ) {
            vector<int> next = current;
            next[k]++; next[(k + 1) % 8]++;
            ans += ways(next, objective);
        }
    }
    return ans;
}

int Chimney::countWays(long long n) {
    seen.clear();
    memset(nextLevel, 0, sizeof nextLevel);
    generateStates();
    // printf("Next level is:\n");
    // For(i, 0, 10) {
    //     printf("i=%d: ", i);
    //     For(j, 0, 10) {
    //         printf("%2d ", nextLevel[i][j]);
    //     }
    //     puts("");
    // }
    memset(g, 0, sizeof g);
    foreach(start, seen) {
        foreach(next, seen) {
            g[start->second][next->second] = ways(start->first, next->first);
        }
    }
    // For(i, 0, 10) {
    //     For(j, 0, 10) {
    //         printf("%2d ", g[i][j]);
    //     }
    //     puts("");
    // }
    Matrix m;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            m.m[i][j] = g[i][j];
        }
    }
    m = pow(m, n);
    
    return m.m[0][0];
}

// BEGIN CUT HERE
int main(){
    Chimney ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
