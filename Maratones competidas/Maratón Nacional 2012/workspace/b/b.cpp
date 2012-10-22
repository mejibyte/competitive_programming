using namespace std;
# include <algorithm>
# include <iostream>
# include <iterator>
# include <sstream>
# include <fstream>
# include <cassert>
# include <cstdlib>
# include <string>
# include <cstring>
# include <cstdio>
# include <vector>
# include <cmath>
# include <queue>
# include <stack>
# include <map>
# include <set>

#define For(i, a, b) for (int i = (a); i < (b); i++)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != v.end(); x++)
#define D(x) cout << #x  " = " << (x) << endl

const double EPS = 1e-9;
int cmp (double x, double y = 0, double tol = EPS){
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

const int MAXN = 1005;
string movies[MAXN];

int main () {
    freopen("movie.in", "r", stdin);
    int M, Q;
    cin >> M >> Q;
    for (int i = 0; i < M; ++i) cin >> movies[i];
    string clip;
    for (int i = 0; i < Q; ++i) {
        cin >> clip;
        
        int index = -1, best = (1 << 30);
        for (int m = 0; m < M; ++m) {
            if (movies[m].size() < clip.size()) continue;
            
            for (int start = 0; start + clip.size() <= movies[m].size(); ++start) {
                int score = 0;
                for (int k = start; k < start + clip.size(); ++k) score += clip[k - start] != movies[m][k];
                if (score < best) {
                    best = score;
                    index = m;
                }
            }
        }
        
        cout << index + 1 << endl;
    }
    return 0;
}
