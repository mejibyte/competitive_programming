// Equipo Poncho, Carriel y Ruana
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
#include <stack>
#include <list>
#include <map>
#include <set>

template <class T> string toStr(const T &x)
{ stringstream s; s << x; return s.str(); }
template <class T> int toInt(const T &x)
{ stringstream s; s << x; int r; s >> r; return r; }

#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
#define D(x) cout << #x " = " << (x) << endl;

const double EPS = 1e-9;

int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

#define INPUT_FILE "problemname"


int main(){
    freopen(INPUT_FILE ".in", "r", stdin);
    long long l, gases;

    vector<pair<long long, long long>> stations;
    
    while(cin >> l >> gases) {
        
        stations.clear();
        if(l == 0 and gases == 0) break;
        for(long long i=0; i<g; i++) {
            long long p, r;
            cin >> p >> r;
            long long li, ls;
            li = max(0, p-r);
            ls = min(l, p+r);
            stations.push_back(make_pair(li, ls);
        }
        sort(stations.begin(), stations.end());
        long long usados = 0;
        for(long long i = 0; i<l;) {
            long long fin = i;
            for(long long g; g<stations.length(); ++g) {
                if (stations[g].first <= i and stations[g].second > i) {
                    fin = max(fin, stations[g].second);
                }
                if (stations[g].first > i) break;
            }
            if(i == fin) {
                cout << -1 << endl; 
                break;
            }
            i = fin;
            usados++;
        }
        cout << gases-usados << endl;
        
    }
    return 0;

}
