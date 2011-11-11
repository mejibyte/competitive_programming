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

#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

int main(){
    string s;
    while (cin >> s) {
        int n = s.size();
        s = "$" + s;
        vector<bool> mark(n + 1, false);
        int need = 0;
        
        for (int i = 2; i <= n; ++i) {
            if (mark[i]) continue;
            if (i + i <= n) {
                assert(i == 2 or i > 2 and mark[i + i]);
                for (int ii = i; ii <= n; ii += i) {
                    if (!mark[ii]) need++;
                    mark[ii] = true;
                }
            }
        }
        
        // for (int i = 1; i <= n; ++i){
        //     printf("%d ", (int)mark[i]);
        //     } puts("");
        
        map<char, int> count;
        int biggest = -1;
        char placeFirst = 0;
        for (int i = 1; i <= n; ++i) {
            int c = ++count[s[i]];
            if (c > biggest) {
                biggest = c;
                placeFirst = s[i];
            }
        }
                
        if (need > biggest) {
            puts("NO");
            continue;
        }

        string ans(n + 1, '*');
        for (int i = 1; i <= n; ++i) {
            if (!mark[i]) continue;
            assert( count[placeFirst] >= 1 );
            ans[i] = placeFirst;
            count[placeFirst]--;
        }
        
        for (int i = 1; i <= n; ++i) {
            if (mark[i]) continue;
            for (char place = 'a'; place <= 'z'; ++place) {
                if (count[place] > 0) {
                    ans[i] = place;
                    count[place]--;
                    break;
                }
            }
        }
        
        puts("YES");
        puts(ans.substr(1).c_str());
    }
    return 0;
}