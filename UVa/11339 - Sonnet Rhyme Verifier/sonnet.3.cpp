// Andrés Mejía
// Wrong Answer
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

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

bool punctuation(wchar_t c) {
    wstring bad = L"(¡, !, ,, ., :, ;, ¿, ?, -) \t";
    for (int i = 0; i < bad.size(); ++i) {
        if (bad[i] == c) return true;
    }
    return false;
}

wstring clean(const wstring &s) {
    wstring ans;
    for (int i = 0; i < s.size(); ++i) {
        //if (punctuation(s[i])) continue;
        //if (i % 3 == 0) continue;
        wcout << s[i] << " ";
        ans += s[i];
    }
    return ans;
}

int main(){
    wstring s;
    while (getline(wcin, s)) {
        wstringstream sin(s);
        vector<wstring> suffixes;
        while (sin >> s) {
            suffixes.push_back(s);
        }
        
        wstring title;
        getline(wcin, title);
        
        while (getline(wcin, s)) {
            if (s == L"") break;
            
            wcout << s << endl;
            s = clean(s);
            
            wcout << s << endl;
        }
        
    }
    return 0;
}