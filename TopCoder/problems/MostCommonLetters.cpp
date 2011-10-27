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

class MostCommonLetters {
  public:
  string listMostCommon(vector <string> text);

  

};

string MostCommonLetters::listMostCommon(vector <string> text) {
    map<char, int> m;
    int biggest = 0;
    for (int i = 0; i < text.size(); ++i){
        const string &s = text[i];
        for (int j = 0; j < s.size(); j++){
            if (s[j] == ' ') continue;
            m[s[j]]++;
            biggest = max(m[s[j]], biggest);
        }
    }
    string ans = "";
    for (char c = 'a'; c <= 'z'; ++c) {
        if (m[c] == biggest){
            ans += c;
        }
    }
    return ans;
}



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
