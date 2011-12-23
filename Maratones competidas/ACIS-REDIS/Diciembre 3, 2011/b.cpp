using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
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

template <class T> string toStr(const T &x)
{ stringstream s; s << x; return s.str(); }
template <class T> int toInt(const T &x)
{ stringstream s; s << x; int r; s >> r; return r; }

#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); \
                           x != (v).end(); ++x)
#define D(x) cout << #x " = " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS){
    return( x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

#define INPUT_FILE "lookandsay"

int main(){
    freopen(INPUT_FILE ".in", "r", stdin); // Read from file 
    int n;
    cin >> n;
    while (n--) {
        string s; cin >> s;
        vector<int> ans;
        for (int i = 0; i < s.size(); ++i) {
            int times = 0;
            int j = i;
            while (j < s.size() and s[i] == s[j]) {
                j++;
                times++;
            }
            ans.push_back(times);
            ans.push_back(s[i] - '0');
            i = j - 1;
        }   
        
        for (int i = 0; i < ans.size(); ++i) cout << ans[i];
        cout << endl;
    }
    
    return 0;
}
