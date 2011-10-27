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

class RequiredSubstrings {
  public:
  int solve(vector <string> words, int C, int L);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"a","aa","aaa","aaaa"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 3; int Arg3 = 50; verify_case(0, Arg3, solve(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"abcdefgh"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 7; int Arg3 = 31810104; verify_case(1, Arg3, solve(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"abcdefgh"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 7; int Arg3 = 0; verify_case(2, Arg3, solve(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"a","b","c","d"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 3; int Arg3 = 24; verify_case(3, Arg3, solve(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arr0[] = {"ab","bc","xy","yz"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 3; int Arg3 = 2; verify_case(4, Arg3, solve(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

/////////////////////////////////////////////////////////////////////////////////////////
// Aho-Corasick's algorithm, as explained in  http://dx.doi.org/10.1145/360825.360855  //
/////////////////////////////////////////////////////////////////////////////////////////

const int MAXS = 6 * 50 + 10; // Max number of states in the matching machine.
                              // Should be equal to the sum of the length of all keywords.

const int MAXC = 26; // Number of characters in the alphabet.

int out[MAXS]; // Output for each state, as a bitwise mask.
               // Bit i in this mask is on if the keyword with index i appears when the
               // machine enters this state.

// Used internally in the algorithm.
int f[MAXS]; // Failure function
int g[MAXS][MAXC]; // Goto function, or -1 if fail.

// Builds the string matching machine.
// 
// words - Vector of keywords. The index of each keyword is important:
//         "out[state] & (1 << i)" is > 0 if we just found word[i] in the text.
// lowestChar - The lowest char in the alphabet. Defaults to 'a'.
// highestChar - The highest char in the alphabet. Defaults to 'z'.
//               "highestChar - lowestChar" must be <= MAXC, otherwise we will
//               access the g matrix outside its bounds and things will go wrong.
//
// Returns the number of states that the new machine has. 
// States are numbered 0 up to the return value - 1, inclusive.
int buildMatchingMachine(const vector<string> &words, char lowestChar = 'a', char highestChar = 'z') {
    memset(out, 0, sizeof out);
    memset(f, -1, sizeof f);
    memset(g, -1, sizeof g);
    
    int states = 1; // Initially, we just have the 0 state
        
    for (int i = 0; i < words.size(); ++i) {
        const string &keyword = words[i];
        int currentState = 0;
        for (int j = 0; j < keyword.size(); ++j) {
            int c = keyword[j] - lowestChar;
            if (g[currentState][c] == -1) { // Allocate a new node
                g[currentState][c] = states++;
            }
            currentState = g[currentState][c];
        }
        out[currentState] |= (1 << i); // There's a match of keywords[i] at node currentState.
    }
    
    // State 0 should have an outgoing edge for all characters.
    for (int c = 0; c < MAXC; ++c) {
        if (g[0][c] == -1) {
            g[0][c] = 0;
        }
    }

    // Now, let's build the failure function
    queue<int> q;
    for (int c = 0; c <= highestChar - lowestChar; ++c) {  // Iterate over every possible input
        // All nodes s of depth 1 have f[s] = 0
        if (g[0][c] != -1 and g[0][c] != 0) {
            f[g[0][c]] = 0;
            q.push(g[0][c]);
        }
    }
    while (q.size()) {
        int state = q.front();
        q.pop();
        for (int c = 0; c <= highestChar - lowestChar; ++c) {
            if (g[state][c] != -1) {
                int failure = f[state];
                while (g[failure][c] == -1) {
                    failure = f[failure];
                }
                failure = g[failure][c];
                f[g[state][c]] = failure;
                out[g[state][c]] |= out[failure]; // Merge out values
                q.push(g[state][c]);
            }
        }
    }

    return states;
}

// Finds the next state the machine will transition to.
//
// currentState - The current state of the machine. Must be between
//                0 and the number of states - 1, inclusive.
// nextInput - The next character that enters into the machine. Should be between lowestChar 
//             and highestChar, inclusive.
// lowestChar - Should be the same lowestChar that was passed to "buildMatchingMachine".

// Returns the next state the machine will transition to. This is an integer between
// 0 and the number of states - 1, inclusive.
int findNextState(int currentState, char nextInput, char lowestChar = 'a') {
    int answer = currentState;
    int c = nextInput - lowestChar;
    while (g[answer][c] == -1) answer = f[answer];
    return g[answer][c];
}


// How to use this algorithm:
// 
// 1. Modify the MAXS and MAXC constants as appropriate.
// 2. Call buildMatchingMachine with the set of keywords to search for.
// 3. Start at state 0. Call findNextState to incrementally transition between states.
// 4. Check the out function to see if a keyword has been matched.
//
// Example:
//
// Assume keywords is a vector that contains {"he", "she", "hers", "his"} and text is a string
// that contains "ahishers".
//
// Consider this program:
//
// buildMatchingMachine(keywords, 'a', 'z');
// int currentState = 0;
// for (int i = 0; i < text.size(); ++i) {
//    currentState = findNextState(currentState, text[i], 'a');
//    if (out[currentState] == 0) continue; // Nothing new, let's move on to the next character.
//    for (int j = 0; j < keywords.size(); ++j) {
//        if (out[currentState] & (1 << j)) { // Matched keywords[j]
//            cout << "Keyword " << keywords[j] << " appears from "
//                 << i - keywords[j].size() + 1 << " to " << i << endl;
//        }
//    }
// }
//
// The output of this program is:
//
// Keyword his appears from 1 to 3
// Keyword he appears from 4 to 5
// Keyword she appears from 3 to 5
// Keyword hers appears from 4 to 7

/////////////////////////////////////////////////////////////////////////////////////////
//                          End of Aho-Corasick's algorithm.                           //
/////////////////////////////////////////////////////////////////////////////////////////



int dp[55][MAXS][1 << 6];

int RequiredSubstrings::solve(vector <string> words, int C, int L) {
    int mod = 1000000009;
    
    int states = buildMatchingMachine(words);
    memset(dp, 0, sizeof dp);
    dp[0][0][0] = 1;
    for (int l = 0; l < L; ++l) {
        for (int s = 0; s < states; ++s) {
            for (int seen = 0; seen < (1 << words.size()); ++seen) {
                if (dp[l][s][seen] == 0) continue;
                for (int c = 'a'; c <= 'z'; ++c) {
                    int nextState = findNextState(s, c);
                    int nextSeen = seen | out[nextState];
                    
                    dp[l+1][nextState][nextSeen] += dp[l][s][seen];
                    if (dp[l+1][nextState][nextSeen] >= mod) {
                        dp[l+1][nextState][nextSeen] -= mod;
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int seen = 0; seen < (1 << words.size()); ++seen) {
        if (__builtin_popcount(seen) != C) continue;
        for (int s = 0; s < states; ++s) {
            ans += dp[L][s][seen];
            if (ans >= mod) ans -= mod;
        }
    }
    return ans;
}

// BEGIN CUT HERE
int main(){
    RequiredSubstrings ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
