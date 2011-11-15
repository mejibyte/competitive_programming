#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
#include <queue>
#include <map>
#include <cstdio>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <cstring>
#include <cassert>
using namespace std;

#define lcm(a, b) ((a * b) / __gcd(a, b))

//LCM of  2   3   4   5   6   7   8   9
#define D 2 * 3 * 2 * 5 * 1 * 7 * 2 * 3

const int least = 10;

int g[30][30];
int maski[30][D];
int d[30];
int d2[30];
int dobro[30];
vector<int> u[1000002];
vector<int> Ks;
vector< pair<int, int> > numery[1000];

vector<pair<int, pair<int, int> > > v;

int main() {
    ios_base::sync_with_stdio(false);
    int sa, sb;
    int n,T;
    cin >> n >> T;
    cin >> sa >> sb;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> g[i][j];
            if (g[i][j] > least) {
                Ks.push_back( g[i][j] );
            }
        }
    }
    sort(Ks.begin(), Ks.end());
    Ks.erase(unique(Ks.begin(), Ks.end()), Ks.end());
    // { Ks = Numbers in the board greater than 10 without repetition }

    for (int k = 0; k < Ks.size(); ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (g[i][j] == Ks[k]) {
                    numery[k].push_back( make_pair(i, j) );
                }
            }
        }
        
        // { numery[k] = Coordinates of cells that have number Ks[k] }
                    
        int z = Ks[k];
        while(z <= T + 1) {
            u[z].push_back(k);
            z += Ks[k];
        }
    }
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < D; ++k) {
                if (g[i][j] <= least && k % g[i][j] == 0) maski[i][k] |= (1 << j);
            }
        }
    }
    sa--;
    sb--;
    d[sa] |= (1 << sb);
    int t = 0;
    int md = 1;
    int z = 0;
    while(t < T){
        for (int i = 0; i < n; ++i) d2[i] = 0;
        for (int i = 0; i < n; ++i) dobro[i] = maski[i][md];
        for (int i = 0; i < u[t+1].size(); ++i) {
            for(int j = 0; j < numery[u[t+1][i]].size(); ++j){
                pair<int, int> p = numery[u[t+1][i]][j];
                dobro[p.first] |= (1 << p.second);
            }
        }
        for (int i = 0; i < n - 2; ++i) {
            d2[i+2] |= (d[i] >> 1) | (d[i] << 1);
            d2[i] |= (d[i+2] >> 1) | (d[i+2] << 1);
        }
        for (int i = 0; i < n - 1; ++i) {
            d2[i+1] |= (d[i] >> 2) | (d[i] << 2);
            d2[i] |= (d[i+1] >> 2) | (d[i+1] << 2);
        }
        int cos = 0;
        for(int i = 0; i < n; ++i) {
            d[i] = d2[i] & dobro[i];
            cos |= d[i];
        }
        if (!cos) break;
        md++;
        if (md == D) md=0;
        t++;
    }
    vector< pair<int, int> > ans;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (d[i] & (1 << j)) {
                ans.push_back( make_pair(i+1, j+1) );
            }
        }
    }
    cout<< ans.size() << endl;
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i].first << " " << ans[i].second << endl;
    }
    return 0;
}
