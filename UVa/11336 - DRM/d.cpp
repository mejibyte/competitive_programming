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

typedef map<string, vector<string> > graph;
typedef string node;

graph g1, g2;

void read(graph &g) {
    string s;
    while(getline(cin, s)) {
        while (s.size() > 0 and s[0] == ' ') s = s.substr(1);
        while (s.size() > 0 and s[s.size() - 1] == ' ') s.resize(s.size() - 1);
        assert(s.size() > 0);
        if (s == "* * *") break;
        
        string a, b;
        stringstream sin(s);
        assert(sin >> a >> b);
        g[a].push_back(b);
        g[b].push_back(a);
    }
    
}

bool reach(const node &s, const node &t) {
    set<node> seen;
    queue<node> q;
    seen.insert(s);
    q.push(s);
    while(q.size() > 0) {
        node u = q.front(); q.pop();
        if (u == t) return true;
        foreach(k, g2[u]) {
            if (*k != t and g1.count(*k) > 0) continue;
            if (seen.count(*k) > 0) continue;
            seen.insert(*k);
            q.push(*k);
        }
    }
    return false;
}

bool check() {
    foreach(u, g1) {
        if (g2.count(u->first) == 0) {
            return false;
        }
    }
    foreach(u, g1) {
        foreach(v, u->second) {
            if (!reach(u->first, *v)) {
                return false;
            }
        }
    }
    return true;
}

int main(){
    string s;
    while (getline(cin, s)) {
        if (s == "END") break;
        
        g1.clear();
        g2.clear();
        
        string title1 = s;
        read(g1);
        string title2;
        getline(cin, title2);
        read(g2);
        
        bool ans = check();
        if (ans) {
            printf("YES: %s is a more detailed version of %s\n", title2.c_str(), title1.c_str());
        } else {
            printf("NO: %s is not a more detailed version of %s\n", title2.c_str(), title1.c_str());
        }
        
    }
    return 0;
}