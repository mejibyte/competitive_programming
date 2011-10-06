///////////////////////////////////////////////////////////////
//         Aho-Corasick's algorithm, as explained in         //
//          http://dx.doi.org/10.1145/360825.360855          //
///////////////////////////////////////////////////////////////

// Max number of states in the matching machine.
// Should be equal to the sum of the length of all keywords.
const int MAXS = 6 * 50 + 10; 

// Number of characters in the alphabet.
const int MAXC = 26; 

// Output for each state, as a bitwise mask.
// Bit i in this mask is on if the keyword with index i
// appears when the machine enters this state.
int out[MAXS]; 

// Used internally in the algorithm.
int f[MAXS]; // Failure function
int g[MAXS][MAXC]; // Goto function, or -1 if fail.

// Builds the string matching machine.
// 
// words - Vector of keywords. The index of each keyword is
//         important:
//         "out[state] & (1 << i)" is > 0 if we just found
//          word[i] in the text.
// lowestChar - The lowest char in the alphabet.
//              Defaults to 'a'.
// highestChar - The highest char in the alphabet.
//               Defaults to 'z'.
//               "highestChar - lowestChar" must be <= MAXC,
//               otherwise we will access the g matrix outside
//               its bounds and things will go wrong.
//
// Returns the number of states that the new machine has. 
// States are numbered 0 up to the return value - 1, inclusive.
int buildMatchingMachine(const vector<string> &words,
                         char lowestChar = 'a',
                         char highestChar = 'z') {
    memset(out, 0, sizeof out);
    memset(f, -1, sizeof f);
    memset(g, -1, sizeof g);
    
    int states = 1; // Initially, we just have the 0 state
        
    for (int i = 0; i < words.size(); ++i) {
        const string &keyword = words[i];
        int currentState = 0;
        for (int j = 0; j < keyword.size(); ++j) {
            int c = keyword[j] - lowestChar;
            if (g[currentState][c] == -1) {
                // Allocate a new node
                g[currentState][c] = states++;
            }
            currentState = g[currentState][c];
        }
        // There's a match of keywords[i] at node currentState.        
        out[currentState] |= (1 << i);
    }
    
    // State 0 should have an outgoing edge for all characters.
    for (int c = 0; c < MAXC; ++c) {
        if (g[0][c] == -1) {
            g[0][c] = 0;
        }
    }

    // Now, let's build the failure function
    queue<int> q;
    // Iterate over every possible input
    for (int c = 0; c <= highestChar - lowestChar; ++c) {
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

                // Merge out values
                out[g[state][c]] |= out[failure]; 
                q.push(g[state][c]);
            }
        }
    }

    return states;
}

// Finds the next state the machine will transition to.
//
// currentState - The current state of the machine. Must be
//                between 0 and the number of states - 1,
//                inclusive.
// nextInput - The next character that enters into the machine.
//             Should be between lowestChar and highestChar,
//             inclusive.
// lowestChar - Should be the same lowestChar that was passed
//              to "buildMatchingMachine".

// Returns the next state the machine will transition to. 
// This is an integer between 0 and the number of states - 1,
// inclusive.
int findNextState(int currentState, char nextInput,
                                    char lowestChar = 'a') {
    int answer = currentState;
    int c = nextInput - lowestChar;
    while (g[answer][c] == -1) answer = f[answer];
    return g[answer][c];
}


// How to use this algorithm:
// 
// 1. Modify the MAXS and MAXC constants as appropriate.
// 2. Call buildMatchingMachine with the set of keywords to
//    search for.
// 3. Start at state 0. Call findNextState to incrementally
//    transition between states.
// 4. Check the out function to see if a keyword has been
//    matched.
//
// Example:
//
// Assume keywords is a vector that contains
// {"he", "she", "hers", "his"} and text is a string that
// contains "ahishers".
//
// Consider this program:
//
// buildMatchingMachine(keywords, 'a', 'z');
// int currentState = 0;
// for (int i = 0; i < text.size(); ++i) {
//    currentState = findNextState(currentState, text[i], 'a');
//
//    Nothing new, let's move on to the next character.
//    if (out[currentState] == 0) continue;
//
//    for (int j = 0; j < keywords.size(); ++j) {
//        if (out[currentState] & (1 << j)) {
//            //Matched keywords[j]
//            cout << "Keyword " << keywords[j]
//                 << " appears from "
//                 << i - keywords[j].size() + 1
//                 << " to " << i << endl;
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

///////////////////////////////////////////////////////////////
//               End of Aho-Corasick's algorithm             //
///////////////////////////////////////////////////////////////