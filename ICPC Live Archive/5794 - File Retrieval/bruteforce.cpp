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

int main(){
    int F;
    while (scanf("%d ", &F) == 1) {
        if (F == 0) break;
        vector<string> files;
        for (int i = 0; i < F; ++i) {
            static char buffer[10005];
            scanf(" %s ", buffer);
            files.push_back(string(buffer));
        }
        
        set<long long> seen;
        for (int k = 0; k < F; ++k) {
            const string &s = files[k];
            for (int i = 0; i < s.size(); ++i) {
                for (int j = i; j < s.size(); ++j) {
                    string key = s.substr(i, j - i + 1);
                    
                    long long mask = 0;
                    for (int f = 0; f < F; ++f) {
                        if (files[f].find(key) != string::npos) mask |= (1LL << f);
                    }
                    seen.insert(mask);
                }
            }
        }
        printf("%lld\n", (long long)seen.size());
    }
    return 0;
}