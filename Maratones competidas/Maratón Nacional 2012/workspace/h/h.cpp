// Equipo Ultimatum

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


vector<int> captains;

const int MAXN = 5005;
set<int> amigos[MAXN];
string equipo[MAXN];
int talla[MAXN];

vector<string> equipos;

int main () {
    freopen("teamface.in", "r", stdin);
    int run = 1;
    int T, N;
    while (cin >> T >> N) {
        if (T == 0 and N == 0) break;
        
        int M = N / T;
        captains.clear();
        equipos.clear();
        for (int i = 0; i < N; ++i) {
            equipo[i] = "";
            amigos[i].clear();
            talla[i] = -1;
        }
        
        for (int i = 0; i < T; ++i) {
            string nombre;
            int cap;
            cin >> nombre >> cap;
            cap--;
            equipo[cap] = nombre;
            captains.push_back( cap );
            equipos.push_back(nombre);
        }
        for (int i = 0; i < N; ++i) {
            int id, mitalla, size;
            cin >> id >> mitalla >> size;
            id--;
            talla[id] = mitalla;
            while (size--) {
                int amigo; cin >> amigo; amigo--;
                amigos[id].insert(amigo);
            }
        }
     
        
        for (int i = 0; i < captains.size(); ++i) {
            int cap = captains[i];
     
            for (int j = 0; j < N; ++j) {
                if (j == cap) continue;
        
                           
                if (amigos[cap].count(j) and amigos[j].count(cap)) {
       
                    vector<int> inter;
                    for(set<int>::iterator i = amigos[cap].begin(); i != amigos[cap].end(); ++i) {
                        if (amigos[j].count(*i)) inter.push_back( *i );
                    
                    }
                    if (inter.size() >= M - 2) {
                        assert(equipo[j] == "");
                        equipo[j] = equipo[cap];
                    }
                }
            }
        }
        for (int i = 0; i < N; ++i) assert(equipo[i] != "");
        
        
        printf("Case %d:\n", run++);
        assert(T == equipos.size());
        for (int i = 0; i < T; ++i) {
            const string &e = equipos[i];
            cout << e << endl;
            map<int, int> rep;
            for (int i = 0; i < N; ++i) {
                if (equipo[i] == e) {
                    rep[talla[i]]++;
                }
            }
            for (map<int, int>::iterator i = rep.begin(); i != rep.end(); ++i) {
                printf("%d %d\n", i->first, i->second);
            }
        }
    }
    return 0;
}
