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

class NoRepeatPlaylist {
  public:
  int numPlaylists(int N, int M, int P);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 0; int Arg2 = 3; int Arg3 = 1; verify_case(0, Arg3, numPlaylists(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 3; int Arg3 = 0; verify_case(1, Arg3, numPlaylists(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 2; int Arg1 = 0; int Arg2 = 3; int Arg3 = 6; verify_case(2, Arg3, numPlaylists(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 4; int Arg1 = 0; int Arg2 = 4; int Arg3 = 24; verify_case(3, Arg3, numPlaylists(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 2; int Arg1 = 1; int Arg2 = 4; int Arg3 = 2; verify_case(4, Arg3, numPlaylists(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arg0 = 50; int Arg1 = 5; int Arg2 = 100; int Arg3 = 222288991; verify_case(5, Arg3, numPlaylists(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

const int mod = 1000 * 1000 * 1000 + 7;

int dp1[105][105];
int dp2[105][105];
int dp3[105][105];
int dp4[105][105];

#define clear(m) memset(m, 0, sizeof(m))

void add(int &a, long long b) {
    b %= mod;
    a += b;
    a %= mod;
}

int M, N, P;

int f4(int i, int s) {
    if (i == 0) return s == 0;
    
    int &ans = dp4[i][s];
    if (ans != -1) return ans;

    ans = 0;
    // repeat song -- there are S songs available for repeat, except for the last M.
    if (s - M >= 0) add(ans, 1LL * f4(i - 1, s) * (s - M));
    
    // play new song -- I will play a new song and will get s songs played in total. So I have to pick one song out of N, except for the s - 1 I had already played before.
    if (s - 1 >= 0) add(ans, 1LL * f4(i - 1, s - 1) * (N - s + 1));
    return ans;
}

int NoRepeatPlaylist::numPlaylists(int N, int M, int P) {
    ::N = N, ::M = M, ::P = P;
    
    //dp1[i][s] = Number of ways to create a valid playlist of i songs
    //            such that it contains exactly s out of the N possible songs
    //            (possibly repeating songs, but repeating them with M or more songs between them).
    clear(dp1);
    dp1[0][0] = 1;
    for (int i = 0; i < P; ++i) {
        for (int s = 0; s <= N; ++s) {
            if (s - M >= 0) {
                add(dp1[i + 1][s], 1LL * (s - M) * dp1[i][s]);
            }
            if (s < N) {
                add(dp1[i + 1][s + 1], 1LL * (N - s) * dp1[i][s]);
            }
        }
    }
    
    int ans1 = dp1[P][N];
    
    // dp2[i][s] = Number of ways to create a valid playlist of i songs
    //             such that exactly s out of the N possible songs haven't
    //             been played yet.
    clear(dp2);
    dp2[0][N] = 1;
    for (int i = 0; i < P; ++i) {
        for (int s = 0; s <= N; ++s) {
            if (N - s - M >= 0) {
                add(dp2[i + 1][s], 1LL * (N - s - M) * dp2[i][s]);
            }
            if (s > 0) {
                add(dp2[i + 1][s - 1], 1LL * s * dp2[i][s]);
            }
        }
    }
    
    int ans2 = dp2[P][0];
    assert(ans1 == ans2);
    
    //dp3[i][s] = Same as dp1, but implemented backwards.
    clear(dp3);
    dp3[0][0] = 1;
    for (int i = 1; i <= P; ++i) {
        for (int s = 0; s <= N; ++s) {
            if (s - 1 >= 0) {
                add(dp3[i][s], 1LL * (N - s + 1) * dp3[i - 1][s - 1]);
            }
            if (s - M >= 0) {
                add(dp3[i][s], 1LL * (s - M) * dp3[i - 1][s]);
            }
        }
    }
    
    int ans3 = dp3[P][N];
    assert(ans1 == ans3);
    
    // dp4[i][s] = Same as dp1, but implemented bottom up.
    memset(dp4, -1, sizeof dp4);
    int ans4 = f4(P, N);
    return ans4;
    assert(ans1 == ans4);
    
    return ans1;
}

// BEGIN CUT HERE
int main(){
    NoRepeatPlaylist ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
