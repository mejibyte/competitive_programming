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

#define INPUT_FILE "addition"

string ans [16];

int parse(string &a){
    if (a == "{}") return 0;
    stack <char> s;
    int ans = 1;
    for (int i = 0; i < a.size(); i++){
        char c = a[i];
        if (c == '{'){
            s.push('{');
        }
        if (c == '}'){
            s.pop();
        }
        if (c == ',' and s.size() == 1){
            ans++;
        }
    }
    return ans;
}

void precompute(){
    ans[0] = "{}";
    for (int i = 1; i < 16; i++){
        string s = "{";
        for (int j = 0; j < i; j++){
            s += ans[j];
            if (j != i - 1){
                s += ",";
            }
        }
        s += "}";
        ans[i] = s;
    }
}


int main(){
    freopen(INPUT_FILE ".in", "r", stdin); // Read from file
    int cases;
    precompute();
    cin >> cases;
    while (cases--){
        string first, second;
        cin >> first >> second;
        int a = parse(first);
        int b = parse(second);
        cout << ans[a+b] << endl;
    }   
    return 0;
}
