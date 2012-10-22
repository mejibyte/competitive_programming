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

const int MAXN = 105;
int minn[MAXN];
int maxn[MAXN];
pair <int,int> prom[MAXN];
int w[MAXN];

int main () {
    int s,n,x;
    freopen("lazyprof.in","r",stdin);
    while(cin>>s>>n) {
        if (s == 0 && n == 0) break;
 
        for (int i = 0; i < n; ++i) {
            prom[i].first = 0;
            prom[i].second = i;
        }
    
        for (int i = 0; i < s; ++i) {
            for (int j = 0; j < n; ++j) {
                cin>>x;
                prom[j].first += x;
            }   
        }
        
        for (int i = 0; i < n; ++i) {
            cin>>minn[i]>>maxn[i];   
        }
        
        //For(i, 0, n) D(prom[i].first);
        
        sort(prom,prom+n);
        int acum = 100;

        for (int i = 0; i < n; ++i) {
            w[i] = minn[i];
            acum -= w[i];   
        }
        for (int i = n-1; i >= 0; --i) {
            int addw = min(  maxn[prom[i].second]   -   w[prom[i].second],  acum);
            acum -= addw;
            w[prom[i].second] += addw;   
        }
        
      
        double ans = 0.0;
        for (int i = 0; i < n; ++i) {
            ans += prom[i].first * w[prom[i].second];   
        }
        ans /=(100.0*s);
        printf("%.2lf\n", ans + EPS);
        
    }
    return 0;
}
