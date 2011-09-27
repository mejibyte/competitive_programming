// Accepted
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

const int MAXN = 105;
bool g[MAXN][MAXN];
int color[MAXN];
int nodes;

enum { white, gray, black };

map<string, int> face;
int currentFace;

int getIndex(const string &s) {
    if (face.count(s) > 0) return face[s];
    return face[s] = currentFace++;
}

void clear() {
    memset(g, 0, sizeof g);
    face.clear();
    currentFace = 0;
}

bool cycleFrom(int u) {
    if (color[u] == gray) return true;
    if (color[u] == black) return false;
    color[u] = gray;
    for (int v = 0; v < nodes; ++v) {
        if (!g[u][v]) continue;
        if (cycleFrom(v)) return true;
    }
    color[u] = black;
    return false;
}

bool cycle() {
    for (int i = 0; i < nodes; ++i) color[i] = white;
    for (int i = 0; i < nodes; ++i) {
        if (cycleFrom(i)) return true;
    }
    return false;
}

void solve() {
    if (!cycle()) {
        printf("F\n");
        return;
    }
    
    for (int u = 0; u < nodes; ++u) {
        for (int v = 0; v < nodes; ++v) {
            if (g[u][v]) {
                g[u][v] = false;
                if (!cycle()) {
                    printf("P\n");
                    return;
                }
                g[u][v] = true;
            }
        }
    }
    
    printf("N\n");
}

int main(){
    string alice, bob;
    while (cin >> alice >> bob) {
        if (alice == "*" and bob == "*") break;
        string s;
        
        vector< vector<string> > a(1);
        while (cin >> s) {
            if (s == ";") break;
            if (s == ",") {
                a.push_back(vector<string>());
                continue;
            }
            a.back().push_back(s);
        }
        
        vector< vector<string> > b(1);
        while (cin >> s) {
            if (s == ";") break;
            if (s == ",") {
                b.push_back(vector<string>());
                continue;
            }
            b.back().push_back(s);
        }
        
        clear();
        
        // for (int i = 0; i < a.size(); ++i) {
        //     printf("row[%d] has %d items\n", i, a[i].size());
        //     for (int j = 0; j < a[i].size(); ++j) {
        //         printf("%s ", a[i][j].c_str());
        //     }
        //     puts("");
        // }
        // 
        // for (int i = 0; i < b.size(); ++i) {
        //     printf("row[%d] has %d items\n", i, b[i].size());
        //     for (int j = 0; j < b[i].size(); ++j) {
        //         printf("%s ", b[i][j].c_str());
        //     }
        //     puts("");
        // }
        
        for (int i = 0; i < a.size(); ++i) {
            for (int j = 1; j < a[i].size(); ++j) {
                g[  getIndex(a[i][j-1])   ][  getIndex(a[i][j])  ] = true;
            }
        }
        
        for (int i = 0; i < b.size(); ++i) {
            for (int j = 1; j < b[i].size(); ++j) {
                g[  getIndex(b[i][j-1])   ][  getIndex(b[i][j])  ] = true;
            }
        }
        
        nodes = currentFace;
        //         for (int i = 0; i < nodes; ++i) {
        //             for (int j = 0; j < nodes; ++j) {
        //                 printf("%d ", g[i][j]);
        //             }
        //             puts("");
        //         }
        //         puts("");
        
        solve();
    }
    return 0;
}