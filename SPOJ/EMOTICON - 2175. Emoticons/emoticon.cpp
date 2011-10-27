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

/////////////////////////////////////////////////////////////////////////////////////////
// Aho-Corasick's algorithm, as explained in  http://dx.doi.org/10.1145/360825.360855  //
/////////////////////////////////////////////////////////////////////////////////////////

const int MAXS = 15 * 100 + 10; // Max number of states in the matching machine.
                                // Should be equal to the sum of the length of all keywords.

const int MAXC = 256; // Number of characters in the alphabet.

vector<int> out[MAXS]; // Output for each state.
                       // out[s] is a vector with the indeces of all keywords found when 
                       // the machine reaches the state s.

// Used internally in the algorithm.
int f[MAXS]; // Failure function
int g[MAXS][MAXC]; // Goto function, or -1 if fail.

// Builds the string matching machine.
// 
// words - Vector of keywords. The index of each keyword is important:
//         "out[state]" contains i if we just found word[i] in the text.
// lowestChar - The lowest char in the alphabet. Defaults to 0.
// highestChar - The highest char in the alphabet. Defaults to 255.
//               "highestChar - lowestChar" must be <= MAXC, otherwise we will
//               access the g matrix outside its bounds and things will go wrong.
//
// Returns the number of states that the new machine has.
// States are numbered 0 up to the return value - 1, inclusive.
int buildMatchingMachine(const vector<string> &words, int lowestChar = 0, int highestChar = 255) {
    for (int i = 0; i < MAXS; ++i) out[i].clear();
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
        out[currentState].push_back(i);
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
                
                for (int k = 0; k < out[failure].size(); ++k) { // Merge output from the failure state into this one
                    out[g[state][c]].push_back(out[failure][k]);
                }
                
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
int findNextState(int currentState, char nextInput, int lowestChar = 0) {
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
// buildMatchingMachine(v, 'a', 'z');
// int currentState = 0;
// for (int i = 0; i < text.size(); ++i) {
//    currentState = findNextState(currentState, text[i], 'a');
//    if (out[currentState.size() == 0) continue; // Nothing new, let's move on to the next character.
//    for (int j = 0; j < out[currentState].size(); ++j) {
//        const string &keyword = keywords[out[currentState][j]];
//        cout << "Keyword " << keyword << " appears from "
//             << i - keyword.size() + 1 << " to " << i << endl;
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

vector<string> keywords;

void simplifyKeywords() {
    int K = keywords.size();
    // Remove duplicate keywords
    sort(keywords.begin(), keywords.end());
    keywords.resize(unique(keywords.begin(), keywords.end()) - keywords.begin());
    assert(keywords.size() <= K);
    
    K = keywords.size();
    vector<bool> rm(K, false);
    for (int i = 0; i < K; ++i) {
        for (int j = 0; j < K; ++j) {
            if (i == j) continue;
            if (keywords[i].find(keywords[j]) != string::npos) {
                // keywords[j] is a substring of keywords[i], delete i
                rm[i] = true;
            }
        }
    }

    vector<string> newKeywords;
    for (int i = 0; i < K; ++i) {
        if (!rm[i]) newKeywords.push_back(keywords[i]);
    }
    keywords = newKeywords;
    assert(keywords.size() <= K);
}

int minimumChanges(const string &s) {
    vector< pair<int, int> > intervals;
    int state = 0;
    for (int j = 0; j < s.size(); ++j) {
        state = findNextState(state, s[j]);
        
        for (int k = 0; k < out[state].size(); ++k) {
            const string &word = keywords[  out[state][k]   ];
            intervals.push_back(   make_pair(j - word.size() + 1,  j)    );
        }
    }
    int ans = 0, last = -1;
    
    for (int i = 0; i < intervals.size(); ++i) {
        int u = intervals[i].first, v = intervals[i].second;
        assert(last < v);
        if (last < u) {
            last = v;
            ans++;
        }
    }
    return ans;
}

int main(){
    int K, L;
    while (cin >> K >> L) {
        if (K == 0 and L == 0) break;
        keywords.clear();
        string line;
        getline(cin, line);
        for (int i = 0; i < K; ++i) {
            getline(cin, line);
            keywords.push_back(line);
            assert(line.size() > 0);
        }
        assert(keywords.size() == K);
        simplifyKeywords();
        assert(keywords.size() <= K);
        K = keywords.size();

        buildMatchingMachine(keywords);

        int ans = 0;
        for (int i = 0; i < L; ++i) {
            getline(cin, line);
            ans += minimumChanges(line);
        }
        cout << ans << endl;
    }
    return 0;
}