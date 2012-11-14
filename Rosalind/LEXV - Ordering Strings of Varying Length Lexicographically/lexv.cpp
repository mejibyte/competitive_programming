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

vector<string> v;
int n;
vector<string> ans;

void generate(int len) {
    for (int i = 0; i < ans.size(); ++i) cout << ans[i];
    cout << endl;
    
    if (len < n) {
        for (int i = 0; i < v.size(); ++i) {
            ans.push_back(v[i]);
            generate(len + 1);
            ans.pop_back();
        }
    }
}

int main(){
    string s; getline(cin, s);
    stringstream sin(s);
    for (string s; sin >> s; v.push_back(s));
    cin >> n;
    generate(0);
    return 0;
}