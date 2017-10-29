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

#define INPUT_FILE "gas"


int main(){
    freopen(INPUT_FILE ".in", "r", stdin);
    long long l, gases;

    vector< pair<long long, long long> > stations;
    
    while(cin >> l >> gases) {
        bool found = true;
        stations.clear();
        if(l == 0 and gases == 0) break;
        for(long long i=0; i<gases; i++) {
            long long p, r;
            long long zero = 0;
            cin >> p >> r;
            long long li, ls;
            li = max(zero, p-r);
            ls = min(l, p+r);
            stations.push_back(make_pair(li, ls));
        }
        sort(stations.begin(), stations.end());
        long long last_index = 0;
        long long usados = 0;
        for(long long i = 0; i<l;) {
            long long fin = i;
            bool primero = true;
            for(long long g = last_index; g<stations.size(); ++g) {
                if (stations[g].first <= i and stations[g].second > i) {
                    if (primero) {
                        primero = false;
                        last_index = g;   
                    }
                    fin = max(fin, stations[g].second);
                }
                if (stations[g].first > i) break;
            }
            if(i == fin) {
                cout << -1 << endl; 
                found = false;
                break;
            }
            i = fin;
            usados++;
        }
        if (found) cout << gases-usados << endl;
        
    }
    return 0;

}
