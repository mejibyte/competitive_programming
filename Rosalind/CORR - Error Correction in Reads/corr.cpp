// Andrés Mejía
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
#include <bitset>
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

string complement(const string &t) {
    string ans = t;
    reverse(ans.begin(), ans.end());
    int at = 'A' ^ 'T';
    int cg = 'C' ^ 'G';
    for (int i = 0; i < ans.size(); ++i) {
        if (ans[i] == 'A' or ans[i] == 'T') ans[i] ^= at;
        else ans[i] ^= cg;
    }
    return ans;
}

int distance(const string &s, const string &t) {
    int ans = 0;
    for (int i = 0; i < s.size(); ++i) ans += s[i] != t[i];
    return ans;
}

int main(){
    
    vector<string> v;
    for (string s; cin >> s; v.push_back(s));
    vector<bool> correct(v.size(), false);
    
    for (int i = 0; i < v.size(); ++i) {
        int times = 0;
        for (int j = 0; j < v.size(); ++j) {
            if (v[j] == v[i] or complement(v[j]) == v[i]) times++;
            
            if (v[i] == complement(v[j])) assert(complement(v[i]) == v[j]);
            if (v[j] == complement(v[i])) assert(complement(v[j]) == v[i]);
        }
        if (times >= 2) correct[i] = true;
    }
    for (int i = 0; i < v.size(); ++i) if (!correct[i]) {
        bool found = false;
        for (int j = 0; j < v.size(); ++j) if (correct[j]){
            if (::distance(v[i], v[j]) == 1) {
                cout << v[i] << "->" << v[j] << endl;
                found = true;
                break;
            }
            if (::distance(v[i], complement(v[j])) == 1) {
                cout << v[i] << "->" << complement(v[j]) << endl;
                found = true;
                break;
            }
        }
        assert(found);
    }
    
    return 0;
}