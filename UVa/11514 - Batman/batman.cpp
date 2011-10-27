//CODIGO EQUIPO FACTOR COMUN


#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

struct power {
  string name;
  int atk;
  int e;
};

struct vil {
    string name;
    int def;
    vector<string> pweak;
};
bool com[1005][1005];
long long dp[1005][1005];
int main() {
  //assert(freopen("batman.in", "r", stdin) != NULL);
    int p,v,e;
    cin >> p >> v >> e;
    while(p!=0 && v!=0 && e!=0) {
        vector<power> powers(p);
        vector<vil> vils(v);
        for(int i =0; i<p;++i) {
            power pp;
            cin >> pp.name >> pp.atk >> pp.e;
            powers[i] = pp;
        }
        for(int i =0; i<v; ++i) {
            vil vv;
            string pw;
            cin >> vv.name >> vv.def >> pw;
            for(int k =0; k<pw.size(); ++k) {
                if(pw[k]==',') pw[k] = ' ';
            }
            stringstream ss(pw);
            while(ss>>pw) vv.pweak.push_back(pw);
            sort(vv.pweak.begin(),vv.pweak.end());
            vils[i] = vv;
        }
        
        //bool com[p+1][v+1];
        memset(com,0,sizeof com);
        for(int i=0;i<p;++i) {
            for(int j =0; j<v; ++j) {
                com[i+1][j+1] = powers[i].atk>=vils[j].def && binary_search(vils[j].pweak.begin(),vils[j].pweak.end(),powers[i].name);
            }
        }
        //long long dp[p+1][v+1];
        for(int j = 1; j<=v; ++j) {
            dp[0][j] = INT_MAX;
        }
        for(int i = 0; i<=p; ++i ) {
            dp[i][0] = 0;
        }
        for(int i=1; i<=p; ++i) {
            for(int j =1; j<=v; ++j) {
                dp[i][j] = dp[i-1][j];
                if(com[i][j]) dp[i][j] = min(dp[i][j],dp[i-1][j-1]+powers[i-1].e);
            }
        }
        if(dp[p][v]<=e) cout << "Yes" << endl;
        else cout << "No" << endl;
        /*for(int i=0;i<p;++i) {
            for(int j =0; j<v; ++j) {
                cout << com[i+1][j+1];
            }
            cout << endl;
        }*/
        /*for(int i=1; i<=p; ++i) {
            for(int j =1; j<=v; ++j) {
                cout << dp[i][j] << " ";
            }
            cout << endl;
        }*/
        cin >> p >> v >> e;
    }
    return 0;
}
